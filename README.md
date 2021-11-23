# mixmod

Mixmod is a software package for Model-Based supervised and unsupervised classification on qualitative, quantitative and mixed data.

Available components:

- A package for R: Rmixmod
- A module for Python: Pymixmod
- A computational library: mixmodLib (C++)
- A Graphical User Interface: mixmodGUI

Main Statistical functionalities:

- Likelihood maximization with EM, CEM and SEM algorithm
- Parsimonious models
  - 14 models for quantitative data (Gaussian mixture models)
  - 5 models for qualitative data (Multinomial mixture models)
  - 20 models for mixed data (quantitative/qualitative)
  - 8 specific models for High Dimension
- Selection criteria: BIC, ICL, NEC, CV

Previous repository: <https://gforge.inria.fr/projects/mixmod>

## Organization

- **Rmixmod**  R interface of the C++ mixmod library
- **mixmodLib** C++ mixmod library
- **mixmodIOStream** C++ library to manage IO
- **Pymixmod** Python interface
- **mixmodCLI** Command Line Interface
- **mixmodGUI** unmaintained
- **mixmodMVC** unmaintained

## Rmixmod

[![Rmixmod build status](https://github.com/mixmod/mixmod/workflows/R-CMD-check/badge.svg?branch=master)](https://github.com/mixmod/mixmod/actions)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/Rmixmod)](https://cran.r-project.org/package=Rmixmod) [![Total Downloads](http://cranlogs.r-pkg.org/badges/grand-total/Rmixmod?color=blue)](http://cranlogs.r-pkg.org/badges/grand-total/Rmixmod) [![Downloads](https://cranlogs.r-pkg.org/badges/Rmixmod)](https://cran.rstudio.com/web/packages/Rmixmod/index.html)

### Requirements

Install the following R packages in order to build Rmixmod:

``` r
install.packages(c("Rcpp", "RcppEigen", "devtools"))
```

### Build

In a terminal, run:

``` sh
./build_rmixmod.sh
```

It creates a directory named `Rmixmod_[version]` containing the package archive.

The package can be installed running:

``` sh
R CMD INSTALL Rmixmod_[version]/Rmixmod_[version].tar.gz
```

and checked running:

``` sh
R CMD check --as-cran Rmixmod_[version]/Rmixmod_[version].tar.gz
```

## Citation

Lebret, R., Iovleff, S., Langrognet, F., Biernacki, C., Celeux, G., & Govaert, G. (2015). Rmixmod: The R Package of the Model-Based Unsupervised, Supervised, and Semi-Supervised Classification Mixmod Library. Journal of Statistical Software, 67(6), 1–29. <https://doi.org/10.18637/jss.v067.i06>

## License

mixmod is distributed under the GPL v3 license
