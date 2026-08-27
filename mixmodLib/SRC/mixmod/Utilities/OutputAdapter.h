#ifndef XEM_OUTPUT_ADAPTER_H
#define XEM_OUTPUT_ADAPTER_H

#include <iostream>

#ifdef RPACKAGE
#include <Rcpp.h>
#endif

namespace XEM
{

inline std::ostream &mixmodOut()
{
#ifdef RPACKAGE
	return Rcpp::Rcout;
#else
	return std::cout;
#endif
}

inline std::ostream &mixmodErr()
{
#ifdef RPACKAGE
	return Rcpp::Rcerr;
#else
	return std::cerr;
#endif
}

}

#define MIXMOD_COUT ::XEM::mixmodOut()
#define MIXMOD_CERR ::XEM::mixmodErr()

#endif
