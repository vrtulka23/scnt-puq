#include <sstream>

#include "unit_value.h"

#ifdef MAGNITUDE_ARRAYS

std::string Array::to_string() {
  std::stringstream ss;
  ss << value << std::scientific;
  return ss.str();
}

void Array::operator+=(Array const&a) {
  value += a.value;
}
Array Array::operator+(Array const&a) {
  return Array(value + a.value);
}

void Array::operator-=(Array const&a) {
  value -= a.value;
}
Array Array::operator-(Array const&a) {
  return Array(value - a.value);
}

void Array::operator*=(Array const&a) {
  value *= a.value;
}
Array Array::operator*(Array const&a) {
  return Array(value * a.value);
}

void Array::operator/=(Array const&a) {
  value /= a.value;
}
Array Array::operator/(Array const&a) {
  return Array(value / a.value);
}

void Array::operator^=(EXPONENT_TYPE &e) {
#ifdef EXPONENT_FRACTIONS
  value = std::pow(value, e.to_real());
#else
  value = std::pow(value, e);
#endif
}
Array Array::operator^(EXPONENT_TYPE &e) {
#ifdef EXPONENT_FRACTIONS
  return Array(std::pow(value, e.to_real()));
#else
  return Array(std::pow(value, e));
#endif
}

bool Array::operator==(Array const&a) const {
  return value == a.value;
}

#endif
