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

cdef mxm.GaussianData *data2gaussian(data):
    """
    Copy a Numpy ndarray or a Pandas dataframe to mixmod GaussianData
    """
    if  isinstance(data, pd.core.frame.DataFrame):
        data_ix = data.iloc
    else:
        data_ix = data
    cdef mxm.GaussianData *g_data
    cdef double **matrix
    cdef int nb_sample = data.shape[0]
    cdef int nb_var = data.shape[1]
    matrix =  <double**>malloc(nb_sample*sizeof(double*))
    #matrix[0] = <double*>data.data
    for i in range(nb_sample):
        matrix[i] = <double*>malloc(nb_var*sizeof(double))
        for j in range(nb_var):
            matrix[i][j] = data_ix[i,j]
    g_data = new mxm.GaussianData(nb_sample, nb_var, matrix)
    for i in range(nb_sample):
        free(matrix[i])
    free(matrix)
    return g_data


cdef mxm.BinaryData *data2binary(data):
    """
    Copy a Numpy ndarray or a Pandas dataframe to mixmod BinaryData
    """
    if not isinstance(data,pd.core.frame.DataFrame):
        raise ValueError("Data must be a pandas dataframe")
    #if isinstance(data, np.ndarray): to be done
    cdef mxm.BinaryData *b_data
    cdef int64_t **matrix
    cdef int nb_sample = data.shape[0]
    cdef int nb_var = data.shape[1]
    cdef vector[int64_t] nb_modality
    tmp_mx = [] #np.empty([nb_sample, nb_var], dtype=np.int64)
    for k in data.columns:
        if data[k].dtype.name != 'category':
            #data[k]=data[k].astype('category')
            raise ValueError("Data must be categorical")
    #for k in data.columns:
        e = data[k].cat.categories
        nb_modality.push_back(len(e))
        tmp_vec = np.empty(nb_sample, dtype=np.int64)
        tmp_vec = data[k].cat.codes
        tmp_mx.append(tmp_vec)
        #tmp_mx[:,k] = data[k].cat.codes
    matrix =  <int64_t**>malloc(nb_sample*sizeof(int64_t*))
    for i in range(nb_sample):
        matrix[i] = <int64_t*>malloc(nb_var*sizeof(int64_t))
        for j in range(nb_var):
            #matrix[i][j] = data.iloc[i,j]
            matrix[i][j] = 1  + tmp_mx[j][i] #data.iloc[:,j].cat.codes[i]
    b_data = new mxm.BinaryData(nb_sample, nb_var, nb_modality, matrix)
    for i in range(nb_sample):
        free(matrix[i])
    free(matrix)
    return b_data

cdef mxm.CompositeData *data2composite(data):
    """
    Copy a Numpy ndarray or a Pandas dataframe to mixmod BinaryData
    """
    cdef mxm.GaussianData *g_data
    cdef double **g_matrix
    cdef mxm.BinaryData *b_data
    cdef int64_t **b_matrix
    cdef mxm.CompositeData *c_data
    cdef int nb_sample = data.shape[0]
    cdef int nb_col = data.shape[1]
    cdef int nb_col_gauss = 0, nb_col_bin = 0
    cdef vector[int64_t] nb_modality
    factor = []
    tmp_mx = []
    for k in data.columns:
        if data[k].dtype.name != 'category':
            factor.append(0)
        else:
            e = data[k].cat.categories
            factor.append(len(e))
            tmp_vec = np.empty(nb_sample, dtype=np.int64)
            tmp_vec = data.loc[:,k].cat.codes
            tmp_mx.append(tmp_vec)
    for i in range(nb_col):
        if factor[i]:
            nb_col_bin += 1
        else:
            nb_col_gauss += 1
    g_matrix =  <double**>malloc(nb_sample*sizeof(double*))
    b_matrix =  <int64_t**>malloc(nb_sample*sizeof(int64_t*))
    for i in range(nb_sample):
        g_matrix[i] = <double*>malloc(nb_col_gauss*sizeof(double))
        b_matrix[i] = <int64_t*>malloc(nb_col_bin*sizeof(int64_t))
        g_j = 0
        b_j = 0
        for j in range(nb_col):
            if factor[j]:
                b_matrix[i][b_j] = 1 + tmp_mx[j][i] #data.iloc[:,j].cat.codes[i]
                nb_modality.push_back(factor[j])
                b_j += 1
            else:
                g_matrix[i][g_j] = data.iloc[i,j]
                g_j += 1
    g_data = new mxm.GaussianData(nb_sample, nb_col_gauss, g_matrix)
    b_data = new mxm.BinaryData(nb_sample, nb_col_bin, nb_modality, b_matrix)
    c_data = new mxm.CompositeData(<mxm.Data*>b_data, <mxm.Data*>g_data)
    for i in range(nb_sample):
        free(g_matrix[i])
    free(g_matrix)
    for i in range(nb_sample):
        free(b_matrix[i])
    free(b_matrix)

    return c_data

cdef c_matrix2ndarray(int nb_sample, int pb_dim,  double **matrix):
    """
    matrix to numpy.ndarray conversion
    """
    mx_out = np.empty([nb_sample, pb_dim])
    for i in range(nb_sample):
        for j in range(pb_dim):
            mx_out[i,j] = matrix[i][j]
    return mx_out

cdef c_matrix2ndarray_int(int nb_sample, int pb_dim,  int64_t **matrix):
    """
    matrix to numpy.ndarray conversion
    """
    mx_out = np.empty([nb_sample, pb_dim],dtype=int)
    for i in range(nb_sample):
        for j in range(pb_dim):
            mx_out[i,j] = matrix[i][j]
    return mx_out



## """
## double ** RcppMatrixToC2DArray(Rcpp::NumericMatrix& in)
## {
##   // get the vector dimension
##   int nrow = in.nrow();
##   int ncol = in.ncol();

##   // allocate columns
##   double ** out = new double * [nrow];
##   for (int i=0; i<nrow; i++)
##   {
##     // allocate rows
##     out[i] = new double[ncol];
##     // get values
##     for (int j=0; j<ncol; j++)
##     {
##       out[i][j] = in(i,j);
##     }
##   }
##   // return C matrix
##   return out;
## }
## """

cdef double* list_to_c_vector(list_):
    len_ = len(list_)
    cdef double *result = new_double_array(len_)
    for i, elt in enumerate(list_):
        result[i] = elt
    return result

cdef int64_t* list_to_c_int_64_t_vector(list_):
    len_ = len(list_)
    cdef int64_t *result = new_int64_t_array(len_)
    for i, elt in enumerate(list_):
        result[i] = elt
    return result

cdef double **ndarray_to_c_matrix(mx):
    nb_row, nb_col = mx.shape
    cdef double ** result = new_double_p_array(nb_row)
    for i in range(nb_row):
        result[i] = new_double_array(nb_col)
        for j in range(nb_col):
            result[i][j] = mx[i, j]
    return result

cdef double ***list_of_ndarray_to_c_matrix(list_of_mx):
    len_ = len(list_of_mx)
    cdef double ***result = new_double_pp_array(len_)
    for i, mx in enumerate(list_of_mx):
        result[i] = ndarray_to_c_matrix(mx)
    return result

## """
## double *** RcppListOfMatrixToC3DArray(Rcpp::List& in)
## {
##   // get the vector dimension
##   int size = in.size();

##   // allocate first dimension
##   double *** out = new double ** [size];

##   // loop over list
##   for (int k=0; k<size; k++)
##   {
##     Rcpp::NumericMatrix mat = SEXP(in[k]);

##     // get dimensions
##     int nrow = mat.nrow();
##     int ncol = mat.ncol();

##     // allocate rows
##     out[k] = new double * [nrow];

##     for (int i=0; i<nrow; i++)
##     {
##       // allocate rows
##       out[k][i] = new double[ncol];
##       // get values
##       for (int j=0; j<ncol; j++)
##       {
##         out[k][i][j] = mat(i,j);
##       }
##     }
##   }

##   // return C matrix
##   return out;
## }


## }


## """
