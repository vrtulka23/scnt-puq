#include <sstream>

#include "../settings.h"
#include "unit_value.h"

Dimensions::Dimensions() {
  magnitude = 1;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    dimensions[i].numerator = 0;
#else
    dimensions[i] = 0; 
#endif
  }
}

Dimensions::Dimensions(MAGNITUDE_TYPE const&m) {
  magnitude = m;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    dimensions[i].numerator = 0;
#else
    dimensions[i] = 0; 
#endif
  }
}

#ifdef MAGNITUDE_ERRORS

Dimensions::Dimensions(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e) {
  magnitude.value = m;
  magnitude.error = e;
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    dimensions[i].numerator = 0;
#else
    dimensions[i] = 0; 
#endif
  }  
}

#endif

std::string Dimensions::to_string(){
  std::stringstream ss;
#ifdef MAGNITUDE_ERRORS
  if (magnitude.value!=1)
    ss << magnitude.to_string() << SYMBOL_MULTIPLY;
#else
  if (magnitude!=1)
    ss << magnitude << std::scientific << SYMBOL_MULTIPLY;
#endif
  for (int i=0; i<NUM_BASEDIM; i++) {
#ifdef EXPONENT_FRACTIONS
    if (dimensions[i].numerator!=0)
      ss << UnitList[i].symbol << dimensions[i].to_string() << SYMBOL_MULTIPLY;
#else
    if (dimensions[i]==1)
      ss << UnitList[i].symbol << SYMBOL_MULTIPLY;
    else if (dimensions[i]!=0)
      ss << UnitList[i].symbol << dimensions[i] << SYMBOL_MULTIPLY;
#endif
  }
  std::string s = ss.str();
  return s.substr(0,s.size()-1);
}

bool Dimensions::operator==(Dimensions const&d) const {
  bool equal = true;
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (dimensions[i]!=d.dimensions[i])
      equal = false;
  }
  return equal;
}

bool Dimensions::operator!=(Dimensions const&d) const {
  bool equal = false;
  for (int i=0; i<NUM_BASEDIM; i++) {
    if (dimensions[i]!=d.dimensions[i])
      equal = true;
  }
  return equal;
}
