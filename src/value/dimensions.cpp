#include <sstream>

#include "../settings.h"
#include "unit_value.h"

Dimensions::Dimensions() {
  numerical = 1;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    physical[i].numerator = 0;
#else
    physical[i] = 0; 
#endif
  }
}

Dimensions::Dimensions(MAGNITUDE_TYPE const&n) {
  numerical = n;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    physical[i].numerator = 0;
#else
    physical[i] = 0; 
#endif
  }
}

#ifdef MAGNITUDE_ERRORS

Dimensions::Dimensions(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e) {
  numerical.value = m;
  numerical.error = e;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    physical[i].numerator = 0;
#else
    physical[i] = 0; 
#endif
  }  
}

#endif

std::string Dimensions::to_string(){
  std::stringstream ss;
#ifdef MAGNITUDE_ERRORS
  if (numerical.value!=1)
    ss << numerical.to_string() << SYMBOL_MULTIPLY;
#else
  if (numerical!=1)
    ss << numerical << std::scientific << SYMBOL_MULTIPLY;
#endif
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    if (physical[i].numerator!=0)
      ss << UnitList[i].symbol << physical[i].to_string() << SYMBOL_MULTIPLY;
#else
    if (physical[i]==1)
      ss << UnitList[i].symbol << SYMBOL_MULTIPLY;
    else if (physical[i]!=0)
      ss << UnitList[i].symbol << physical[i] << SYMBOL_MULTIPLY;
#endif
  }
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

bool Dimensions::operator==(Dimensions const&d) const {
  bool equal = true;
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (physical[i]!=d.physical[i])
      equal = false;
  }
  return equal;
}

bool Dimensions::operator!=(Dimensions const&d) const {
  bool equal = false;
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (physical[i]!=d.physical[i])
      equal = true;
  }
  return equal;
}
