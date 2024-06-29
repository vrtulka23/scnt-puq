#include <iostream>

#include "quantity.h"

Quantity::Quantity(const MAGNITUDE_TYPE &m, const std::string& s) {
  value = UnitValue(s);
  value.magnitude *= m;
}

#ifdef MAGNITUDE_ERRORS

Quantity::Quantity(const MAGNITUDE_PRECISION& m, const std::string& s) {
  value = UnitValue(s);
  value.magnitude *= Magnitude(m);
}

Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const std::string& s) {
  value = UnitValue(s);
  value.magnitude *= Magnitude(m,e);
}

#endif

std::string Quantity::to_string() {
  return value.to_string();
}

Quantity Quantity::operator+(Quantity &q) {
  return Quantity(value+q.value);
}

Quantity Quantity::operator-(Quantity &q) {
  return Quantity(value-q.value);
}

Quantity Quantity::operator*(Quantity &q) {
  return Quantity(value*q.value);
}

Quantity Quantity::operator/(Quantity &q) {
  return Quantity(value/q.value);
}

void Quantity::operator+=(Quantity &q) {
  value += q.value;
}

void Quantity::operator-=(Quantity &q) {
  value -= q.value;
}

void Quantity::operator*=(Quantity &q) {
  value *= q.value;
}

void Quantity::operator/=(Quantity &q) {
  value /= q.value;
}
