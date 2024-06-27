#include <sstream>
#include <iostream>
#include <string>

#include "value/unit_value.h"

#ifdef MAGNITUDE_ARRAYS

inline constexpr void compare_size(const Array& a1, const Array& a2) {
  if (a1.value.size()!=a2.value.size())
    throw std::invalid_argument("Arrays have different size: "+std::to_string(a1.value.size())+" != "+std::to_string(a2.value.size()));
}

std::string Array::to_string() const {
  std::stringstream ss;
  if (value.size()==1) {
    ss << value[0] << std::scientific;
  } else {
    ss << "[" << value[0] << ", " << value[1] << std::scientific;
    if (value.size()>2)
      ss << ", ...]";
    else
      ss << "]";
  }
  return ss.str();
}

void Array::operator+=(const Array& a) {
  for (int i=0; i<value.size(); i++)
    value[i] += a.value[i];
}

Array operator+(const Array& a1, const Array& a2) {
  compare_size(a1, a2);
  ArrayValue av;
  for (int i=0; i<a1.value.size(); i++)
    av.push_back(a1.value[i] + a2.value[i]);
  return Array(av);
}

void Array::operator-=(const Array& a) {
  for (int i=0; i<value.size(); i++)
    value[i] -= a.value[i];
}

Array operator-(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(-a.value[i]);
  return Array(av);
}

Array operator-(const Array& a1, const Array& a2) {
  compare_size(a1, a2);
  ArrayValue av;
  for (int i=0; i<a1.value.size(); i++)
    av.push_back(a1.value[i] - a2.value[i]);
  return Array(av);
}

void Array::operator*=(const Array& a) {
  for (int i=0; i<value.size(); i++)
    value[i] *= a.value[i];
}

Array operator*(const Array& a1, const Array& a2) {
  compare_size(a1, a2);
  ArrayValue av;
  for (int i=0; i<a1.value.size(); i++)
    av.push_back(a1.value[i] * a2.value[i]);
  return Array(av);
}

void Array::operator/=(const Array& a) {
  for (int i=0; i<value.size(); i++)
    value[i] /= a.value[i];
}

Array operator/(const Array& a1, const Array& a2) {
  compare_size(a1, a2);
  ArrayValue av;
  for (int i=0; i<a1.value.size(); i++)
    av.push_back(a1.value[i] / a2.value[i]);
  return Array(av);
}

void Array::pow(const EXPONENT_TYPE& e) {
  for (int i=0; i<value.size(); i++)
    value[i] = std::pow(value[i], (EXPONENT_REAL_PRECISION)e);
}

Array pow(const Array &a, const EXPONENT_TYPE& e) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::pow(a.value[i], (EXPONENT_REAL_PRECISION)e));
  return Array(av);
}

#ifdef EXPONENT_FRACTIONS
void Array::pow(const EXPONENT_INT_PRECISION& e) {
  for (int i=0; i<value.size(); i++)
    value[i] = std::pow(value[i], e);
}

Array pow(const Array &a, const EXPONENT_INT_PRECISION& e) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::pow(a.value[i], e));
  return Array(av);
}
#endif

bool Array::operator==(const Array& a) const {
  for (int i=0; i<value.size(); i++)
    if (value != a.value) {
      return false;
    }
  return true;
}

bool Array::operator!=(const Array& a) const {
  for (int i=0; i<value.size(); i++)
    if (value != a.value) {
      return true;
    }
  return false;
}

Array log10(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::log10(a.value[i]));
  return Array(av);
}

Array floor(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::floor(a.value[i]));
  return Array(av);
}

Array abs(const Array& a) {
  ArrayValue av;
  for (int i=0; i<a.value.size(); i++)
    av.push_back(std::abs(a.value[i]));
  return Array(av);
}

Array max(const Array& a1, const Array& a2) {
  compare_size(a1, a2);
  ArrayValue av;
  for (int i=0; i<a1.value.size(); i++)
    av.push_back(std::max(a1.value[i],a2.value[i]));
  return Array(av);
}

#endif
