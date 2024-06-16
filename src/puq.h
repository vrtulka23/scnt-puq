#include <string>
#include "settings.h"

enum class ErrorType {
  NONE,
};

class Magnitude {
public:
  MAGNITUDE_TYPE value;
  MAGNITUDE_TYPE error;
  ErrorType etype;
  Magnitude(MAGNITUDE_TYPE v): value(v), error(0), etype(ErrorType::NONE) {};
  Magnitude(MAGNITUDE_TYPE v, MAGNITUDE_TYPE e, ErrorType et): value(v), error(e), etype(et) {};
};

class Dimensions {
public:
  Dimensions(std::string units) {};
  Dimensions(std::string dimensions[NUM_BASEDIM]) {};
};

/*
class Quantity {
public:
  Quantity(MAGNITUDE_TYPE &m, std::string units) {};
  Quantity(MAGNITUDE_TYPE &m, BaseUnits units) {};
  Quantity(Magnitude &m, std::string units) {};
  Quantity(Magnitude &m, BaseUnits units) {};
};
*/

#include "solver/solver.h"
