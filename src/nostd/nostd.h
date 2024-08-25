#ifndef PUQ_NOSTD_H
#define PUQ_NOSTD_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
//#include <omp.h>

#include "../settings.h"
#include "../magnitude.h"
#include "../value/value.h"
#include "../array.h"

namespace puq {
  namespace nostd {

    /*
     *  stof, stod, stold -> to_number
     */

    inline MAGNITUDE_PRECISION to_number(const std::string& value) {
      if (typeid(MAGNITUDE_PRECISION)==typeid(float)) 
	return std::stof(value); 
      else if (typeid(MAGNITUDE_PRECISION)==typeid(double)) 
	return std::stod(value);
      else if (typeid(MAGNITUDE_PRECISION)==typeid(long double)) 
	return std::stold(value);
      else
	throw std::range_error("Unsupported magnitude precision.");
    }
  
    /*
     *  to_string
     */
  
    extern std::string to_string(const MAGNITUDE_PRECISION& value, int precision=std::cout.precision());
#ifdef MAGNITUDE_ARRAYS
    extern std::string to_string(const Array& value, int precision=std::cout.precision());
#endif
#ifdef MAGNITUDE_ERRORS
    extern std::string to_string(const Magnitude& value, int precision=std::cout.precision());
#endif
    extern std::string to_string(const BaseUnits& value, int precision=std::cout.precision());
    extern std::string to_string(const Dimensions& value, Dformat format=Dformat::NUM|Dformat::PHYS, int precision=std::cout.precision());
    extern std::string to_string(const bool& use_prefixes, const AllowedPrefixes& value);
  
    /*
     *  exp
     */
  
    extern MAGNITUDE_PRECISION exp(const MAGNITUDE_PRECISION& e);
#ifdef MAGNITUDE_ARRAYS
    extern Array exp(const Array& e);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude exp(const Magnitude& e);
#endif
    extern UnitValue exp(const UnitValue& uv);
  
    /*
     * log
     */

    extern MAGNITUDE_PRECISION log(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array log(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude log(const Magnitude& m);
#endif

    /*
     * log10
     */
  
    extern MAGNITUDE_PRECISION log10(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array log10(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude log10(const Magnitude& m);
#endif

    /*
     * sqrt
     */
  
    extern MAGNITUDE_PRECISION sqrt(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array sqrt(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude sqrt(const Magnitude& m);
#endif

    /*
     * cbrt
     */
  
    extern MAGNITUDE_PRECISION cbrt(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array cbrt(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude cbrt(const Magnitude& m);
#endif
  
    /*
     *  pow
     */

    extern MAGNITUDE_PRECISION pow(const MAGNITUDE_PRECISION& m, const EXPONENT_REAL_PRECISION& e);
#ifdef MAGNITUDE_ARRAYS
    extern Array pow(const Array &a, const EXPONENT_REAL_PRECISION& e);
    extern Array pow(const Array &a, const Array& e);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude pow(const Magnitude& m, const EXPONENT_REAL_PRECISION& e);
    extern Magnitude pow(const Magnitude& m, const Magnitude& e);
#endif

    /*
     * floor
     */
  
    extern MAGNITUDE_PRECISION floor(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array floor(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude floor(const Magnitude& m);
#endif

    /*
     * abs
     */
  
    extern MAGNITUDE_PRECISION abs(const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    extern Array abs(const Array& a);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude abs(const Magnitude& m);
#endif

    /*
     * max
     */
  
    extern MAGNITUDE_PRECISION max(const MAGNITUDE_PRECISION& m1, const MAGNITUDE_PRECISION& m2);
#ifdef MAGNITUDE_ARRAYS
    extern Array max(const Array& a1, const Array& a2);
#endif
#ifdef MAGNITUDE_ERRORS
    extern Magnitude max(const Magnitude& m1, const Magnitude& m2);
#endif
  
  }
}

#endif // PUQ_NOSTD_H
