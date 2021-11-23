# mixmod

copy of mixmod svn repository: <https://gforge.inria.fr/projects/mixmod>

[![Rmixmod build status](https://github.com/mixmod/mixmod/workflows/R-CMD-check/badge.svg)](https://github.com/mixmod/mixmod/actions)

Mixmod is a well-established software package for fitting mixture models of multivariate Gaussian or multinomial probability distribution functions to a given dataset with either a clustering, a density estimation or a discriminant analysis purpose. The Rmixmod S4 package provides an interface from the R statistical computing environment to the C++ core library of Mixmod (mixmodLib).

## Organization

* **Rmixmod**  information about funding, meeting reports...
* **mixmodLib**
* **mixmodIOStream**
* **mixmodCLI** communications, articles...
* **Pymixmod** code of the different components
* **mixmodGUI**
* **mixmodMVC**

**Rmixmod** can be built using [build_rmixmod.sh](./build_rmixmod.sh)

## Requirements

Install the following R packages in order to compile Rmixmod:

``` r
install.packages(c("Rcpp", "RcppEigen", "devtools"))
```
