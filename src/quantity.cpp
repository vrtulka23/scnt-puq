#include <iostream>

#include "quantity.h"
#include "solver/unit_solver.h"

Quantity::Quantity(MAGNITUDE_TYPE m, std::string const&s) {
  UnitSolver solver;  
  UnitAtom atom = solver.solve(s);
  value.magnitude = m * atom.value.magnitude;
  value.baseunits = atom.value.baseunits;
}

#ifdef MAGNITUDE_ERRORS

Quantity::Quantity(MAGNITUDE_PRECISION const&m, std::string const&s) {
  UnitSolver solver;  
  UnitAtom atom = solver.solve(s);
  value.magnitude = Magnitude(m) * atom.value.magnitude;
  value.baseunits = atom.value.baseunits;
}

Quantity::Quantity(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, std::string const&s) {
  UnitSolver solver;  
  UnitAtom atom = solver.solve(s);
  value.magnitude = Magnitude(m,e) * atom.value.magnitude;
  value.baseunits = atom.value.baseunits;
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
