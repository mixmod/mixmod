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

##     All informations available on : http://www.mixmod.org
## ################################################################################

##  @author: Christian Poli, INRIA

"""
**PyMixmod** is the Python package of **mixmodLib** version **3.0.1**

**Condition of use**

Copyright (C)  **MIXMOD** Team - 2001-2015

MIXMOD is publicly available under the GPL license (see www.gnu.org/copyleft/gpl.html)
You can redistribute it and/or modify it under the terms of the GPL-3 license.
Please understand that there may still be bugs and errors. Use it at your own risk.
We take no responsibility for any errors or omissions in this package or for any misfortune that may befall you or others as a result of its use.

Please report bugs at: http://www.mixmod.org/article.php3?id_article=23

More information on : www.mixmod.org

"""
from __future__ import (absolute_import, division,
                        print_function, unicode_literals)

cimport cppmixmod as mxm
from cppmixmod cimport array_delete_int64_p, array_delete_int64_pp
from cppmixmod cimport new_double_array, new_double_p_array, new_double_pp_array, new_int64_t_array, new_array_parameter_1
import numpy as np
import pandas as pnd
cimport numpy as cnp
import numbers
#import gmixmod as gm
from libc.stdlib cimport malloc, free
from cython.view cimport array as cvarray
from libc.stdint cimport int64_t
from libcpp.vector cimport vector
from libcpp.string cimport string
#import StringIO
try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO
    
import matplotlib
import matplotlib.pyplot as plt
import copy
include "util.pxi"
include "gmixmod.pxi"
include "plotutil.pxi"
include "conversion.pxi"
include "cbuilder.pxi"
include "strategy.pxi"
include "parameter.pxi"
include "models.pxi"

cdef class Result(object):
    """
    :Description: This class defines results for a given configuration

        .. admonition:: Constructor
            :class: warning

            Though **Result** class is instanciable, its instanciation is \
            dedicated to the API so it's not recomended to instanciate it in your \
            own programs.
        
    .. _result_class_var:
    
    :var nb_cluster: number of classes for the configuration
    :vartype nb_cluster: int+
    :var model: model descriptor for the configuration
    :vartype model: :ref:`gm.ModelName<gmMN>`
    :var criterion:  see :py:func:`cluster`
    :vartype criterion: :ref:`gm.CriterionName<gmCN>`, list[:ref:`gm.CriterionName<gmCN>`]
    :var criterion_value: value(s) for the criterion/criteria 
    :vartype criterion_value: float, list[float]
    :var parameters: see :py:class:`Parameter` and its subclasses
    :vartype parameters: :py:class:`GaussianParameter`, \
    :py:class:`MultinomialParameter`, \
    :py:class:`CompositeParameter`
    :var partition: integer list providing the labels assigned to observations \
    (data rows)
    :vartype partition: list[int]
    :var proba: matrix holding the probabilities for individuals to be assigned to a class
    :vartype proba: list[list[float]]
    :var likelihood: likelihood
    :vartype likelihood: float
    :var error: error code for the configuration
    """
    cdef readonly model, nb_cluster, model_error, likelihood, parameters,\
         criterion, criterion_value, criterion_error, partition, proba
    def __init__(self, model, model_error, nb_cluster=None,  likelihood=None,
                 parameters=None, criterion=None, criterion_value=None,
                 criterion_error=None, partition=None, proba=None):
        self.model = model
        self.nb_cluster = nb_cluster
        self.model_error = model_error
        self.likelihood = likelihood
        self.parameters = parameters
        self.criterion = criterion
        self.criterion_value = criterion_value
        self.criterion_error = criterion_error
        self.partition = partition
        self.proba = proba
    def to_str(self, out):
        model = self.model
        #criterion , criterion_value = self.criterion, self.criterion_value
        parameters = self.parameters
        likelihood = self.likelihood
        nb_cluster = self.nb_cluster
        out.write("* nbCluster   = {}\n".format(nb_cluster))      
        out.write("* model name  = {}\n".format(model))
        for criterion, criterion_value in zip(self.criterion, self.criterion_value):
            out.write("* criterion   = {criterion}({criterion_value:1.4f})\n".format(criterion=criterion.name, criterion_value=criterion_value))
        out.write("* likelihood  = {likelihood:1.4f}\n".format(likelihood=likelihood))
        out.write(str(parameters))
    def __str__(self):
        out = StringIO()
        self.to_str(out)
        res = out.getvalue()
        out.close()
        return res
    def __reduce__(self):
        return Result, (self.model, self.model_error, self.nb_cluster,
                        self.likelihood, self.parameters, self.criterion,
                        self.criterion_value, self.criterion_error,
                        self.partition, self.proba)

        
cdef class LearnResult(Result):
    """
    :Description: This class defines results for a given configuration \
    returned after a :py:func:`learn` call (see *results* and \
    *best_result* attributes on :py:class:`LearnOutput`). It inherits all features of \
    :py:class:`Result` class and additionally it defines specific features.

    .. admonition:: Constructor
        :class: warning

        Though **LearnResult** class is instanciable, its instanciation is \
        dedicated to the API so it's not recomended to instanciate it in your \
        own programs.

    :var cv_label: labels found by cross-validation
    :vartype cv_label: list[int+]
    :var cv_classification: cross-validation reclassification matrix (nb_cluster :math:`^2` sized)
    :vartype cv_classification: list[list[int+]]
    :var map_error_rate: error rate by MAP
    :vartype map_error_rate: float
    :var map_classification: MAP reclassification matrix (nb_cluster :math:`^2` sized)
    """
    cdef readonly cv_label, cv_classification, map_classification, map_error_rate
    def __init__(self, model, model_error, nb_cluster=None,  likelihood=None,
                 parameters=None, criterion=None, criterion_value=None,
                 criterion_error=None, partition=None, proba=None, cv_label=None,
                 cv_classification=None, map_classification=None,
                 map_error_rate=None):
        self.model = model
        self.nb_cluster = nb_cluster
        self.model_error = model_error
        self.likelihood = likelihood
        self.parameters = parameters
        self.criterion = criterion
        self.criterion_value = criterion_value
        self.criterion_error = criterion_error        
        self.partition = partition
        self.proba = proba
        self.cv_label = cv_label
        self.cv_classification = cv_classification
        self.map_classification = map_classification
        self.map_error_rate = map_error_rate
    def __reduce__(self):
        return LearnResult, (self.model, self.model_error, self.nb_cluster,
                             self.likelihood, self.parameters, self.criterion,
                             self.criterion_value, self.criterion_error,
                             self.partition, self.proba, self.cv_label,
                             self.cv_classification, self.map_classification,
                             self.map_error_rate)
    def to_str(self, out):
        super(LearnResult,self).to_str(out)
        criterion , criterion_value = self.criterion[0], self.criterion_value[0]
        if not self.cv_label:
            return
        out.write("* Classification with CV:\n")
        def header(i):
            out.write("           |")
            for i in range(self.nb_cluster):
                out.write(" Cluster {} |".format(i+1))
            out.write("\n")
        header(self.nb_cluster)
        def separator(i):
            out.write("-----------")
            for i in range(self.nb_cluster):
                out.write(" -----------")
            out.write("\n")
        separator(self.nb_cluster)
        for i in range(self.nb_cluster):
            out.write(" Cluster {} |".format(i+1))
            for j in range(self.nb_cluster):
                out.write(" {cell:9d} |".format(cell=self.cv_classification[i,j]))
            out.write("\n")
        separator(self.nb_cluster)
        out.write("* Error rate with CV = {rate:.2f}\n".format(rate=(1-criterion_value)*100))
        out.write("* Classification with MAP:\n")
        header(self.nb_cluster)
        for i in range(self.nb_cluster):
            out.write(" Cluster {} |".format(i+1))
            for j in range(self.nb_cluster):
                out.write(" {cell:9d} |".format(cell=self.map_classification[i,j]))
            out.write("\n")
        separator(self.nb_cluster)
        out.write("* Error rate with MAP = {rate:.2f}\n".format(rate=self.map_error_rate*100))
        
cdef class Output(object):
    """
    :Description: This class defines common features for  :py:func:`cluster` \
    and :py:func:`learn` output objects.
    
    .. admonition:: Constructor
        :class: warning

        This is an abstract class, so instanciate it isn't a good idea ...
        
    :var data:  see :py:func:`cluster`
    :type data:  numpy.ndarray, pandas.DataFrame    
    :var nb_cluster: see :py:func:`cluster`
    :var data_type: see :py:func:`cluster`
    :var nb_sample: number of individuals
    :vartype nb_sample: int
    :var nb_variable: number of variables
    :vartype nb_variable: int
    :var known_labels: see :py:func:`cluster`
    :vartype known_labels: pandas.Categorical, numpy.array(int+), list[int+]
    :var weight: see :py:func:`cluster`
    :vartype weight: list[int+], numpy.ndarray[int+],... 
    :var criterion: see :py:func:`cluster`
    :vartype criterion: :ref:`gm.CriterionName<gmCN>`, list[:ref:`gm.CriterionName<gmCN>`]
    :var models: see :py:func:`cluster`
    :vartype models: list[:ref:`gm.ModelName<gmMN>`]
    :var error: **False** if at least one configuration was computed successfully
    :vartype error: bool
    :var strategy: see :py:func:`cluster`
    :var factor: number of modalities for qualitative variables    
    """    
    cdef readonly data, nb_cluster,known_labels, criterion, error, ordered_by,
    cdef readonly models, weight, factor, results, best_result, data_type    
    def str_models(self):
        out = StringIO()
        out.write("****************************************\n")
        out.write("*** MIXMOD Models:\n")
        out.write("* list =")
        write_list(self.models, out)
        out.write("****************************************\n")
        res = out.getvalue()
        out.close()
        return res
    def to_str(self, out, summary=True):
        out.write("* nbCluster =")
        write_list(self.nb_cluster, out)
        for crit in self.criterion:
            out.write("* criterion = {}\n".format(crit.name))
        out.write(self.str_models())
        # to do : weight
        nb_sample, nb_var = self.data.shape
        if summary:
            nb_row = min(nb_sample, 10)
            nb_col = min(nb_var,10)
            out.write("* data (limited to a 10x10 matrix) =\n")
        else:
            nb_row = nb_sample
            nb_col = nb_var
            out.write("* data =\n")
        if  isinstance(self.data, pnd.core.frame.DataFrame):
            data_ix = self.data.iloc
        else:
            data_ix = self.data
        
        data = pnd.DataFrame(data_ix[:nb_row,:nb_col]) #,index=range(1,nb_row+1))        
        out.write(data.to_string(header=False))
        out.write("\n* ... ...\n")  
        # to do : known labels
    cdef set_results(self, results, best_result):
        pass
        if is_iterable(self.criterion) and len(self.criterion) > 1:
            self.results = {self.criterion[0] : results}
            self.best_result = {self.criterion[0] : best_result}
            for index_, crit in enumerate(self.criterion[1:], 1):
                self.results[crit] = results[:]
                self.results[crit].sort(key=lambda obj: (obj.criterion_error[index_],
                                       obj.criterion_value[index_],
                                       obj.parameters.nb_free_param))
                self.best_result[crit] = self.results[crit][0]

        else:
            self.results = results
            self.best_result = best_result            
    @property        
    def default_results(self):
        if isinstance(self.results, dict):
            return self.results[self.criterion[0]]
        else:
            return self.results
    @property
    def default_best_result(self):
        if isinstance(self.best_result, dict):
            return self.best_result[self.criterion[0]]
        else:
            return self.best_result
    def get_best_result(self, criterion=None):
        if criterion is None:
            return self.default_best_result
        return self.best_result[criterion]
                        
    ## def sort_by_criterion(self, criterion):
    ##     """
    ##     .. admonition:: Signature
    ##         :class: note

    ##         *obj.sort_by_criterion(criterion)*

    ##     :var criterion: a criterion member of the *obj.criterion* list
    ##     :vartype criterion: :ref:`gm.CriterionName<gmCN>`

    ##     .. warning:: This method returns no result. The object (obj) is \
    ##     modified:

    ##         * the sorting criterion is memorized in the *ordered_by*\
    ##         attribute.
    ##         * *results* and *best_result* attributes are updated.
    ##     """
    ##     if criterion not in self.criterion:
    ##         raise ValueError("Invalid criterion {}".format(criterion))
    ##     index_ = self.criterion.index(criterion)
    ##     self.results.sort(key=lambda obj: (obj.criterion_error[index_],
    ##                                    obj.criterion_value[index_],
    ##                                    obj.parameters.nb_free_param))
    ##     self.ordered_by = criterion
    ##     self.best_result = self.results[0]

## def sort_by_criterion(obj, criterion):
##     """
##     .. admonition:: Signature
##         :class: note
    
##         *mixmod.sort_by_criterion(obj, criterion)*
        
##     :var obj: object returned by a clustering or learning operation
##     :vartype obj: :py:class:`ClusterOutput`, :py:class:`LearnOutput`
##     :var criterion: a criterion member of the *output.criterion* list
##     :vartype criterion: :ref:`gm.CriterionName<gmCN>`

##     .. warning:: This method returns no result. The object (obj) is \
##     modified:

##         * the sorting criterion is memorized in the *ordered_by*\
##         attribute.
##         * *results* and *best_result* attributes are updated.
##     """
##     if not isinstance(obj, Output):
##         raise ValueError("invalid object: obj")
##     obj.sort_by_criterion(criterion)

cdef class ClusterOutput(Output):
    """
    :Description: This class defines the type returned by the \
    :py:func:`cluster` function. It inherits all features of \
    :py:class:`Output` class and additionally it defines specific features for \
    :py:func:`cluster` objects.
    
    .. admonition:: Constructor
        :class: warning

        Though **ClusterOutput** is instanciable, its instanciation is \
        dedicated to the API so it's not recomended to instanciate it in your \
        own programs.
        
    :var strategy: see :py:func:`cluster`
    :var results: provides :

        * the list of results for all configurations for a monocriterion clustering
        * a dictionary for a multicriteria clustering. Each entry in the dictionary \
          takes the form <criterion>: <list-of-results>
        
    :vartype results: list[:py:class:`Result`] or  dict(:ref:`gm.CriterionName<gmCN>` : list[:py:class:`Result`])
    :var best_result: the result of the best configuration for a monocriterion clustering or a dictionary when the clustering is multicriteria.
    :vartype best_result: :py:class:`Result` or dict(:ref:`gm.CriterionName<gmCN>` : :py:class:`Result`)
    """
    cdef readonly strategy
    def __cinit__(self, data, nb_cluster, known_labels, strategy, criterion,
                   models, data_type, weight, factor, results, best_result,
                  ordered_by=None, error=False):
        """
        cinit
        """
        self.data = data
        self.nb_cluster = nb_cluster
        self.known_labels = known_labels
        self.strategy = strategy
        self.criterion = criterion
        self.models = models
        self.data_type = data_type
        self.weight = weight
        self.factor = factor
        Output.set_results(self, results, best_result)
        ## if is_iterable(self.criterion) and len(self.criterion) > 1:
        ##     self.results = {self.criterion[0] : results}
        ##     self.best_result = {self.criterion[0] : best_result}
        ##     for index_, crit in enumerate(self.criterion[1:], 1):
        ##         self.results[crit] = results[:]
        ##         self.results[crit].sort(key=lambda obj: (obj.criterion_error[index_],
        ##                                obj.criterion_value[index_],
        ##                                obj.parameters.nb_free_param))
        ##         self.best_result[crit] = self.results[crit][0]

        ## else:
        ##     self.results = results
        ##     self.best_result = best_result        
            
        self.ordered_by = ordered_by
        self.error = error
    ## @property        
    ## def default_results(self):
    ##     if isinstance(self.results, dict):
    ##         return self.results[self.criterion[0]]
    ##     else:
    ##         return self.results
    ## @property
    ## def default_best_result(self):
    ##     if isinstance(self.best_result, dict):
    ##         return self.best_result[self.criterion[0]]
    ##     else:
    ##         return self.best_result
    def __reduce__(self):
        #import pymixmod
        return (ClusterOutput, #pymixmod.pickle_clustering_output,
                (
                    self.data,
                    self.nb_cluster,
                    self.known_labels,
                    self.strategy,
                    self.criterion,
                    self.models,
                    self.data_type,
                    self.weight,
                    self.factor,
                    self.results,
                    self.best_result,
                    self.ordered_by,
                    self.error))

        
    def write_delta(self, out):
        """
        write delta
        """
        out.write(str(self.strategy))
    def __str__(self):
        return self.dump()
    def dump(self, summary=False):
        out = StringIO()
        out.write("****************************************\n")
        out.write("*** INPUT:\n")
        out.write("****************************************\n")
        self.to_str(out, summary=summary)
        # to do : known labels
        out.write(str(self.strategy))
        if not self.error:        
            out.write("\n\n")
            out.write("****************************************\n")
            out.write("*** BEST MODEL OUTPUT:\n")
            out.write("*** According to the {} criterion\n".format(
                self.criterion[0].name))
            out.write("****************************************\n")            
            # best result
            self.default_best_result.to_str(out)
            #out.write("****************************************\n")                        
        res = out.getvalue()
        out.close()
        return res
    def summary(self):
        """
        Returns a displayable string giving the main information
        about the object
        """        
        return self.dump(summary=True)
    def plot(self, y=None, colors=None, r_digits=None, show_multi_cluster=False, show=True, criterion=None, **kwargs):
        """
        :Description: see :py:func:`plot` function
        
        .. admonition:: Signature
            :class: note
    
            *fig = x.plot([y, show=True, \*\*kwargs])*

        :Parameters:  see :py:func:`plot` function
        """
        data = self.data
        best_result = self.get_best_result(criterion)
        nb_sample, nb_var = data.shape
        if nb_var == 1:
            raise ValueError("data has only one variable. Try hist() method to get a 1D representation of x.")
        if self.data_type == gm.QUANTITATIVE:
            if y is not None:
                y = check_y_plot(y, data)
            else:
                y = list(range(nb_var))
            len_y = len(y)
            fig, plt_array = plt.subplots(len_y, len_y)
            # create histogram on diagonal
            for i, y_i in enumerate(y):
                hist_cluster_var(plt_array[i][i], best_result, data, var=y_i, **kwargs)
            if len(y) > 1:
                # create biplots
                for i, y_i in enumerate(y[1:], 1):
                    for j, y_j in enumerate(y[:i]):
                        plot_cluster(plt_array[i][j], best_result, data, x_var=y_j, y_var=y_i, **kwargs)
                for i in range(len_y):
                    for j in range(len_y):
                        if j > i:
                            (plt_array[i][j]).axis('off')
                plt.gcf().canvas.set_window_title('Quantitative variables')	
                if show:
                    plt.show()
        elif self.data_type == gm.QUALITATIVE:
            df = as_dataframe(data)
            mat_x = matrix2binary(df).as_matrix()
            n, p = data.shape
            unit_arr = np.empty(n,dtype=np.int)
            unit_arr.fill(1)
            d_c = np.dot(unit_arr, mat_x)            
            y = mat_x/np.sqrt(p*d_c)
            u_svd, s_svd, v_svd = np.linalg.svd(y)            
            indiv = np.dot(y, v_svd.T[:,1:3]/(p*1.0))
            
            if r_digits != None:
                indiv = np.round(indiv, decimals=r_digits)
            else:
                ind_threshold = (np.max(indiv) - np.min(indiv))/10000.0
                nb_digits = int(np.floor(np.log10(ind_threshold)))
                if nb_digits < 0:
                    indiv = np.round(indiv, decimals=-nb_digits)
            d_ind = dict()
            partition = best_result.partition
            point_size = []
            unique_ind = []
            point_part = []
            multi_cluster = set()
            for ind, part in zip(indiv, partition):
                k = (ind[0],ind[1]) # (x,y) for an individual
                ix =  d_ind.get(k,-1)
                if ix >= 0:
                    point_size[ix] += 1
                    if point_part[ix] != part:
                        multi_cluster.add(k)
                else:
                    unique_ind.append(k)
                    point_size.append(1)
                    point_part.append(part)
                    d_ind[k]=len(point_size)-1

            for k in set(point_part):
                #k_color = kwargs['colors'][k] if 'colors' in kwargs else get_color(k)
                for sz in set(point_size):
                    points = [p for i, p in enumerate(unique_ind) if point_part[i]==k and point_size[i]==sz]
                    if not len(points): continue
                    p_x, p_y = zip(*points)
                    plt.plot(p_x, p_y , marker=get_marker(k), markersize=5+2*sz, markerfacecolor='none', markeredgecolor=get_color(k, colors), linestyle='')
            if len(multi_cluster) and show_multi_cluster:
                print("show_multi_cluster")
                p_x, p_y =  zip(*list(multi_cluster))
                plt.plot(p_x, p_y , marker='x', markersize=10, color='red', linestyle='')
            plt.xlabel('Axis 1')
            plt.ylabel('Axis 2')
            plt.title('Multiple Correspondance Analysis')
            fig = plt.gcf()
            fig.canvas.set_window_title('Multiple Correspondance Analysis')	
            if show:
                plt.show()
                
        elif self.data_type == gm.HETEROGENEOUS:        
            raise ValueError("visualization for heterogeneous is not available yet")
        return fig
    def hist(self, variables=None, show=True, criterion=None, **kwargs):
        """
        :Description: see :py:func:`hist` function
        
        .. admonition:: Signature
            :class: note
    
            *fig = x.hist([variables, bins=10, show=True, \*\*kwargs])*

        :Parameters:  see :py:func:`hist` function
        """
        data = self.data
        #best_result = self.best_result
        best_result = self.get_best_result(criterion)
        nb_sample, nb_var = data.shape
        if self.data_type != gm.QUANTITATIVE:
            raise ValueError("data must contain only quantitative variables!")
        if variables is not None:
            variables = check_y_plot(variables, data)
        else:
            variables = list(range(nb_var))
        nb_sel_var = len(variables)
        if not nb_sel_var:
            raise ValueError("'variables' is empty!")
        if nb_sel_var < 4:
            plot_col = nb_sel_var
            plot_row = 1
        else:
            plot_col = int(np.floor(np.sqrt(nb_sel_var)))
            if nb_sel_var > plot_col**2:
                plot_row = plot_col + 1
            else:
                plot_row = plot_col
        fig, plt_array = plt.subplots(plot_row, plot_col) if plot_row>1 or plot_col>1 else plt.subplots(1)
        def get_plt_obj(i, j):
            if plot_row>1 and plot_col>1:
                return plt_array[i][j]
            if plot_row==1 and plot_col==1:
                return plt_array
            return plt_array[j]
        for v in variables:
            i = int(v // plot_col)
            j = v % plot_col
            hist_cluster_var(get_plt_obj(i,j), best_result, data, var=v, **kwargs)
        for r in range(j+1, plot_col):
            get_plt_obj(i,r).axis('off')
        plt.gcf().canvas.set_window_title('Variables histograms')	    
        if show:
            plt.show()
        return fig
    def barplot(self,*args, **kwargs):
        """
        :Description: see :py:func:`barplot` function
        
        .. admonition:: Signature
            :class: note
    
            *fig = x.barplot([variables, colors, show=True, \*\*kwargs])*

        :Parameters:  see :py:func:`barplot` function            
        """
        return barplot_cluster(self,*args, **kwargs)
            
def plot(x, *args, **kwargs):
    """
    :Description: This function plots data provided by a \
        :py:class:`ClusterOutput` instance (i.e. **x** parameter). It's \
        implementation is based on `matplotlib <http://matplotlib.org>`_. \
        Clusters are distinguished thanks to information provided by \
        :ref:`x.best_result.parameters<result_class_var>` and \
        :ref:`x.best_result.partition<result_class_var>`.
        
        * **For quantitative data**, ellipsoids (i.e. linear transformations of \
        hyperspheres) centered at the mean are drawn using \
        :ref:`x.best_result.parameters<result_class_var>`. The directions of the \
        principal axes of the ellipsoids are given by the eigenvectors of the \
        covariance matrix. The squared relative lengths of the \
        principal axes are given by the corresponding eigenvalues. \
        A 1-dimensional representation of variables with the densities is drawn on \
        the diagonal.
        * **For qualitative data**, a Multiple Correspondance Analysis is performed \
        to get a 2-dimensional representation of the data set. Bigger symbol means \
        that observations are similar.

    .. admonition:: Signature
        :class: note
    
            *fig = mixmod.plot(x, [y, show=True, criterion=None, \*\*kwargs])*

    :param x: object returned by :py:func:`cluster`
    :type x: :py:class:`ClusterOutput`
    :param y: a list of variable names or indices to plot. Relevant only for quantitative data.
    :type y: list[str], list[int], **default** = all
    :param colors: list of colors to be used instead of default colors. \
    Colors encoding must be `matplotlib <http://matplotlib.org>`_ compliant \
    (see http://matplotlib.org/api/colors_api.html). Relevant only for \
    qualitative data.    
    :type colors: list[str]
    :param with_ellipse: when **True** (i.e. by default), ellipsoids (cf. \
    Description) are drawn. Relevant only for quantitative data.
    :type with_ellipse: bool, **default** = True
    :param show: when set to **False** the result is not displayed. Useful \
    when the function is called  only in order to obtain the returned object \
    (e.g. for a later use with plotly)
    :type show: bool, **default** = True
    :param criterion: it selects the "best result" bound to this criterion \
    when **x** is the result of a multicriteria clustering.
    :type criterion: :ref:`gm.CriterionName<gmCN>`
    :param kwargs\*\*: further arguments are passed to **matplotlib**    
    :return: a `matplotlib <http://matplotlib.org>`_ figure object
    :rtype: `matplotlib.figure.Figure <http://matplotlib.org/api/figure_api.html>`_
    """
    x.plot(*args, **kwargs)

def hist(x, *args, **kwargs):
    """
    :Description: Builds and displays the histogram of quantitative data  \
        provided by a :py:class:`ClusterOutput` instance (i.e. **x** \
        parameter). It's implementation is based on \
        `matplotlib <http://matplotlib.org>`_. It uses information provided by \
        :ref:`x.best_result.parameters<result_class_var>` to plot densities.

    .. admonition:: Signature
        :class: note
    
            *fig = mixmod.hist(x, [variables, bins=10, show=True, criterion=None, \*\*kwargs])*

    :param x: object returned by :py:func:`cluster`
    :type x: :py:class:`ClusterOutput`
    :param variables: a list of variable names or indices to plot.
    :type variables: list[str], list[int],  **default** = all
    :param bins: number of bins for the histogram
    :type bins: int, **default** = 10
    :param show: see :py:func:`plot`
    :type show: bool, **default** = True
    :param criterion: it selects the "best result" bound to this criterion \
    when **x** is the result of a multicriteria clustering.
    :type criterion: :ref:`gm.CriterionName<gmCN>`
    :param kwargs\*\*: further arguments are passed to **matplotlib**    
    :return: a `matplotlib <http://matplotlib.org>`_ figure object
    :rtype: `matplotlib.figure.Figure <http://matplotlib.org/api/figure_api.html>`_        
    """
    x.hist(*args, **kwargs)
"""
    .. admonition:: Signature
        :class: note
    
            *fig = mixmod.barplot(x, [variables, colors, show=True, \*\*kwargs])*

            or (as a :py:class:`ClusterOutput` method):

            *fig = x.barplot([variables, colors, show=True, \*\*kwargs])*

"""

def barplot(x, *args, **kwargs):
    """
    :Description: Builds and displays the barplot of qualitative data  \
        provided by a :py:class:`ClusterOutput` instance (i.e. **x** \
        parameter). It's implementation is based on \
        `matplotlib <http://matplotlib.org>`_. It uses information provided by \
        :ref:`x.best_result.parameters<result_class_var>` to plot probablities \
        of modalities.

    .. admonition:: Signature
        :class: note

            *fig = mixmod.barplot(x, [list : variables, colors, show=True, criterion=None, \*\*kwargs])*
            

    :param x: object returned by :py:func:`cluster`
    :type x: :py:class:`ClusterOutput`
    :param variables: a list of variable names or indices to plot.
    :type variables: list[str], list[int],  **default** = all
    :param colors: list of colors to be used instead of default colors. \
    Colors encoding must be `matplotlib <http://matplotlib.org>`_ compliant \
    (see http://matplotlib.org/api/colors_api.html). Relevant only for \
    qualitative data.    
    :type colors: list[str]
    :param show: when set to **False** the result is not displayed. Useful when the function is called  only in order to obtain the returned object (e.g. for a later use with plotly)
    :type show: bool, **default** = True
    :param criterion: it selects the "best result" bound to this criterion \
    when **x** is the result of a multicriteria clustering.
    :type criterion: :ref:`gm.CriterionName<gmCN>`    
    :param kwargs\*\*: further arguments are passed to **matplotlib**    
    :return: a `matplotlib <http://matplotlib.org>`_ figure object
    :rtype: `matplotlib.figure.Figure <http://matplotlib.org/api/figure_api.html>`_        
    """
    x.barplot(*args, **kwargs)

    
cdef class LearnOutput(Output):
    """
    :Description: This class defines the type returned by the \
    :py:func:`learn` function. It inherits all features of \
    :py:class:`Output` class and dditionally it defines specific features for \
    :py:func:`learn` objects.
    
    .. admonition:: Constructor
        :class: warning

        Though **LearnOutput** is instanciable, its instanciation is \
        dedicated to the API so it's not recomended to instanciate it in your \
        own programs.
        
    :var results: provides the list of results for all configurations
    :vartype results: list[:py:class:`LearnResult`]
    :var best_result: the result of the best configuration (for the first \
    criterion)
    
    :vartype best_result: :py:class:`LearnResult`
    :var nb_cv_block: see :py:func:`learn`
    """    
    cdef readonly nb_cv_block
    def __cinit__(self, data, nb_cluster, known_labels, nb_cv_block , criterion,
                   models, data_type, weight, factor, results, best_result,
                  ordered_by=None, error=False):
        self.data = data
        self.nb_cluster = nb_cluster
        self.known_labels = known_labels
        self.nb_cv_block = nb_cv_block
        self.criterion = criterion
        self.models = models
        self.data_type = data_type
        self.weight = weight
        self.factor = factor
        Output.set_results(self, results, best_result)        
        ## self.results = results
        ## self.best_result = best_result
        self.ordered_by = ordered_by     
        self.error = error
    def __reduce__(self):
        return LearnOutput, (self.data, self.nb_cluster, self.known_labels,
                             self.nb_cv_block , self.criterion, self.models,
                             self.data_type, self.weight, self.factor,
                             self.results, self.best_result, self.ordered_by,
                             self.error)
    def write_delta(self, out):
        out.write("nb_cv_block: {}".format(self.nb_cv_block))
    def __str__(self):
        return self.dump()        
    def dump(self, summary=False):
        out = StringIO()
        out.write("****************************************\n")
        out.write("*** INPUT:\n")
        out.write("****************************************\n")
        self.to_str(out, summary=summary)
        if not self.error:        
            out.write("\n\n")
            out.write("****************************************\n")
            out.write("*** BEST MODEL OUTPUT:\n")
            out.write("*** According to the {} criterion\n".format(
                self.criterion[0].name))
            out.write("****************************************\n")            
            # best result
            self.default_best_result.to_str(out)
            out.write("****************************************\n")            
        res = out.getvalue()
        out.close()
        return res
    def summary(self):
        """
        Returns a displayable string giving the main information
        about the object
        """        
        return self.dump(summary=True)

cdef class PredictOutput(object):
    """
    :Description: This class defines the type returned by the \
    :py:func:`predict` function. 
    
    .. admonition:: Constructor
        :class: warning

        Though **PredictOutput** is instanciable, its instanciation is \
        dedicated to the API so it's not recomended to instanciate it in your \
        own programs.
        
        
    :var data: see :py:func:`predict`
    :type data:  numpy.ndarray, pandas.DataFrame
    :var nb_sample: number of individuals
    :vartype nb_sample: int
    :var nb_variable: number of variables
    :vartype nb_variable: int
    :var error: error code
    :var classification_rule: object giving the classification rule
    :vartype classification_rule:  :py:class:`Result`
    :var partition: integer list providing the labels assigned to individuals \
    by :py:func:`predict`
    :vartype partition: list[int]
    :var proba: matrix holding the probabilities for individuals to be assigned to a class
    :vartype proba: list[list[float]]
    """    
    cdef readonly data, data_type, nb_sample, nb_variable
    cdef readonly error, classification_rule,partition, proba
    def __cinit__(self, data, data_type, nb_sample, nb_variable, error,
                  classification_rule, partition, proba):
        self.data = data
        self.data_type = data_type
        self.nb_sample = nb_sample
        self.nb_variable = nb_variable
        self.error = error 
        self.classification_rule = classification_rule
        self.partition = partition
        self.proba = proba
    def __reduce__(self):
        return PredictOutput, (self.data, self.data_type, self.nb_sample,
                               self.nb_variable, self.error,
                               self.classification_rule, self.partition,
                               self.proba)
    def data_to_str(self, out, summary=True):
        nb_sample, nb_var = self.data.shape
        if summary:
            nb_row = min(nb_sample, 10)
            nb_col = min(nb_var,10)
            out.write("* data (limited to a 10x10 matrix) =\n")
        else:
            nb_row = nb_sample
            nb_col = nb_var
            out.write("* data =\n")
        if  isinstance(self.data, pnd.core.frame.DataFrame):
            data_ix = self.data.iloc
        else:
            data_ix = self.data
        
        data = pnd.DataFrame(data_ix[:nb_row,:nb_col]) #,index=range(1,nb_row+1))        
        out.write(data.to_string(header=False))
        out.write("\n* ... ...\n")  
     
    def dump(self, summary=False):
        out = StringIO()
        out.write("****************************************\n")
        out.write("*** INPUT:\n")
        out.write("****************************************\n")
        out.write(str(self.classification_rule))
        self.data_to_str(out, summary=summary)
        if not self.error:        
            out.write("\n\n")
            out.write("****************************************\n")
            out.write("*** PREDICTION:\n")
            out.write("* partition =")
            write_list(self.partition, out)
            data = pnd.DataFrame(self.proba)
            nn, _ = data.shape
            s_proba = "* probabilities = "
            b_proba = " "*len(s_proba)
            for j, el in enumerate(data.to_string(header=False,
                        index=False,
                        float_format = '{:,.4f}'.format).split('\n')):
                out.write("{}|{}|\n".format(b_proba if j else s_proba, el))
        res = out.getvalue()
        out.close()
        return res
    def summary(self):
        """
        Returns a displayable string giving the main information
        about the object
        """
        return self.dump(summary=True)
    def __str__(self):
        return self.dump()        
 

cdef class _Cluster:
    cdef readonly data, nb_cluster, data_type
    cdef readonly models, strategy, criterion, weight, known_labels
    def __cinit__(self, data,
                 nb_cluster, 
                 data_type=None, 
                 models=None, 
                 strategy=None, 
                 criterion=[gm.default_criterion_name],
                 weight=None, 
                 known_labels=None):
        """
        Cluster constructor
        """
        if is_positive_int(nb_cluster):
            self.nb_cluster = [nb_cluster]
        elif isinstance(nb_cluster, list):
            for n in nb_cluster:
                if not is_positive_int(n):
                    raise ValueError("nb_cluster must be a positive int.")
            self.nb_cluster = nb_cluster
        else:
            raise ValueError("nb_cluster must be a [list of] positive int.")
        inferred_dtype, allowed_dtypes = type_of(data)
        if data.ndim != 2:
            raise ValueError("data  must be a bi-dimesional matrix")
        model_dtype = None if models is None else check_models(models) #data_type_from_model(models)
        if model_dtype and model_dtype not in allowed_dtypes:
            raise ValueError("Type doensn't match between model ({}) and data ({})".format(model_dtype, allowed_dtypes))
        if data_type is None:
            self.data_type = model_dtype if model_dtype else inferred_dtype
        elif data_type not in gm.DataType:
            raise ValueError("unknown data_type {}".format(data_type))
        elif data_type not in allowed_dtypes:
            raise ValueError(
                "data_type {} does not match with data. Allowed types:{}".
                format(data_type,
                       [dt.name for dt in list(allowed_dtypes)]))
        elif model_dtype and model_dtype != data_type:
            raise ValueError("Type doensn't match between model ({}) and required type ({})".format(model_dtype, data_type))
        else:
            self.data_type = data_type
        self.data = data        
        self.models = models #if models is None else models()
        self.strategy = strategy if strategy else Strategy()
        if self.strategy.init.name in [gm.PARAMETER, gm.LABEL] and len(self.nb_cluster)>1:
            raise ValueError("gm.PARAMETER and gm.LABEL initialisations require nbCluster to be mono-valued!")
        if criterion in gm.valid_cluster_criterion:
            self.criterion = [criterion]
        elif not isinstance(criterion, list) or not criterion:
            raise ValueError("Unknown criterion: {}".format(criterion))
        else: 
            for elt in criterion:
                if elt not in gm.valid_cluster_criterion:
                    raise ValueError("Unknown criterion: {}".format(elt))
            self.criterion = criterion
        if not weight is None:
            if not is_positive_int_iter(weight):
                raise ValueError("weight must be an array-like of integers")
            if len(weight) != data.shape[0]:
                raise ValueError("weight size ({}) does not match the data size ({})",len(weight), data.shape[0])
        self.weight = weight
        if not known_labels is None:
            if not is_positive_int(nb_cluster):
                raise ValueError("more than one cluster, known_labels can be used only with one number of cluster!")
            self.known_labels = check_known_labels(known_labels, data.shape[0])
            if max(self.known_labels) > nb_cluster:
                raise ValueError("more than one cluster, known_labels can be used only with one number of cluster!")
        else:
            self.known_labels =  known_labels # i.e. None
    
    def run(self):
        builder = ClusteringBuilder(self) # cbuilder.pxi
        builder.process_input()        
        builder.set_algo()        
        builder.set_init_algo()        
        builder.set_criterion()        
        builder.set_model()        
        builder.set_weight()        
        builder.set_known_partition()        
        builder.finalize()        
        builder.main_run()        
        return builder.get_output()

#http://thomas-cokelaer.info/tutorials/sphinx/docstring_python.html#template.MainClass1.function1


def cluster(*args, **kwargs):
    """
    :Description:

     This function computes an optimal mixture model according to the provided \
     criteria and the list of model defined in  :py:class:`Model`, 
     using the algorithm specified in :py:class:`Strategy` .

    .. admonition:: Signature
        :class: note

            *cluster_output = mixmod.cluster(data, nb_cluster, [data_type, models, \
            strategy, criterion, weight, known_labels])*

    .. _cluster_fun_params:
    
    :param data: 2-dimension input data. Either *numpy.ndarray* \
    or *pandas. DataFrame* inputs are accepted for quantitative data, whereas \
    *pandas.DataFrame* type is required for qualitative or heterogeneous \
    input data. Rows represent observations and columns represent variables. 
    :type data:  numpy.ndarray, pandas.DataFrame
    :param nb_cluster: number of clusters [#int_plus]_.
    :type nb_cluster: int+, list[int+]
    :param data_type: There are 3 possible values: \
    :ref:`gm.QUALITATIVE<gmDT>`, :ref:`gm.QUANTITATIVE<gmDT>` or :ref:`gm.HETEROGENEOUS<gmDT>` \
    [#dt_shortcut_fnot]_ .  Set to **None** by default, type will be inferred \
    from the variables type and the model type (when provided).
    :type data_type: :ref:`gm.DataType<gmDT>`
    :param models: defines the list of models to run. Default model depends on data type:
    
        +-------------+--------------------------------------------+-------------------------------------+
        |Data type    |Default model                               |See also(for specifying other models)|
        +=============+============================================+=====================================+
        |quantitative |:ref:`gm.Gaussian_pk_Lk_Ce<gmMN>`           |:py:func:`gaussian_model`            |
        +-------------+--------------------------------------------+-------------------------------------+
        |qualitative  |:ref:`gm.Binary_pk_Ekjhe<gmMN>`             |:py:func:`multinomial_model`         |
        +-------------+--------------------------------------------+-------------------------------------+
        |composite    |:ref:`gm.Heterogeneous_pk_Ekjh_Lk_Bke<gmMN>`|:py:func:`composite_model`           |
        +-------------+--------------------------------------------+-------------------------------------+

    :type models: list[:ref:`gm.ModelName<gmMN>`]
    :param strategy: the strategy to run. The default value is provided by the \
    :py:func:`strategy` function.
    :type strategy: :py:class:`Strategy`
    :param criterion:  defines the criterion/criteria to select the best model. \
    The best model is the one with the lowest criterion value. \
    Possible items: *gm.BIC*, *gm.ICL*, *gm.NEC* [#crit_shortcut_fnot]_ .
    :type criterion: :ref:`gm.CriterionName<gmCN>`, list[:ref:`gm.CriterionName<gmCN>`], **default** = **gm.BIC**
    :param weight: numeric vector [#int_plus]_, it's size equals the data row number.\
    It is optionnal and it's to be used when weight is associated \
    to the data.
    :type weight: list[int+], numpy.ndarray[int+],... 
    :param known_labels: numeric vector [#int_plus]_, it's size equals the data row number. It is used for \
    semi-supervised classification when labels are known. Each cell \
    corresponds to a cluster affectation (**see note:** [#known_labels_footnote]_).
    :type known_labels: pandas.Categorical, numpy.array(int+), list[int+]

    :return: The returned object has two attributes containing the results :
    
        * **results:** a list of :py:class:`Result` objects containing\
        **all the results** sorted in ascending order according to the given \
        criterion when clustering is monocriterion otherwise a dictionary of \
        sorted results for all criteria ( see :py:class:`ClusterOutput` ).
        * **best_result:**  the :py:class:`Result` object containing the \
        **best model** results  when clustering is monocriterion otherwise a dictionary of \
        "best result" objects for all criteria ( see :py:class:`ClusterOutput` ).
 

    :rtype: :py:class:`ClusterOutput`

    .. rubric:: __

    .. [#int_plus] **int+** means here **positive integer** 

    .. [#dt_shortcut_fnot] *gm.QUANTITATIVE*, *gm.QUALITATIVE* and \
    gm.HETEROGENEOUS are shortcuts for *gm.DataType* enum items
    
    .. [#crit_shortcut_fnot] *gm.BIC*, *gm.ICL* etc. are shortcuts for \
    *gm.CriterionName* enum items
    
    .. [#known_labels_footnote] **known_labels** parameter is authorized only \
    if **nb_cluster** is mono-valued.
    """
    cluster_ = _Cluster(*args, **kwargs)
    return cluster_.run()


cdef class _Learn:
    cdef readonly data, nb_cluster, data_type, nb_cv_block
    cdef readonly models, strategy, criterion, weight, known_labels
    def __cinit__(self, data,
                 known_labels, 
                 data_type=None, 
                 models=None, 
                 criterion=None,
                 weight=None, 
                 nb_cv_block=None):
        """
        Learn object constructor
        """
        inferred_dtype, allowed_dtypes = type_of(data)
        if data.ndim != 2:
            raise ValueError("data  must be a bi-dimesional matrix")
        ####################
        model_dtype = None if models is None else check_models(models) #data_type_from_model(models)
        if model_dtype and model_dtype not in allowed_dtypes:
            raise ValueError("Type doensn't match between model ({}) and data ({})".format(model_dtype, allowed_dtypes))
        if data_type is None:
            self.data_type = model_dtype if model_dtype else inferred_dtype
        elif data_type not in gm.DataType:
            raise ValueError("unknown data_type {}".format(data_type))
        elif data_type not in allowed_dtypes:
            raise ValueError(
                "data_type {} does not match with data. Allowed types:{}".
                format(data_type,
                       [dt.name for dt in list(allowed_dtypes)]))
        elif model_dtype and model_dtype != data_type:
            raise ValueError("Type doensn't match between model ({}) and required type ({})".format(model_dtype, data_type))
        else:
            self.data_type = data_type

        ####################
        ## if data_type is None:
        ##     self.data_type = inferred_dtype
        ## elif data_type not in gm.DataType:
        ##     raise ValueError("unknown data_type {}".format(data_type))
        ## elif data_type not in allowed_dtypes:
        ##     raise ValueError(
        ##         "data_type {} does not match with data. Allowed types:{}".
        ##         format(data_type,
        ##                [dt.name for dt in list(allowed_dtypes)]))
        ## else:
        ##     self.data_type = data_type
        self.data = data        
        self.known_labels = check_known_labels(known_labels, data.shape[0])
        self.nb_cluster = np.max(self.known_labels)
        #self.models = check_model(models)
        self.models = models
        if criterion is None:
            self.criterion=[gm.default_learn_criterion_name]
        elif criterion in gm.valid_learn_criterion:
            self.criterion = [criterion]
        elif not isinstance(criterion, list) or not criterion:
            raise ValueError("Unknown criterion: {}".format(criterion))
        else: 
            for elt in criterion:
                if elt not in gm.valid_learn_criterion:
                    raise ValueError("Unknown criterion: {}".format(elt))
            self.criterion = criterion
        if weight is not None:
            check_weight(weight, data.shape[0])
            self.weight = weight
        if nb_cv_block is not None:
            if is_positive_int(nb_cv_block):
                if self.criterion != [gm.CV]:
                    raise ValueError("nb_cv_block is not compatible with the {} criterion".format(criterion))
                else:
                    self.nb_cv_block = nb_cv_block
            else:
                raise ValueError("nb_cv_block value is not valid")
        #else:
        #    self.nb_cv_block = 10
    
    def run(self):
        builder = LearningBuilder(self) # cbuilder.pxi
        builder.process_input()
        builder.set_criterion()
        builder.set_model()        
        builder.set_weight()        
        builder.set_nb_cv_block()
        builder.finalize()        
        builder.main_run()        
        return builder.get_output()


def learn(*args, **kwargs):
    """
    :Description: This function computes the first step of a discriminant analysis (its \
    purpose is to find the best classification rule by running an **M** step \
    from the training observations).
    
    .. admonition:: Signature
        :class: note
    
            *learn_output = mixmod.learn(data, known_labels, [data_type, models, \
            criterion, weight, nb_cv_block])*
    
    :param data: see **data** parameter on :ref:`cluster()<cluster_fun_params>`
    :type data:  numpy.ndarray, pandas.DataFrame
    :param known_labels: numeric vector [#int_plus]_, it's size equals the data row number. \
    Each cell corresponds to a cluster affectation (the max. value shows up \
    the number of clusters) .
    :type known_labels: pandas.Categorical, numpy.array(int+), list[int+]    
    :param data_type: see **data_type:** parameter on :ref:`cluster()<cluster_fun_params>`
    :type data_type: :ref:`gm.DataType<gmDT>`   
    :param models: see **models** parameter on :ref:`cluster()<cluster_fun_params>`
    :type models: list[:ref:`gm.ModelName<gmMN>`]
    :param criterion:  defines the criterion/criteria to select the best model. \
    The best model is the one with the lowest criterion value. \
    Possible items: *gm.CV* and *gm.BIC* [#crit_shortcut_fnot]_ .
    :type criterion: :ref:`gm.CriterionName<gmCN>`, list[:ref:`gm.CriterionName<gmCN>`], **default** = **gm.CV**
    :param weight: see **weight** parameter on :ref:`cluster()<cluster_fun_params>`
    :type weight: list[int+], numpy.ndarray[int+],... 
    :param nb_cv_block: defines the number of block to perform the cross validation. Ignored if criterion!=gm.CV. Default value is 10.
    :type nb_cv_block: int+
    :return: The returned object has two attributes containing the results:
    
        * **results:** a list of :py:class:`LearnResult` objects containing\
        **all the results** sorted in ascending order according to the given \
        criterion.
        * **best_result:**  the :py:class:`LearnResult` object containing the \
        **best model** results.
    :rtype: :py:class:`LearnOutput`
    """
    learn_ = _Learn(*args, **kwargs)
    return learn_.run()

cdef class _Predict:
    """
    :Description: This function computes the second step of a discriminant analysis. The aim \
    of this step is to assign remaining observations to one of the groups.
    
    .. admonition:: Signature
        :class: note
    
            *predict_output = mixmod.predict(data, classification_rule)*
    
    :param data: 2-dimension input data to reclassify (quantitative or qualitative). Either *numpy.ndarray* \
    or *pandas. DataFrame* inputs are accepted for quantitative data, whereas \
    *pandas.DataFrame* type is required for qualitative \
    input data. Rows represent observations and columns represent variables. 
    :type data:  numpy.ndarray, pandas.DataFrame
    :param classification_rule: object containing  the classification rule \
    computed by :py:func:`learn` (i.e. the **best_result** \
    attribute value of the object returned by :py:func:`learn`)
    :type classification_rule: :py:class:`Result`
    :return: The returned object has two attributes containing the computed \
    results:
    
        * **partition:** assignation to groups of the processed observations.
        * **proba** probability of belonging to each group for every \
        observation.    
    :rtype:  :py:class:`PredictOutput`
    """    
    cdef readonly data, data_type, nb_variable, nb_sample, error
    cdef readonly classification_rule, partition, proba
    def __cinit__(self, data, classification_rule):
        _, allowed_dtypes = type_of(data)
        if data.ndim != 2:
            raise ValueError("data  must be a bi-dimesional matrix")
        if not isinstance(classification_rule, Result):
            raise ValueError("classification_rule  must be a Result Object")
        if isinstance(classification_rule.parameters, GaussianParameter):
            self.data_type = gm.QUANTITATIVE
        elif isinstance(classification_rule.parameters, MultinomialParameter):
            self.data_type = gm.QUALITATIVE                        
        elif isinstance(classification_rule.parameters, CompositeParameter):
            self.data_type = gm.HETEROGENEOUS
        else:
            raise ValueError("Unknown parameter type")
        if self.data_type not in allowed_dtypes:
            raise ValueError("data are not compatible with the classification rule parameters")
        self.data = data        
        self.classification_rule = classification_rule
        self. nb_sample = data.shape[0]
        self.nb_variable = data.shape[1]
    def run(self):
        builder = PredictBuilder(self) # cbuilder.pxi
        builder.process_input()
        builder.finalize()  
        builder.main_run()
        return builder.get_output()
            
def predict(*args, **kwargs):
    """
    :Description: This function computes the second step of a discriminant analysis. The aim \
    of this step is to assign remaining observations to one of the groups.
    
    .. admonition:: Signature
        :class: note
    
            *predict_output = mixmod.predict(data, classification_rule)*
    
    :param data: 2-dimension input data to reclassify (quantitative or qualitative). Either *numpy.ndarray* \
    or *pandas. DataFrame* inputs are accepted for quantitative data, whereas \
    *pandas.DataFrame* type is required for qualitative \
    input data. Rows represent observations and columns represent variables. 
    :type data:  numpy.ndarray, pandas.DataFrame
    :param classification_rule: object containing  the classification rule \
    computed by :py:func:`learn` (i.e. the **best_result** \
    attribute value of the object returned by :py:func:`learn`)
    :type classification_rule: :py:class:`Result`
    :return: The returned object has two attributes containing the computed \
    results:
    
        * **partition:** assignation to groups of the processed observations.
        * **proba** probability of belonging to each group for every \
        observation.    
    :rtype:  :py:class:`PredictOutput`
    """    
    predict_ = _Predict(*args, **kwargs)
    return predict_.run()

