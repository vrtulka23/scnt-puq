#include <sstream>
#include <cmath>
#include <iostream>
#include <format>

#include "unit_value.h"

#ifdef MAGNITUDE_ERRORS

/*
 * Return a string representation of a magnitude
 */
std::string Magnitude::to_string() {
  std::stringstream ss;
  if (error==0) {
    if (magnitude!=1)
      ss << magnitude << std::scientific;
  } else {
    int N = 2;
    int exp_mag  = std::floor(std::log10(magnitude));
    int exp_err  = std::floor(std::log10(error));
    int exp_diff = std::abs(exp_mag-exp_err)+1;
    MAGNITUDE_PRECISION val_mag = magnitude*std::pow(10,-exp_mag);
    int val_err  = std::round(error*std::pow(10,1-exp_err));
    ss << std::vformat("{:.0"+std::to_string(exp_diff)+"f}", std::make_format_args(val_mag));
    ss << std::format("({:2d})", val_err);
    if (exp_mag!=0)
      ss << (exp_mag>=0 ? "e+" : "e-") << std::format("{:-02d}", std::abs(exp_mag));
  }
  return ss.str();
}

/*
 * Multiply magnitude by another magnitude
 */
void Magnitude::operator*=(Magnitude &m) {
  magnitude *= m.magnitude;
}

/*
 * Divide magnitude by another magnitude
 */
void Magnitude::operator/=(Magnitude &m) {
  magnitude /= m.magnitude;
}

/*
 *  Rise magnitude to the power of an exponent (not a binary operation!!)
 */
void Magnitude::operator^=(EXPONENT_TYPE &e) {
#ifdef EXPONENT_FRACTIONS
  magnitude = std::pow(magnitude, e.to_real());
#else
  magnitude = std::pow(magnitude, e);
#endif
}

#endif
