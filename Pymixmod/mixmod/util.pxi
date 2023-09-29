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

def is_positive_int(n):
    if isinstance(n,numbers.Integral):
        return n>0
    return False

def is_index(n):
    if isinstance(n,numbers.Integral):
        return n>=0
    return False

def is_iterable(obj):
    try:
        _ = iter(obj)
    except TypeError:
        return False
    return True

def is_positive_int_iter(iter_):
    if not is_iterable(iter_):
        return False
    for n in iter_:
        if not  is_positive_int(n):
            return False
    return True

def is_index_iter(iter_):
    if not is_iterable(iter_):
        return False
    for n in iter_:
        if not  is_index(n):
            return False
    return True

def is_dataframe(data):
    return isinstance(data, pd.core.frame.DataFrame)




def write_list(x,o):
    if is_iterable(x):
        for e in x:
            o.write(" {}".format(e))
        o.write("\n")
    else:
        o.write(" {}\n".format(x))

def write_list_float(lst,o, d=4):
    fmt = " {:1."+str(d)+"f}"
    for e in lst:
        o.write(fmt.format(e))
    o.write("\n")

def is_float(f):
    return isinstance(f, float)

def check_known_labels(kl, size):
    if isinstance(kl, pd.core.series.Series):
        if kl.size != size:
            raise ValueError("Weight must be a {} sized vector".format(size))
        if kl.dtype.name != 'category':
            kl = kl.astype('category')
        return np.array(kl.cat.codes,dtype=np.int64) + 1
    elif not isinstance(kl, np.ndarray):
        kl = np.array(kl)
    if kl.shape != (size,):
        raise ValueError("Weight must be a {} sized vector".format(size))
    if kl.dtype.name != 'int64':
        raise ValueError("Weight elements must be integers")
    return kl

EPSILON = 0.00001

def check_weight(w8, size):
    if  not isinstance(w8, np.ndarray) or w8.dtype != np.float64:
        w8 = np.array(w8,dtype=np.float64)
    if w8.shape != (size,):
        raise ValueError("Weight must be a {} sized vector".format(size))
    if w8.min() < 0:
        raise ValueError("Weight elements must be positive")
    if np.abs(np.abs(w8.sum()) - 1) > EPSILON:
        raise ValueError("The sum of weight elements must be 1")
    return w8

def is_included(sublist, list_):
    for e in sublist:
        if e not in list_:
            return False
    return True




def type_of(data):
    """
    returns a 2 values tuple:
    1st value: the inferred datatype, it is to be used if no datatype is specified
    2nd value: a list of compatible datatypes
    """
    if  isinstance(data, np.ndarray):
        if data.dtype.name == 'float64':
            return  gm.QUANTITATIVE, [gm.QUANTITATIVE]
        elif data.dtype.name == 'int64':
            return  gm.QUALITATIVE, [gm.QUALITATIVE, gm.QUANTITATIVE]
        else:
            raise ValueError("numpy.ndarray data must be numerical.\n"
                             "For heterogeneous data use pandas DataFrames")
    elif not isinstance(data, pd.core.frame.DataFrame):
        raise ValueError("Data must be a pandas dataframe or a numpy.ndarray")
    # dataframe case
    type_set = set((data[e].dtype.name for e in data.columns))
    if type_set == set(['float64']):
        return  gm.QUANTITATIVE, [gm.QUANTITATIVE]
    elif type_set == set(['int64']):
        return  gm.QUALITATIVE, [gm.QUALITATIVE, gm.QUANTITATIVE]
    elif type_set == set(['category']):
        return  gm.QUALITATIVE, [gm.QUALITATIVE]
    elif type_set == set(['int64', 'float64']):
        return  gm.QUANTITATIVE, [gm.HETEROGENEOUS, gm.QUANTITATIVE]

    elif 'category' in type_set:
        return gm.HETEROGENEOUS, [gm.HETEROGENEOUS]
    else:
        return  gm.QUALITATIVE, [gm.QUALITATIVE]


def as_dataframe(data):
    if isinstance(data, pd.core.frame.DataFrame):
        return data
    if  isinstance(data, np.ndarray):
        return pd.DataFrame(data)
    raise ValueError("Cannot convert data to DataFrame")

def matrix2binary(data):
    """

    """
    res = {}
    nb_lig, nb_col = data.shape
    for k in data.columns:
        if data[k].dtype.name != 'category':
            data[k]=data[k].astype('category')
    new_cols = []
    for k in data.columns:
        cts = data[k].cat.categories
        nb_cat = len(cts)
        mx = np.zeros([nb_lig, nb_cat],dtype=int);
        for i, j in enumerate(data[k].cat.codes):
            mx[i,j] = 1
        for i in range(nb_cat):
            k_i = "{}{}".format(k,cts[i])
            res[k_i]=mx[:,i]
            new_cols.append(k_i)
    return pd.DataFrame(res, columns=new_cols)

def header_to_categories(data):
    """
    Only for running the provided examples!
    """
    if not isinstance(data,pd.core.frame.DataFrame):
        raise ValueError("Data must be a pandas dataframe")
    for k in data.columns:
        if data[k].dtype.name == 'category':
            continue
        if k[0] != 'B':
            continue
        factor = int(k[1])
        data[k] = data[k].astype('category')
