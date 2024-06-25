#ifndef PUQ_QUANTITY_H
#define PUQ_QUANTITY_H

#include "../settings.h"
#include "../value/unit_value.h"

class Quantity {
public:
  UnitValue value;
  Quantity() {};
  Quantity(UnitValue const&v): value(v) {}; 
  Quantity(MAGNITUDE_TYPE const&m): value(m) {}; 
  Quantity(MAGNITUDE_TYPE const&m, BaseUnitsList const&bu): value(m,bu) {};
  Quantity(MAGNITUDE_TYPE m, std::string const&s);
#ifdef MAGNITUDE_ERRORS
  Quantity(MAGNITUDE_PRECISION const&m): value(m) {};
  Quantity(MAGNITUDE_PRECISION const&m, BaseUnitsList const&bu): value(m,bu) {};
  Quantity(MAGNITUDE_PRECISION const&m, std::string const&s);
  Quantity(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e): value(m,e) {};
  Quantity(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, BaseUnitsList const&bu): value(m,e,bu) {};
  Quantity(MAGNITUDE_PRECISION const&m, MAGNITUDE_PRECISION const&e, std::string const&s);
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
