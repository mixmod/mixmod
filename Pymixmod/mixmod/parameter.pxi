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

cdef class Parameter(object):
    """
    :Description: Abstract base class for parameter description

    .. admonition:: Constructor
        :class: warning

        This is an abstract class, so instanciate it directly is not a good \
        idea ...

    :var proportions: nb_cluster sized list, the sum of proportions is **1**
    :vartype proportions: list[float]    
    """
    cdef readonly proportions, nb_free_param
    def __init__(self, proportions, nb_free_param=None):
        self.proportions = proportions
        self.nb_free_param = nb_free_param


cdef class GaussianParameter(Parameter):
    """
    :Description: Gaussian parameter definition. It inherits all features of \
    :py:class:`Parameter` class and additionally it defines specific \
    features.

    .. admonition:: Constructor
        :class: note

        par = GaussianParameter(proportions, mean, variance)

    :var proportions: see :py:class:`Parameter`
    :var mean: means matrix (nb_cluster * nb_variable sized)
    :vartype mean: numpy.ndarray
    :var variance: list of float matrices (nb_cluster * nb_variable sized)
    :vartype variance: list[numpy.ndarray]
    """    
    cdef readonly mean, variance
    def __init__(self, proportions, mean, variance, nb_free_param=None):
        self.proportions = proportions
        self.nb_free_param = nb_free_param        
        self.mean = mean
        self.variance = variance

    
    def __str__(self):
        out = StringIO()        
        if len(self.proportions):
            out.write("****************************************\n")
            for i, prop in enumerate(self.proportions):
                out.write("*** Cluster {}\n".format(i+1))
                out.write("* proportion = {:1.4f}\n".format(prop))
                out.write("* means      =")
                write_list_float(self.mean[i], out)
                data = pnd.DataFrame(self.variance[i]) #,index=range(1,nb_row+1))
                nn, _ = data.shape
                s_variance = "* variances  = "
                b_variance = " "*len(s_variance)
                for j, el in enumerate(data.to_string(header=False,
                                                      index=False,
                                                      float_format = '{:,.4f}'.\
                                                      format).split('\n')):
                    out.write("{}|{}|\n".
                              format(b_variance if j else s_variance, el))
                
            out.write("****************************************\n")
            out.write("\n")
        res = out.getvalue()
        out.close()
        return res
    def __reduce__(self):
        return GaussianParameter, (self.proportions, self.mean, self.variance, self.nb_free_param)


cdef class MultinomialParameter(Parameter):
    """
    :Description: Multinomial parameter definition. It inherits all features \
    of :py:class:`Parameter` class and additionally it defines \
    specific features.

    .. admonition:: Constructor
        :class: note

        par = MultinomialParameter(proportions, center, scatter, factor)

    :var proportions: see :py:class:`Parameter`
    :var center:  nb_cluster * nb_variable sized matrix of integers (list of lists, actually)
    :vartype center: list[list[int]]
    :var scatter:  list of float matrices
    :vartype scatter:  list[numpy.ndarray]
    :var factor: number of modalities for qualitative variables
    :vartype factor: list[int]
    """    
    cdef readonly center, scatter, factor
    def __init__(self, proportions, center, scatter, factor, nb_free_param=None):
        self.proportions = proportions
        self.nb_free_param = nb_free_param        
        self.center = center
        self.scatter = scatter
        self.factor = factor        
    def __str__(self):
        out = StringIO()        
        if len(self.proportions):
            out.write("****************************************\n")
            out.write("* number of modalities =")
            write_list(self.factor, out)
            for i, prop in enumerate(self.proportions):
                out.write("*** Cluster {}\n".format(i+1))
                out.write("* proportion = {:1.4f}\n".format(prop))
                out.write("* center     =")
                write_list(self.center[i], out)
                data = pnd.DataFrame(self.scatter[i]) #,index=range(1,nb_row+1))
                nn, _ = data.shape
                s_scatter = "* scatter    = "
                b_scatter = " "*len(s_scatter)
                for j, el in enumerate(
                        data.to_string(header=False,
                                       index=False,
                                       float_format = '{:,.4f}'.format).\
                        split('\n')):
                    out.write("{}|{}|\n".\
                              format(b_scatter if j else s_scatter, el))
                
            out.write("****************************************\n")
            out.write("\n")
        res = out.getvalue()
        out.close()
        return res
    def __reduce__(self):
        return MultinomialParameter, (self.proportions, self.center,
                                      self.scatter, self.factor, self.nb_free_param)
    
cdef class CompositeParameter(object):
    """
    :Description: This class groups together a gaussian parameter and a \
    multinomial parameter

    .. admonition:: Constructor
        :class: note

        par = CompositeParameter(m_parameter, g_parameter, proportions, factor)

    :var m_parameter: multinomial parameter
    :var g_parameter: gaussian parameter
    :var proportions: nb_cluster sized list, the sum of proportions is **1**
    :vartype proportions: list[float]
    :var factor: number of modalities for qualitative variables
    :vartype factor: list[int]
    """    
    cdef readonly m_parameter, g_parameter, factor, proportions, nb_free_param
    def __init__(self, m_parameter, g_parameter, proportions, factor, nb_free_param=None):
        self.m_parameter = m_parameter
        self.g_parameter = g_parameter
        self.proportions = proportions
        self.nb_free_param = nb_free_param        
        self.factor = factor
    def __str__(self):
        out = StringIO()        
        out.write("Gaussian Parameters\n")        
        out.write(str(self.g_parameter))
        out.write("Multinomial Parameters\n")
        out.write(str(self.m_parameter))
        res = out.getvalue()
        out.close()
        return res
    def __reduce__(self):
        return CompositeParameter, (self.m_parameter, self.g_parameter,
                                    self.proportions, self.factor, self.nb_free_param)
