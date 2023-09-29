## ################################################################################
##     copyright            : (C) MIXMOD Team - 2001-2014
##     email                : contact@mixmod.org
## ################################################################################

## ################################################################################
##     This file is part of MIXMOD

##     MIXMOD is free software: you can redistribute it and/or modify
##     it under the terms of the GNU General Public License as published by
##     the Free Software Foundation, either version 3 of the License, or
##     (at your option) any later version.

##     MIXMOD is distributed in the hope that it will be useful,
##     but WITHOUT ANY WARRANTY; without even the implied warranty of
##     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##     GNU General Public License for more details.

##     You should have received a copy of the GNU General Public License
##     along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

##     All information available on : http://www.mixmod.org
## ################################################################################

##  @author: Christian Poli, INRIA

cdef class Builder(object):
    #cdef mxm.ClusteringStrategy *c_strategy
    cdef mxm.Input *input_
    cdef mxm.DataDescription *data_desc
    #cdef mxm.ClusteringMain *c_main
    cdef mxm.GaussianData *gauss_data
    cdef mxm.BinaryData *bin_data
    cdef mxm.CompositeData *composite_data

    cdef object_, data_factor
    def __cinit__(self, obj):
        self.input_ = NULL
        self.data_desc = NULL
        self.gauss_data = NULL
        self.bin_data = NULL
        self.composite_data = NULL
        self.object_ = obj

    def __dealloc__(self):
        #print ("CALL DEALLOC")
        if self.input_ is not NULL:
            del self.input_
            self.input_ = NULL
        if self.data_desc is not NULL:
            del self.data_desc
            self.data_desc = NULL
        if self.gauss_data is not NULL:
            del self.gauss_data
            self.gauss_data = NULL
        if self.bin_data is not NULL:
            del self.bin_data
            self.bin_data = NULL
        if self.composite_data is not NULL:
            del self.composite_data
            self.composite_data = NULL
    cdef get_data_factor(self):
        factor = []
        data = self.object_.data
        for k in data.columns:
            if data[k].dtype.name != 'category':
                factor.append(0)
            else:
                e = data[k].cat.categories
                factor.append(len(e))
        return factor
    cdef process_data_desc(self):
        cdef mxm.DataType data_type_
        cdef mxm.DataDescription *result = NULL
        if self.object_.data_type == gm.QUANTITATIVE:
            data_type_ = mxm.QuantitativeData
            self.gauss_data = data2gaussian(self.object_.data)
            result = new mxm.DataDescription(self.gauss_data)
        elif self.object_.data_type == gm.QUALITATIVE:
            data_type_ = mxm.QualitativeData
            self.bin_data = data2binary(self.object_.data)
            result = new mxm.DataDescription(self.bin_data)
        else:
            data_type_ = mxm.HeterogeneousData
            self.composite_data = data2composite(self.object_.data)
            result = new mxm.DataDescription(self.composite_data)
        if result is NULL:
            raise MemoryError()
        self.data_desc =  result

    cdef set_weight(self):
        if self.object_.weight is None:
            return
        cdef vector[double] weight_ = self.object_.weight
        self.input_.setWeight(&weight_.front())


    cdef set_known_partition(self):
        if self.object_.known_labels is None:
            return
        cdef vector[int64_t] labels = self.object_.known_labels
        cdef mxm.LabelDescription *label_desc
        label_desc = new mxm.LabelDescription(labels.size(), labels)
        self.input_.setKnownLabelDescription(label_desc[0])
        del label_desc

    cdef set_model(self):
        if self.object_.models is None:
            return
        cdef vector[mxm.ModelName] mvect
        for m in self.object_.models:
            mvect.push_back(<mxm.ModelName>m.value)
        self.input_.setModel(mvect)

    cdef finalize(self):
        cdef mxm.Input *ptr_
        ptr_ = <mxm.Input*>self.input_
        ptr_.finalize()

    cdef add_output(self, mxm.ModelOutput* m_output, models):
        cdef string model_name
        data_type = self.object_.data_type
        model_name = mxm.ModelNameToString(m_output.getModelType().
                                           getModelName())
        model_err = <mxm.Exception&>m_output.getStrategyRunError()
        model_err_str = m_output.getStrategyRunError().what()
        models.add(<object>model_name)
        result = dict(model=model_name,nb_cluster = m_output.getNbCluster(), model_error=model_err_str)
        if m_output.getStrategyRunError() == mxm.NOERROR:
            result['likelihood'] = m_output.getLikelihood()
            if data_type == gm.QUANTITATIVE:
                parameters = self.make_gaussian_param(m_output)
            elif data_type == gm.QUALITATIVE:
                parameters = self.make_binary_param(m_output)
            elif data_type == gm.HETEROGENEOUS:
                parameters = self.make_composite_param(m_output)
            else:
                raise ValueError("Unknown data type {}".format(data_type))
            result['parameters'] = parameters
        return result

    cdef make_gaussian_param(self, mxm.ModelOutput* m_output):
        cdef mxm.Parameter* par
        cdef mxm.GaussianParameter* g_par
        cdef mxm.GaussianEDDAParameter*  ge_par
        cdef mxm.Matrix** matrix_variance
        cdef double* c_proportions
        par = m_output.getParameterDescription().getParameter()
        g_par = <mxm.GaussianParameter*>par
        ge_par = <mxm.GaussianEDDAParameter*>par
        c_proportions = par.getTabProportion()
        nb_cluster = m_output.getNbCluster()
        proportions = [c_proportions[i] for i in range(nb_cluster)]
        nb_var = par.getPbDimension()
        nb_sample = self.object_.data.shape[0]
        #c_tab_mean = g_par.getTabMean()
        mean = c_matrix2ndarray(nb_cluster,nb_var,g_par.getTabMean())
        matrix_variance = ge_par.getTabSigma()
        variance=[c_matrix2ndarray(nb_var,nb_var,matrix_variance[i].storeToArray()) for i in range(nb_cluster)]
        return GaussianParameter(proportions=proportions, mean=mean, variance=variance, nb_free_param=par.getFreeParameter())

    cdef make_binary_param(self, mxm.ModelOutput* m_output):
        cdef mxm.Parameter* par
        cdef mxm.BinaryParameter* b_par
        cdef double* c_proportions
        cdef  double *** c_scatter
        par = m_output.getParameterDescription().getParameter()
        b_par = <mxm.BinaryParameter*>par
        nb_var = par.getPbDimension()
        nb_sample = self.object_.data.shape[0]
        c_proportions = par.getTabProportion()
        nb_cluster = m_output.getNbCluster()
        proportions = [c_proportions[i] for i in range(nb_cluster)]
        center = c_matrix2ndarray_int(nb_cluster,nb_var,b_par.getTabCenter())
        cdef int64_t* c_factor = b_par.getTabNbModality()
        factor = [c_factor[i] for i in range(nb_var)]
        c_scatter = b_par.scatterToArray()
        max_ = max(factor)
        scatter = []
        for k in range(nb_cluster):
            mx_out = np.empty([nb_var, max_])
            for j in range(nb_var):
                for h in range(factor[j]):
                    mx_out[j,h] = c_scatter[k][j][h]
            scatter.append(mx_out)
        return MultinomialParameter(proportions=proportions, center=center, factor=factor, scatter=scatter, nb_free_param=par.getFreeParameter())

    cdef make_composite_param(self, mxm.ModelOutput* m_output):
        cdef mxm.Parameter* par
        cdef mxm.CompositeParameter* c_par
        cdef mxm.GaussianParameter* g_par
        cdef mxm.GaussianEDDAParameter*  ge_par
        cdef mxm.BinaryParameter* b_par

        cdef mxm.Matrix** matrix_variance
        #cdef double* c_proportions
        par = m_output.getParameterDescription().getParameter()
        c_par = < mxm.CompositeParameter*>par
        ge_par = <mxm.GaussianEDDAParameter*>c_par.getGaussianParameter()
        g_par = <mxm.GaussianParameter*>ge_par
        b_par = c_par.getBinaryParameter()
        nb_cluster = m_output.getNbCluster()
        cdef int64_t nb_var_gauss = (<mxm.Parameter*>ge_par).getPbDimension()
        cdef int64_t nb_var_bin = (<mxm.Parameter*>b_par).getPbDimension()
        cdef double* c_proportions_g = (<mxm.Parameter*>ge_par).\
                                       getTabProportion()
        proportions_g = [c_proportions_g[i] for i in range(nb_cluster)]


        nb_var = par.getPbDimension()
        nb_sample = self.object_.data.shape[0]
        mean = c_matrix2ndarray(nb_cluster,nb_var_gauss,g_par.getTabMean())
        matrix_variance = ge_par.getTabSigma()
        variance=[c_matrix2ndarray(nb_var_gauss,nb_var_gauss,matrix_variance[i].storeToArray()) for i in range(nb_cluster)]
        g_param = GaussianParameter(proportions=proportions_g, mean=mean, variance=variance, nb_free_param=g_par.getFreeParameter())
        # binary parameter
        cdef double* c_proportions_b =  (<mxm.Parameter*>b_par).\
                                       getTabProportion()
        proportions_b = [c_proportions_b[i] for i in range(nb_cluster)]
        center = c_matrix2ndarray_int(nb_cluster,nb_var_bin,b_par.getTabCenter())
        cdef int64_t* c_factor = b_par.getTabNbModality()
        factor = [c_factor[i] for i in range(nb_var_bin)]
        c_scatter = b_par.scatterToArray()
        max_ = max(factor)
        scatter = []
        for k in range(nb_cluster):
            mx_out = np.empty([nb_var_bin, max_])
            for j in range(nb_var_bin):
                for h in range(factor[j]):
                    mx_out[j,h] = c_scatter[k][j][h]
            scatter.append(mx_out)
        m_param = MultinomialParameter(proportions=proportions_b,
                                       center=center, factor=factor,
                                       scatter=scatter, nb_free_param=b_par.getFreeParameter())
        return CompositeParameter(g_parameter=g_param, m_parameter=m_param, factor=self.get_data_factor(), proportions=proportions_g, nb_free_param=par.getFreeParameter())



cdef class ClusteringBuilder(Builder):
    cdef mxm.ClusteringStrategy *c_strategy
    cdef mxm.ClusteringMain *c_main
    cdef object strategy
    cdef set_criterion(self):
        criterion_ = self.object_.criterion
        cdef mxm.ClusteringInput *ptr_
        ptr_ = <mxm.ClusteringInput*>self.input_
        self.input_.removeCriterion(0)
        for cr in criterion_:
            if cr == gm.BIC:
                ptr_.addCriterion(mxm.BIC)
            elif cr == gm.ICL:
                ptr_.addCriterion(mxm.ICL)
            elif cr == gm.NEC:
                ptr_.addCriterion(mxm.NEC)
            elif cr == gm.CV:
                ptr_.addCriterion(mxm.CV)
            else:
                raise ValueError("Unknown criterion {}".format(cr))

    def process_input(self):
        self.process_data_desc()
        cdef vector[int64_t] cluster_array
        for c in self.object_.nb_cluster:
            cluster_array.push_back(c)
        self.input_ =  <mxm.Input*>new mxm.ClusteringInput(cluster_array, self.data_desc[0]);
        self.c_strategy = (<mxm.ClusteringInput*>self.input_).getStrategy()

    cdef get_output(self):
        data_type = self.object_.data_type
        cdef mxm.ClusteringOutput* c_out
        cdef mxm.ModelOutput* m_output
        #cdef mxm.Exception& c_exc
        #cdef string model_name
        if not self.c_main:
            raise ValueError("You have tu run clustering before getting output!")
        c_out = self.c_main.getOutput()
        crit_0 = (<mxm.Input*>self.input_).getCriterionName(0)
        c_out.sort(crit_0)
        ordered_by = None
        for e in gm.CriterionName:
            if e.value == crit_0:
                ordered_by = e
                break
        results = []
        models = set()
        if c_out.atLeastOneEstimationNoError():
            for i in range(c_out.getNbClusteringModelOutput()):
                m_output=<mxm.ModelOutput*>c_out.getClusteringModelOutput(i)
                cl_out = self.add_output(m_output, models)
                if m_output.getStrategyRunError() == mxm.NOERROR:
                    criterion=[]
                    criterion_value=[]
                    criterion_error=[]
                    #parameters = None
                    for crit in self.object_.criterion:
                        ## if crit == gm.BIC:
                        ##     crit_val= m_output.getCriterionOutput(mxm.BIC).\
                        ##     getValue()
                        ## elif crit == gm.ICL:
                        ##     crit_val= m_output.getCriterionOutput(mxm.ICL).\
                        ##     getValue()
                        ## elif crit == gm.NEC:
                        ##     crit_val= m_output.getCriterionOutput(mxm.NEC).\
                        ##     getValue()
                        ## else:
                        ##     raise ValueError("Unknown criterion {}".
                        ##                      format(crit))
                        crit_val = m_output.getCriterionOutput(crit.value).\
                                   getValue()
                        crit_err = not m_output.getCriterionOutput(crit.value).\
                                   getError() == mxm.NOERROR

                        #criterion.append((crit,crit_val))
                        criterion.append(crit)
                        criterion_value.append(crit_val)
                        criterion_error.append(crit_err)

                    cl_out['criterion'] = criterion
                    cl_out['criterion_value'] = criterion_value
                    cl_out['criterion_error'] = criterion_error
                    cl_out['partition'] =  m_output.getLabelDescription().getLabel().getLabel()
                    cl_out['proba'] = m_output.getProbaDescription().getProba().getProba()
                results.append(Result(**cl_out))
            cl = self.object_
            return ClusterOutput(data=cl.data, nb_cluster=cl.nb_cluster,
                              known_labels=cl.known_labels, ordered_by=ordered_by,
                              strategy=cl.strategy, criterion=cl.criterion,
                              models=list(models), data_type=cl.data_type,
                              weight=cl.weight, factor=None, results=results,
                              best_result=results[0])

    cdef set_algo(self):
        self.c_strategy.removeAlgo(0)
        for i, algo in enumerate(self.object_.strategy.algo):
            if algo.name == gm.EM:
                self.c_strategy.addAlgo(mxm.EM)
                self.c_strategy.setAlgoEpsilon(i, algo.epsilon)
            elif algo.name == gm.SEM:
                self.c_strategy.addAlgo(mxm.SEM)
            elif algo.name == gm.CEM:
                self.c_strategy.addAlgo(mxm.CEM)
                self.c_strategy.setAlgoEpsilon(i, algo.epsilon)
            else:
                raise ValueError("Unknown algo")
            self.c_strategy.setAlgoIteration(i, algo.nb_iteration)

    cdef set_init_algo(self):
        #cdef double* c_proportions, double** c_mean, double*** c_variance
        cdef double* c_proportions
        cdef double** c_mean
        cdef double** c_center
        cdef double*** c_variance
        cdef double*** c_scatter
        cdef int64_t* c_factor
        cdef vector[int64_t] labels_array
        cdef mxm.Parameter** c_parameter_p
        cdef mxm.Label* c_label
        cdef mxm.Partition* c_partition
        strategy = self.object_.strategy
        if strategy.init.name != gm.PARAMETER and strategy.init.name != gm.LABEL:
            self.c_strategy.setNbTry(strategy.nb_try)
            self.c_strategy.setNbTryInInit(strategy.init.nb_try)
        if strategy.init.name == gm.RANDOM:
            return
        elif strategy.init.name == gm.SMALL_EM:
            self.c_strategy.setStrategyInitName(mxm.SMALL_EM)
            self.c_strategy.setEpsilonInInit(strategy.init.epsilon)
            return
        elif strategy.init.name == gm.CEM_INIT:
            self.c_strategy.setStrategyInitName(mxm.CEM_INIT)
            return
        elif strategy.init.name == gm.SEM_MAX:
            self.c_strategy.setStrategyInitName(mxm.SEM_MAX)
            return
        elif strategy.init.name == gm.PARAMETER:
            self.c_strategy.setStrategyInitName(mxm.USER)
            param = strategy.init.parameter
            c_proportions = list_to_c_vector(param.proportions)
            if self.object_.data_type == gm.QUANTITATIVE:
                if not isinstance(param, GaussianParameter):
                    raise ValueError("gaussian data requires a GaussianParameter instance as parameter")

                c_mean = ndarray_to_c_matrix(param.mean)
                nb_cluster, pb_dimension = param.mean.shape
                c_variance = list_of_ndarray_to_c_matrix(param.variance)
                c_parameter_p = new_array_parameter_1 # kind of "macro" expanding: new XEM::Parameter*[1]
                c_parameter_p[0] = <mxm.Parameter*>new mxm.GaussianGeneralParameter(
                    nb_cluster,
                    pb_dimension,
                    self.input_.getModelType()[0],
                    c_proportions,
                    c_mean, c_variance)
                (<mxm.ClusteringInput*>self.input_).getStrategy().setTabInitParameter(c_parameter_p, 1)
            elif self.object_.data_type == gm.QUALITATIVE:
                if not isinstance(param, MultinomialParameter):
                    raise ValueError("multinomial data requires a MultinomialParameter instance as parameter")
                c_center  = ndarray_to_c_matrix(param.center)
                nb_cluster, pb_dimension = param.center.shape
                c_scatter = list_of_ndarray_to_c_matrix(param.scatter)
                c_factor = list_to_c_int_64_t_vector(param.factor)
                c_parameter_p = new_array_parameter_1 # kind of "macro" expanding: new XEM::Parameter*[1]
                c_parameter_p[0] = <mxm.Parameter*>new mxm.BinaryEkjhParameter(
                    nb_cluster,
                    pb_dimension,
                    self.input_.getModelType()[0],
                    c_factor,
                    c_proportions,
                    c_center,
                    c_scatter)
                (<mxm.ClusteringInput*>self.input_).getStrategy().setTabInitParameter(c_parameter_p, 1)
                #raise ValueError("not YET implemented")
            elif self.object_.data_type == gm.HETEROGENEOUS:
                if not isinstance(param, CompositeParameter):
                    raise ValueError("composite data requires a "
                                     "CompositeParameter instance as parameter")

                raise ValueError("not YET implemented")
            else:
                raise ValueError("unknown data type")


            return
        elif strategy.init.name == gm.LABEL:
            if len(self.object_.nb_cluster) != 1:
                raise ValueError("gm.LABEL initialization is illegal "
                                 "when nb_cluster is multiple")
            labels = strategy.init.labels
            nb_sample = self.object_.data.shape[0]
            if len(labels) != nb_sample:
                raise ValueError("The size of labels vector({}) doesn't match "
                                 "the number of samples ({})"
                                 .format(len(labels), nb_sample))
            self.c_strategy.setStrategyInitName(mxm.USER_PARTITION)
            for lab in labels:
                labels_array.push_back(lab)
            c_label = new mxm.Label(nb_sample)
            c_label.setLabel(labels_array, nb_sample)
            c_partition = new mxm.Partition(c_label, self.object_.nb_cluster[0])
            self.c_strategy.setInitPartition(c_partition, 0)
        else:
            raise ValueError("Not implemented init method {}".format(strategy.init.name.name))

    cdef main_run(self):
        self.c_main = new mxm.ClusteringMain(<mxm.ClusteringInput*>self.input_)
        #cdef int c_seed = -1
        self.c_main.run(self.object_.strategy.seed) #<int>self.strategy.seed)



cdef class LearningBuilder(Builder):
    cdef mxm.LearnMain *l_main
    cdef vector[int64_t] __labels
    #cdef mxm.LabelDescription *label_desc
    cdef set_criterion(self):
        criterion_ = self.object_.criterion
        cdef mxm.LearnInput *ptr_
        ptr_ = <mxm.LearnInput*>self.input_
        self.input_.removeCriterion(0)
        for cr in criterion_:
            if cr == gm.BIC:
                ptr_.addCriterion(mxm.BIC)
            elif cr == gm.ICL:
                ptr_.addCriterion(mxm.ICL)
            elif cr == gm.NEC:
                ptr_.addCriterion(mxm.NEC)
            elif cr == gm.CV:
                ptr_.addCriterion(mxm.CV)
            else:
                raise ValueError("Unknown criterion {}".format(cr))

    def __cinit__(self, obj):
        #self.label_desc = NULL
        pass

    def __dealloc__(self):
        print ("CALL LEARN DEALLOC")
        #if self.label_desc is not NULL:
        #    del self.label_desc
        #    self.label_desc = NULL

    def process_input(self):
        self.process_data_desc()

        for c in self.object_.known_labels:
            self.__labels.push_back(c)
        len_ = len(self.object_.known_labels)
        cdef mxm.LabelDescription *label_desc
        label_desc = new mxm.LabelDescription(len_, self.__labels)
        self.input_ = <mxm.Input*>new mxm.LearnInput(self.data_desc, label_desc)

    def set_nb_cv_block(self):
        if self.object_.nb_cv_block is None:
            return
        cdef mxm.LearnInput *ptr_
        ptr_ = <mxm.LearnInput*>self.input_
        ptr_.setNbCVBlock(self.object_.nb_cv_block)

    cdef main_run(self):
        self.l_main = new mxm.LearnMain(<mxm.LearnInput*>self.input_)
        #cdef int c_seed = -1
        self.l_main.run(-1) #<int>self.strategy.seed)

    cdef get_output(self):
        data_type = self.object_.data_type
        cdef mxm.LearnOutput* l_out
        cdef mxm.LearnModelOutput* m_output
        cdef int64_t** tab_
        if not self.l_main:
            raise ValueError("You have tu run clustering before getting output!")
        l_out = self.l_main.getLearnOutput()
        crit_0 = (<mxm.Input*>self.input_).getCriterionName(0)
        l_out.sort(crit_0)
        ordered_by = None
        for e in gm.CriterionName:
            if e.value == crit_0:
                ordered_by = e
                break

        results = []
        models = set()
        if l_out.atLeastOneEstimationNoError():
            for i in range(l_out.getNbLearnModelOutput()):
                m_output=<mxm.LearnModelOutput*>l_out.getLearnModelOutput(i)
                nb_cluster = m_output.getNbCluster()
                cl_out = self.add_output(<mxm.ModelOutput*>m_output, models)
                if m_output.getStrategyRunError() == mxm.NOERROR:
                    criterion=[]
                    criterion_value=[]
                    criterion_error=[]
                    #parameters = None
                    for crit in self.object_.criterion:
                        if crit == gm.BIC:
                            crit_val= m_output.getCriterionOutput(mxm.BIC).\
                            getValue()
                        elif crit == gm.CV:
                            crit_val= 1 - m_output.getCriterionOutput(mxm.CV).\
                            getValue()
                            cl_out['cv_label'] = m_output.getCVLabel().\
                              getLabel().getLabel()
                            tab_ =  m_output.getCVLabel().getLabel().\
                              getClassificationTab(self.__labels, nb_cluster)
                            cl_out['cv_classification'] = c_matrix2ndarray_int(nb_cluster, nb_cluster, tab_)
                            for j in range(nb_cluster):
                                array_delete_int64_p(tab_[j]) #(tab_[i])
                            array_delete_int64_pp(tab_)
                        else:
                            raise ValueError("Unknown criterion {}".
                                             format(crit))
                        crit_err = not m_output.getCriterionOutput(crit.value).\
                                   getError() == mxm.NOERROR

                        #criterion.append((crit,crit_val))
                        criterion.append(crit)
                        criterion_value.append(crit_val)
                        criterion_error.append(crit_err)
                    cl_out['criterion'] = criterion
                    cl_out['criterion_value'] = criterion_value
                    cl_out['criterion_error'] = criterion_error
                    cl_out['partition'] = self.__labels
                    tab_ =  m_output.getLabelDescription().getLabel().getClassificationTab(self.__labels, nb_cluster)
                    cl_out['map_classification'] =  c_matrix2ndarray_int(nb_cluster, nb_cluster, tab_)
                    for j in range(nb_cluster):
                        array_delete_int64_p(tab_[j]) #(tab_[i])
                    array_delete_int64_pp(tab_)
                    cl_out['map_error_rate'] =  m_output.getLabelDescription().getLabel().getErrorRate(self.__labels)
                results.append(LearnResult(**cl_out))
            cl = self.object_
            return LearnOutput(data=cl.data, nb_cluster=cl.nb_cluster,
                                 known_labels=cl.known_labels,ordered_by=ordered_by,
                                 nb_cv_block=cl.nb_cv_block, criterion=cl.criterion,
                                 models=list(models), data_type=cl.data_type,
                                 weight=cl.weight, factor=None, results=results,
                                 best_result=results[0])



cdef class PredictBuilder(Builder):
    cdef mxm.ParameterDescription* param_desc
    cdef mxm.PredictMain *p_main
    def __cinit__(self):
        self.param_desc = NULL
        self.p_main = NULL
    cdef mxm.ParameterDescription * process_parameters(self):
        #cdef mxm.ParameterDescription* param_desc
        class_rule = self.object_.classification_rule
        param = class_rule.parameters
        nb_cluster = class_rule.nb_cluster
        _, nb_variable = self.object_.data.shape
        cdef mxm.ModelName model_name = mxm.StringToModelName(class_rule.model)
        cdef vector[int64_t] factor, m_factor
        cdef double* c_proportions
        cdef double** c_mean
        cdef double** c_center
        cdef double*** c_variance
        cdef double*** c_scatter
        if self.object_.data_type == gm.QUANTITATIVE:
            c_proportions = list_to_c_vector(param.proportions)
            c_mean = ndarray_to_c_matrix(param.mean)
            c_variance = list_of_ndarray_to_c_matrix(param.variance)
            self.param_desc = new mxm.ParameterDescription(nb_cluster,
                                                           nb_variable,
                                                           model_name,
                                                           c_proportions,
                                                           c_mean,
                                                           c_variance)
        elif self.object_.data_type == gm.QUALITATIVE:
            for fact in param.factor:
                factor.push_back(fact)
            c_proportions = list_to_c_vector(param.proportions)
            c_center = ndarray_to_c_matrix(param.center)
            c_scatter = list_of_ndarray_to_c_matrix(param.scatter)
            self.param_desc = new mxm.ParameterDescription(nb_cluster,
                                                           nb_variable,
                                                           model_name ,
                                                           c_proportions,
                                                           c_center,
                                                           c_scatter, factor)
        else:
            g_param = param.g_parameter
            m_param = param.m_parameter
            c_proportions = list_to_c_vector(param.proportions)
            # gaussian
            c_mean = ndarray_to_c_matrix(g_param.mean)
            c_variance = list_of_ndarray_to_c_matrix(g_param.variance)
            # multimodal
            for fact in m_param.factor:
                m_factor.push_back(fact)
            c_center = ndarray_to_c_matrix(m_param.center)
            c_scatter = list_of_ndarray_to_c_matrix(m_param.scatter)
            self.param_desc = new mxm.ParameterDescription(nb_cluster,
                                                  m_factor.size(),
                                                  len(param.factor)-
                                                  m_factor.size(),
                                                  model_name,
                                                  c_proportions,
                                                  c_center,
                                                  c_scatter,
                                                  c_mean,
                                                  c_variance,
                                                  m_factor)
    def process_input(self):
        self.process_data_desc()
        self.process_parameters()
        self.input_ = <mxm.Input*>new mxm.PredictInput(self.data_desc,
                                                       self.param_desc)

    cdef main_run(self):
        self.p_main = new mxm.PredictMain(<mxm.PredictInput*>self.input_)
        self.p_main.run()
    def get_output(self):
        cdef mxm.ModelOutput* m_output
        m_output = <mxm.ModelOutput*>self.p_main.getPredictOutput().\
          getPredictModelOutput().front()
        if m_output.getStrategyRunError() == mxm.NOERROR:
            that = self.object_
            partition = m_output.getLabelDescription().getLabel().getLabel()
            proba = m_output.getProbaDescription().getProba().getProba()

            return PredictOutput(data=that.data, data_type=that.data_type,
                                nb_sample=that.nb_sample,
                                nb_variable=that.nb_variable,
                                error=None,
                                classification_rule=that.classification_rule,
                                partition=partition, proba=proba)
