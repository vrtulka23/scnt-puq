#include <sstream>

#include "unit_value.h"

#ifdef MAGNITUDE_ERRORS

std::string Magnitude::to_string() {
  std::stringstream ss;
  if (magnitude!=1)
    ss << magnitude << std::scientific;
  return ss.str();
}

void Magnitude::operator*=(Magnitude &m) {
  magnitude *= m.magnitude;
}

void Magnitude::operator/=(Magnitude &m) {
  magnitude /= m.magnitude;
}

#endif
