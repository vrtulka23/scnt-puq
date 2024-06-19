#ifndef PUQ_QUANTITY_H
#define PUQ_QUANTITY_H

#include "../settings.h"
#include "../value/unit_value.h"

class Quantity {
public:
  UnitValue value;
  Quantity(UnitValue const&v): value(v) {}; 
  Quantity(Magnitude const&m): value(m) {}; 
  Quantity(Magnitude const&m, BaseUnits const&bu): value(m, bu) {}; 
};  

#endif // PUQ_QUANTITY_H
