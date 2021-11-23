# mixmod

previous repository: <https://gforge.inria.fr/projects/mixmod>

[![Rmixmod build status](https://github.com/mixmod/mixmod/workflows/R-CMD-check/badge.svg?branch=master)](https://github.com/mixmod/mixmod/actions)

Mixmod is a software package for Model-Based supervised and unsupervised classification on qualitative, quantitative and mixed data.

Available components:

- A package for R : Rmixmod
- A module for Python : Pymixmod
- A Graphical User Interface : mixmodGUI
- A computational library (mixmodLib) (C++)

Main Statistical functionalities:

- Likelihood maximization with EM, CEM and SEM algorithm
- Parsimonious models
  - 14 models for quantitative data (Gaussian mixture models)
  - 5 models for qualitative data (Multinomial mixture models)
  - 20 models for mixed data (quantitative/qualitative)
  - 8 specific models for High Dimension
- Selection criteria : BIC, ICL, NEC, CV

## Organization

- **Rmixmod**  R interface of the C++ mixmod library
- **mixmodLib** C++ mixmod library
- **mixmodIOStream**
- **mixmodCLI**
- **Pymixmod** Python interface
- **mixmodGUI** unmaintained
- **mixmodMVC** unmaintained

## Rmixmod

### Requirements

Install the following R packages in order to compile Rmixmod:

``` r
install.packages(c("Rcpp", "RcppEigen", "devtools"))
```

### Installation

In a terminal, run:

``` sh
./build_rmixmod.sh
```

## Citation

Lebret, R., Iovleff, S., Langrognet, F., Biernacki, C., Celeux, G., & Govaert, G. (2015). Rmixmod: The R Package of the Model-Based Unsupervised, Supervised, and Semi-Supervised Classification Mixmod Library. Journal of Statistical Software, 67(6), 1–29. <https://doi.org/10.18637/jss.v067.i06>
