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

cdef class Init(object):
    """
    :Description: Defines the parameters for the initiation step \
    of a strategy. Customarily, **Init** instances  are components of \
    :py:class:`Strategy` objects.

    .. admonition:: Constructor
        :class: note

            *init_output = mixmod.Init([name, nb_try, nb_iteration, epsilon])*

        **Parameters:** see :py:func:`init` function

        **NB:** An **Init** instance could be also obtained by calling \
        :py:func:`init` function


    :var name: defines the initialisation method
    :vartype name: :ref:`gm.StrategyInitName<gmSIN>`, **default** = gm.CEM_INIT
    :var nb_try: defines the number of tries in the initialisation step.
    :vartype nb_try: int+, **default** = 10
    :var nb_iteration: defines the number of iterations for the algorithm in \
    the initialisation step.
    :vartype nb_iteration: int+
    :var epsilon: defines the epsilon value in the initialization step.
    :vartype epsilon: float, **default** = 0.001
    :var parameter: see :py:func:`init`
    :var labels: see :py:func:`init`
    """
    cdef readonly name, nb_try, nb_iteration, epsilon, parameter, labels
    def __cinit__(self, name=gm.SMALL_EM, nb_try=10, nb_iteration=None,
                  epsilon=None, parameter=None, labels=None):
        """
        Init strategy constructor
        """
        if name not in gm.StrategyInitName:
            raise ValueError("Unknown init method: {}".format(name))
        self.name = name
        if name == gm.SMALL_EM or name == gm.CEM_INIT or name == gm.RANDOM:
            if not is_positive_int(nb_try):
                raise ValueError("Init.nb_try must be a positive integer")
        self.nb_try = nb_try
        if name == gm.SMALL_EM or name == gm.SEM_MAX:
            if nb_iteration is None:
                self.nb_iteration = 5 if name == gm.SMALL_EM else 100
            elif not is_positive_int(nb_iteration):
                raise ValueError("Init.nb_iteration must be a positive int.")
            else:
                self.nb_iteration = nb_iteration
        if name == gm.SMALL_EM:
            if epsilon is None:
                self.epsilon = 0.001
            elif not is_float(epsilon):
                raise ValueError("Init.epsilon must be a real.")
            elif epsilon < 0 or epsilon > 1:
                raise ValueError("Init.epsilon must be less than one and "
                                 "positive.")
            else:
                self.epsilon = epsilon
        else:
            if epsilon is not None:
                raise ValueError("epsilon is not allowed in initialization when"
                                 " initialization name is not gm.SMALL_EM")
        if name == gm.PARAMETER:
            if not isinstance(parameter, Parameter):
                raise ValueError("gm.PARAMETER initialisation requires a valid parameter.")
            self.parameter = parameter
        else:
            if parameter is not None:
                raise ValueError("parameter is not allowed with a gm.{} initialisation".format(name.name))
        if name == gm.LABEL:
            if not is_index_iter(labels):
                raise ValueError("gm.LABEL initialisation requires partition to be a vector of integers >=0.")
            self.labels = labels
        else:
            if labels is not None:
                raise ValueError("labels param. is not allowed with a gm.{} initialisation".format(name.name))
    def __reduce__(self):
        return Init, (self.name, self.nb_try, self.nb_iteration,
                      self.epsilon, self.parameter, self.labels)


def init(*args, **kwargs):
    """
    :Description: This function creates a :py:class:`Init` object, defining \
    the parameters for the initiation step of a strategy. The returned object \
    is used by :py:func:`strategy` function.

    .. admonition:: Signature
        :class: note

            *init_output = mixmod.init([name, nb_try, nb_iteration, epsilon])*

    :param name: defines the initialisation method
    :type name: :ref:`gm.StrategyInitName<gmSIN>`, **default** = gm.CEM_INIT
    :param nb_try: defines the number of tries in the initialisation step. \
    Available only if **name** parameter is  gm.SMALL_EM, \
    gm.CEM_INIT or gm.RANDOM
    :type nb_try: int+, **default** = 10
    :param nb_iteration: defines the number of iterations for the algorithm in \
    the initialisation step. Available only if **name** \
    parameter is gm.SMALL_EM or gm.SEM_MAX. The *default value** is 5 if \
    name == gm.SMALL_EM or 100 if name == gm.SEM_MAX
    :type nb_iteration: int+
    :param epsilon: defines the epsilon value in the initialization step. \
    Available only if name == gm.SMALL_EM
    :type epsilon: float, **default** = 0.001
    :param parameter: initiation with a user defined :py:class:`Parameter` \
    subclass instance. Mandatory if **name==gm.USER**, otherwise illegal.
    :type parameter: :py:class:`GaussianParameter`, :py:class:`MultinomialParameter`
    :param labels: vector containing integers (>=0)
    :type labels: list[int], numpy.array[int]
    :return: initialisation object
    :rtype: :py:class:`Init`
    """
    return Init(*args, **kwargs)


default_init = Init()

cdef class Algo(object):
    """
    :Description: Defines the algorithm with options to be run on a strategy. \
    An **Algo** object or a list of **Algo** objects is customarily used to \
    set the **algo** parameter for the :py:func:`strategy` \
    function or Strategy constructor.

    .. admonition:: Constructor
        :class: note

            init_output = mixmod.Algo([name, nb_iteration, epsilon])

        **Parameters:** see :py:func:`algo` function

        **NB:** An **Algo** instance could be also obtained by calling \
        :py:func:`algo` function

    :var name: algorithm name
    :vartype name: :ref:`gm.AlgoName<gmAN>`,  **default** = gm.EM
    :var nb_iteration: defines the number of iterations for the algorithm.
    :vartype nb_iteration: int+, **default** = 200
    :var epsilon: defines the epsilon value  (threshold value used \
    when the algorithm is wanted to be stopped at stationarity).
    :vartype epsilon: float, **default** = 0.001
    """
    cdef readonly name, nb_iteration, epsilon
    def __init__(self, name=gm.EM, nb_iteration=200, epsilon=0.001):
        if name not in gm.valid_algos:
            raise ValueError("Algo.name {} is not valid".format(name))
        self.name = name
        if not is_positive_int(nb_iteration):
            raise ValueError("Algo.nb_iteration must be a positive int.")
        self.nb_iteration = nb_iteration
        if not is_float(epsilon):
            raise ValueError("Algo.epsilon must be a real.")
        self.epsilon = epsilon
    def __str__(self):
        out = StringIO()
        out.write("{}\n".format(self.name.name))
        out.write("* number of iterations = {}\n".format(self.nb_iteration))
        out.write("* epsilon              = {}\n".format(self.epsilon))
        res = out.getvalue()
        out.close()
        return res

    def __iter__(self):
        yield self
    def __reduce__(self):
        return Algo, (self.name, self.nb_iteration, self.epsilon)

default_algo = Algo()

def algo(*args, **kwargs):
    """
    :Description: This function creates an :py:class:`Algo` object, \
    defining the algorithm with options to be run on a strategy. The returned \
    object or a list of **Algo** objects is customarily used to \
    set the **algo** parameter for the :py:func:`strategy`

    .. admonition:: Signature
        :class: note

            init_output = mixmod.algo([name, nb_iteration, epsilon])

    :param name: algorithm name
    :type name: :ref:`gm.AlgoName<gmAN>`,  **default** = gm.EM
    :param nb_iteration: defines the number of iterations for the algorithm.
    :type nb_iteration: int+, **default** = 200
    :param epsilon: defines the epsilon value. This is a threshold value used \
    when the algorithm is wanted to be stopped at stationarity. Available only \
    if **name** is **NOT** gm.SEM
    :type epsilon: float, **default** = 0.001
    :return: algorithm object
    :rtype: :py:class:`Algo`

    """
    return Algo(*args, **kwargs)

cdef class Strategy(object):
    """
    :Description: Its instances hold initialisation options and algorithms for clustering, accepted as **strategy** \
    parameter for :py:func:`cluster` function calls.

    .. admonition:: Constructor
        :class: note

        strategy_output = mixmod.Strategy([nb_try, init, algo])

        **Parameters:** see :py:func:`strategy` function

        **NB:** A **Strategy** instance could be also obtained by calling \
        :py:func:`strategy` function

    :var nb_try: defines the  number of repetitions of the strategy
    :vartype nb_try: int+, **default** = 1
    :var init: initialisation of the strategy
    :vartype init: :py:class:`Init`, **default** = :py:func:`init`
    :var algo: [list of] estimation algorithm[s]
    :vartype algo: :py:class:`Algo`, list[:py:class:`Algo`], \
    **default** = :py:func:`algo`
    """
    cdef readonly algo, init, nb_try, seed
    def __cinit__(self, algo=default_algo, init=default_init, nb_try=1, seed=-1):
        for a in algo:
            if not isinstance(a, Algo):
                raise ValueError("{} is not an Algo instance".format(a))
        self.algo = algo
        if not isinstance(init, Init):
            raise ValueError("{} is not an Init instance".format(init))
        self.init = init
        if not is_positive_int(nb_try):
            raise ValueError("Strategy.nb_try must be a positive int.")
        self.nb_try = nb_try
        if not isinstance(seed, numbers.Integral):
            raise ValueError("Strategy.seed must be an int.")
        self.seed = seed
        """
    def get_algo_name(self):
        out = StringIO()
        for a in self.algo:
            out.write(" {}".format(a.algo.name)
        res = out.getvalue()
        out.close()
        return res
        """
    def __str__(self):
        out = StringIO()
        out.write("****************************************\n")
        out.write("*** MIXMOD Strategy:\n")
        out.write("* number of tries      = {}\n".format(self.nb_try))
        for i, a in enumerate(self.algo):
            out.write("* algorithm{}         = ".format([i+1] if i else "   "))
            out.write(str(a))
        out.write("*** Initialization strategy:\n")
        out.write("* algorithm            = {}\n".format(self.init.name.name))
        out.write("* number of tries      = {}\n".format(self.init.nb_try))
        out.write("* number of iterations = {}\n".format(self.init.nb_iteration))
        out.write("* epsilon              = {}\n".format(self.init.epsilon))
        out.write("* seed                 = {}\n".format("NULL" if self.seed < 0 else self.seed))
        out.write("****************************************\n")
        res = out.getvalue()
        out.close()
        return res
    def __reduce__(self):
        return Strategy, (self.algo, self.init, self.nb_try, self.seed)





def strategy(*args, **kwargs):
    """
    :Description: This function creates a :py:class:`Strategy` \
    object, containing the initialisation options and algorithms. The returned \
    object is used by :py:func:`cluster` function.

    .. admonition:: Signature
        :class: note

            strategy_output = mixmod.strategy([nb_try, init, algo])

    :param nb_try: defines the  number of repetitions of the strategy
    :type nb_try: int+, **default** = 1
    :param init: initialisation of the strategy
    :type init: :py:class:`Init`, **default** = :py:func:`init`
    :param algo: [list of] estimation algorithm[s]
    :type algo: :py:class:`Algo`, list[:py:class:`Algo`], \
    **default** = :py:func:`algo`
    :return: a strategy object to be used a strategy parameter on a clustering operation
    :rtype: :py:class:`Strategy`
    """
    return Strategy(*args, **kwargs)
