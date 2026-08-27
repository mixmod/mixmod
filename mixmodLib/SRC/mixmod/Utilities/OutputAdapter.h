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

#if defined(RPACKAGE) && !defined(MIXMOD_ENABLE_DEBUG_IO)
class MixmodNullBuffer : public std::streambuf
{
public:
	int overflow(int c) { return c; }
};

inline std::ostream &mixmodDebugOut()
{
	static MixmodNullBuffer nullBuffer;
	static std::ostream nullStream(&nullBuffer);
	return nullStream;
}
#else
inline std::ostream &mixmodDebugOut() { return mixmodOut(); }
#endif

}

#define MIXMOD_COUT ::XEM::mixmodOut()
#define MIXMOD_CERR ::XEM::mixmodErr()
#define MIXMOD_DEBUG_COUT ::XEM::mixmodDebugOut()

#endif
