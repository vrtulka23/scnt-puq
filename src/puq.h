#include <string>
#include "settings.h"

enum class ErrorType {
  NONE,
};

class Magnitude {
public:
  NUMBER_DTYPE value;
  NUMBER_DTYPE error;
  ErrorType etype;
  Magnitude(NUMBER_DTYPE v): value(v), error(0), etype(ErrorType::NONE) {};
  Magnitude(NUMBER_DTYPE v, NUMBER_DTYPE e, ErrorType et): value(v), error(e), etype(et) {};
};

class Dimensions {
public:
  Dimensions(std::string units) {};
  Dimensions(std::string dimensions[NUM_BASEDIM]) {};
};

class BaseUnits {
public:
  BaseUnits(std::string units) {};
  BaseUnits(std::string dimensions[NUM_BASEDIM]) {};
  BaseUnits(Dimensions dimensions) {};
};

class Quantity {
public:
  Quantity(NUMBER_DTYPE &m, std::string units) {};
  Quantity(NUMBER_DTYPE &m, BaseUnits units) {};
  Quantity(Magnitude &m, std::string units) {};
  Quantity(Magnitude &m, BaseUnits units) {};
};

#include "unit_solver/solver.h"
