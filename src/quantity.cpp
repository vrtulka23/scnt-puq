#include <iostream>

#include "quantity.h"

namespace puq {

Quantity::Quantity(const MAGNITUDE_TYPE &m, const std::string& s) {
  value = UnitValue(m, s);
}

#ifdef MAGNITUDE_ERRORS

Quantity::Quantity(const MAGNITUDE_PRECISION& m, const std::string& s) {
  Magnitude mag(m);
  value = UnitValue(mag, s);
}

Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const std::string& s) {
  Magnitude mag(m,e);
  value = UnitValue(mag, s);
}

#endif

std::string Quantity::to_string() {
  return value.to_string();
}

Quantity Quantity::operator+(Quantity& q) {
  return Quantity(value+q.value);
}

Quantity Quantity::operator-(Quantity& q) {
  return Quantity(value-q.value);
}

Quantity Quantity::operator*(Quantity& q) {
  return Quantity(value*q.value);
}

Quantity Quantity::operator/(Quantity& q) {
  return Quantity(value/q.value);
}

void Quantity::operator+=(Quantity& q) {
  value += q.value;
}

void Quantity::operator-=(Quantity& q) {
  value -= q.value;
}

void Quantity::operator*=(Quantity& q) {
  value *= q.value;
}

void Quantity::operator/=(Quantity& q) {
  value /= q.value;
}

Quantity Quantity::convert(const Quantity& q) const {
  UnitValue uv = value.convert(q.value);
  return Quantity(uv);
}

Quantity Quantity::convert(const std::string& s) const {
  UnitValue uv = value.convert(s);
  return Quantity(uv);
}

Quantity Quantity::convert(const UnitValue& uv1) const {
  UnitValue uv2 = value.convert(uv1);
  return Quantity(uv2);
}

}
