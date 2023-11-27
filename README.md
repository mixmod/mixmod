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

## Table of contents

- [Folder structure](#folder-structure)
- [C++ components](#c-components)
  - [Requirements](#requirements)
  - [Compilation](#compilation)
  - [Examples](#examples)
- [Rmixmod](#rmixmod)
  - [R Requirements](#r-requirements)
  - [Build](#build)
- [PyMixmod](#pymixmod)
- [Docs](#docs)
- [Citation](#citation)
- [License](#license)
- [Contributing](#contributing)

## Folder structure

- **Rmixmod**  R interface of the C++ mixmod library
- **mixmodLib** C++ mixmod library
- **mixmodIOStream** C++ library to manage IO
- **mixmodCLI** Command Line Interface
- **Pymixmod** Python interface
- **mixmodGUI** unmaintained
- **mixmodMVC** unmaintained

## C++ components

[![C++ components](https://github.com/mixmod/mixmod/actions/workflows/build.yml/badge.svg)](https://github.com/mixmod/mixmod/actions/workflows/build.yml)

### Requirements

Requirements for mixmoLib:

``` bash
sudo apt install -y cmake libeigen3-dev
```

Extra requirement for mixmodIOStream

``` bash
sudo apt install -y libxml++2.6-dev
```

### Compilation

A main [CMake file](CMakeLists.txt) is used to compiled mixmodLib, mixmodIOStream and mixmodCLI.

Compilation options:

- `-DCMAKE_INSTALL_PREFIX`: installation folder
- `-DCMAKE_BUILD_TYPE`: `Debug` or `Release` (default)
- `-DCMAKE_CXX_FLAGS`: extra c++ compilation flags (optional)
- `-DMIXMOD_BUILD_IOSTREAM`: `ON` or `OFF` (default). Compile or not mixmodIOStream
- `-DMIXMOD_BUILD_CLI`: `ON` or `OFF` (default). Compile or not mixmodCLI. It requires `-DMIXMOD_BUILD_IOSTREAM=ON`
- `-DMIXMOD_BUILD_EXAMPLES`: `ON` or `OFF` (default)
- `-DMIXMOD_ENABLE_OPENMP`: `OFF` or `ON` (default). Enable OpenMP or not.

Generate makefile:

``` bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/usr/local/ -DCMAKE_CXX_FLAGS="-Wall -Wextra -D_GLIBCXX_ASSERTIONS" ..
```

Compile:

``` bash
make install -j2
```

### Examples

See [mixmodLib/EXAMPLES](mixmodLib/EXAMPLES) for some examples.

## Rmixmod

R interface of the C++ mixmod library.

[![Rmixmod build status](https://github.com/mixmod/mixmod/workflows/R-CMD-check/badge.svg?branch=master)](https://github.com/mixmod/mixmod/actions)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/Rmixmod)](https://cran.r-project.org/package=Rmixmod) [![Total Downloads](http://cranlogs.r-pkg.org/badges/grand-total/Rmixmod?color=blue)](http://cranlogs.r-pkg.org/badges/grand-total/Rmixmod) [![Downloads](https://cranlogs.r-pkg.org/badges/Rmixmod)](https://cran.rstudio.com/web/packages/Rmixmod/index.html)

### R Requirements

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

## PyMixmod

Python interface of the C++ mixmod library.

[![Test PyMixmod](https://github.com/mixmod/mixmod/actions/workflows/Pymixmod.yml/badge.svg?branch=master)](https://github.com/mixmod/mixmod/actions/workflows/Pymixmod.yml)

See the dedicated [README](Pymixmod/README.rst).

## Docs

See the [doc](doc) folder to find the different paper about Rmixmod, a statistical documentation and a user guide for mixmod.

## Citation

Lebret, R., Iovleff, S., Langrognet, F., Biernacki, C., Celeux, G., & Govaert, G. (2015). Rmixmod: The R Package of the Model-Based Unsupervised, Supervised, and Semi-Supervised Classification Mixmod Library. Journal of Statistical Software, 67(6), 1–29. <https://doi.org/10.18637/jss.v067.i06>

See [CITATION.bib](CITATION.bib)

## License

mixmod is distributed under the GPL v3 license

## Contributing

- Use the [.clang-format](.clang-format) file to format the c++ code.
- Use [lintr](https://cran.r-project.org/package=lintr) to format the R code with the following .lintr file:

  ``` text
  linters: linters_with_defaults(
    line_length_linter(127),
    object_name_linter = NULL
    )
  ```
