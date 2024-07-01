#include <sstream>
#include <iostream>

#include "../settings.h"
#include "unit_value.h"

Dimensions::Dimensions() {
  numerical = 1;
  for (int i=0; i<NUM_BASEDIM; i++) {
    physical[i] = 0; 
  }
}

Dimensions::Dimensions(const MAGNITUDE_TYPE& n) {
  numerical = n;
  for (int i=0; i<NUM_BASEDIM; i++) {
    physical[i] = 0; 
  }
}

#ifdef MAGNITUDE_ERRORS

Dimensions::Dimensions(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e) {
  numerical.value = m;
  numerical.error = e;
  for (int i=0; i<NUM_BASEDIM; i++) {
    physical[i] = 0; 
  }  
}

#endif

std::string Dimensions::to_string(char which) const {
  std::stringstream ss;
  if (which=='a' || which=='n') {
#if defined(MAGNITUDE_ERRORS)
    if (numerical.value!=1)
      ss << numerical.to_string() << SYMBOL_MULTIPLY;
#elif defined(MAGNITUDE_ARRAYS)
    if (numerical!=1)
      ss << numerical.to_string() << SYMBOL_MULTIPLY;
#else
    if (numerical!=1)
      ss << numerical << std::scientific << SYMBOL_MULTIPLY;
#endif
  }
  if (which=='a' || which=='p') {
    for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
      if (physical[i]!=0)
	ss << UnitList[i].symbol << physical[i].to_string() << SYMBOL_MULTIPLY;
#else
      if (physical[i]==1)
	ss << UnitList[i].symbol << SYMBOL_MULTIPLY;
      else if (physical[i]!=0)
	ss << UnitList[i].symbol << physical[i] << SYMBOL_MULTIPLY;
#endif
    }
  }
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

bool Dimensions::operator==(const Dimensions& d) const {
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (physical[i]!=d.physical[i])
      return false;
  }
  return true;
}

bool Dimensions::operator!=(const Dimensions& d) const {
  bool equal = false;
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (physical[i]!=d.physical[i])
      return true;
  }
  return false;
}
