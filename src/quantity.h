#ifndef PUQ_QUANTITY_H
#define PUQ_QUANTITY_H

#include "settings.h"
#include "value/unit_value.h"
#include "solver/unit_solver.h"

class Quantity {
public:
  UnitValue value;
  Quantity() {};
  Quantity(const std::string& s): value(s) {};
  Quantity(const UnitValue& v): value(v) {}; 
  Quantity(const MAGNITUDE_TYPE& m): value(m) {}; 
  Quantity(const MAGNITUDE_TYPE& m, const BaseUnitsList& bu): value(m,bu) {};
  Quantity(const MAGNITUDE_TYPE& m, const std::string& s);
#ifdef MAGNITUDE_ERRORS
  Quantity(const MAGNITUDE_PRECISION& m): value(m) {};
  Quantity(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bu): value(m,bu) {};
  Quantity(const MAGNITUDE_PRECISION& m, const std::string& s);
  Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e): value(m,e) {};
  Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bu): value(m,e,bu) {};
  Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const std::string& s);
#endif
  std::string to_string();
  Quantity operator+(Quantity &q);
  Quantity operator-(Quantity &q);
  Quantity operator*(Quantity &q);
  Quantity operator/(Quantity &q);
  void operator+=(Quantity &q);
  void operator-=(Quantity &q);
  void operator*=(Quantity &q);
  void operator/=(Quantity &q);
};

#endif // PUQ_QUANTITY_H
