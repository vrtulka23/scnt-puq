#ifndef PUQ_NOSTD_H
#define PUQ_NOSTD_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "settings.h"
#include "magnitude.h"
#include "value/value.h"
#include "array.h"

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
  
  inline std::string to_string(const MAGNITUDE_PRECISION& value, int precision=std::cout.precision()) {
    std::stringstream ss;
    ss << std::setprecision(precision);
    ss << value << std::scientific;
    return ss.str();
  }

#ifdef MAGNITUDE_ARRAYS
  inline std::string to_string(const Array& value, int precision=std::cout.precision()) {
    return value.to_string(precision);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline std::string to_string(const Magnitude& value, int precision=std::cout.precision()) {
    return value.to_string(precision);
  }
#endif
  
  inline std::string to_string(const BaseUnits& value, int precision=std::cout.precision()) {
    return value.to_string();
  }
  
  inline std::string to_string(const Dimensions& value, Dformat format=Dformat::NUM|Dformat::PHYS, int precision=std::cout.precision()) {
    return value.to_string(format, precision);
  }
  
  inline std::string to_string(const bool& use_prefixes, const AllowedPrefixes& value) {
    std::stringstream ss;
    if (use_prefixes) {
      if (value.size()>0) {
	std::stringstream sss;
	bool sep = false;
	for (auto pref: value) {
	  sss << (sep?", ":"") << pref;
	  sep = true;
	}
	ss << sss.str();
      } else ss << "all";
    }
    return ss.str();
  }
  
  /*
   *  exp
   */
  
  inline MAGNITUDE_PRECISION exp(const MAGNITUDE_PRECISION& e) {
    return std::exp(e);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array exp(const Array& e) {
    ArrayValue av;
    for (int i=0; i<e.size(); i++)
      av.push_back(std::exp(e[i]));
    return Array(av);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude exp(const Magnitude& e) {
    return Magnitude(exp(e.value));
  }
#endif

  /*
   *  pow
   */

  inline MAGNITUDE_PRECISION pow(const MAGNITUDE_PRECISION& m, const EXPONENT_REAL_PRECISION& e) {
    return std::pow(m, e);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array pow(const Array &a, const EXPONENT_REAL_PRECISION& e) {
    ArrayValue av;
    for (int i=0; i<a.size(); i++)
      av.push_back(std::pow(a[i], e));
    return Array(av);
  }
  inline Array pow(const Array &a, const Array& e) {
    auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
      return std::pow(v1, v2);
    };
    return Array::const_operation(a, e, fn);
  }
#endif

#ifdef MAGNITUDE_ERRORS
  inline Magnitude pow(const Magnitude& m, const EXPONENT_REAL_PRECISION& e) {
    return Magnitude(pow(m.value, e));
  }
  inline Magnitude pow(const Magnitude& m, const Magnitude& e) {
    return Magnitude(pow(m.value, e.value));
  }
#endif

  /*
   * log
   */

  inline MAGNITUDE_PRECISION log(const MAGNITUDE_PRECISION& m) {
    return std::log(m);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array log(const Array& a) {
    ArrayValue av;
    for (int i=0; i<a.size(); i++)
      av.push_back(std::log(a[i]));
    return Array(av);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude log(const Magnitude& m) {
    return Magnitude(log(m.value));
  }
#endif

  /*
   * log10
   */
  
  inline MAGNITUDE_PRECISION log10(const MAGNITUDE_PRECISION& m) {
    return std::log10(m);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array log10(const Array& a) {
    ArrayValue av;
    for (int i=0; i<a.size(); i++)
      av.push_back(std::log10(a[i]));
    return Array(av);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude log10(const Magnitude& m) {
    return Magnitude(log10(m.value));
  }
#endif

  /*
   * floor
   */
  
  inline MAGNITUDE_PRECISION floor(const MAGNITUDE_PRECISION& m) {
    return std::floor(m);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array floor(const Array& a) {
    ArrayValue av;
    for (int i=0; i<a.size(); i++)
      av.push_back(std::floor(a[i]));
    return Array(av);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude floor(const Magnitude& m) {
    return Magnitude(floor(m.value));
  }
#endif

  /*
   * abs
   */
  
  inline MAGNITUDE_PRECISION abs(const MAGNITUDE_PRECISION& m) {
    return std::abs(m);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array abs(const Array& a) {
    ArrayValue av;
    for (int i=0; i<a.size(); i++)
      av.push_back(std::abs(a[i]));
    return Array(av);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude abs(const Magnitude& m) {
    return Magnitude(abs(m.value));
  }
#endif

  /*
   * max
   */
  
  inline MAGNITUDE_PRECISION max(const MAGNITUDE_PRECISION& m1, const MAGNITUDE_PRECISION& m2) {
    return std::max(m1, m2);
  }

#ifdef MAGNITUDE_ARRAYS
  inline Array max(const Array& a1, const Array& a2) {
    auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
      return std::max(v1, v2);
    };
    return Array::const_operation(a1, a2, fn);
  }
#endif
  
#ifdef MAGNITUDE_ERRORS
  inline Magnitude max(const Magnitude& m1, const Magnitude& m2) {
    return Magnitude(max(m1.value, m2.value));
  }
#endif
  
}
}

#endif // PUQ_NOSTD_H
