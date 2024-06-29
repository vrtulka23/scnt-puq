#include <sstream>
#include <iostream>
#include <string>

#include "array.h"

#ifdef MAGNITUDE_ARRAYS

Array Array::filled(const MAGNITUDE_PRECISION& v, const size_t &s) {
  Array a;
  for (size_t i = 0; i<s; i++)
    a.append(v);
  return a;
};

inline constexpr void compare_size(const Array& a1, const Array& a2) {
  if (a1.size()!=a2.size())
    throw std::invalid_argument("Arrays have different size: "+std::to_string(a1.size())+" != "+std::to_string(a2.size()));
}

std::string Array::to_string() const {
  std::stringstream ss;
  if (value.size()==1) {
    ss << value[0] << std::scientific;
  } else if (value.size()==2) {
    ss << SYMBOL_ARRAY_START << value[0];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << value[1];
    ss << std::scientific << SYMBOL_ARRAY_END;
  } else if (value.size()>2) {
    ss << SYMBOL_ARRAY_START << value[0];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << value[1];
    ss << SYMBOL_ARRAY_SEPARATOR << " " << SYMBOL_ARRAY_MORE;
    ss << std::scientific << SYMBOL_ARRAY_END;
  }
  return ss.str();
}

size_t Array::size() const {
  return value.size();
};

void Array::append(const MAGNITUDE_PRECISION& v) {
  value.push_back(v);
}

void Array::append(const ArrayValue& v) {
  value.insert(value.end(), v.begin(), v.end());
}

MAGNITUDE_PRECISION Array::operator[](const size_t i) const {
  return value[i];
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
