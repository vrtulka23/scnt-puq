#include "lists.h"

namespace puq {

UnitSystem::UnitSystem(Stype st): closed(false) {
  previous = UnitList;
  switch (st) {
  case UnitSystem::SI:
    UnitList = &puq::si::UnitList;
    break;
#ifdef UNITS_SYSTEM_CGS
  case UnitSystem::ESU:
    UnitList = &puq::cgs::UnitListESU;
    break;
  case UnitSystem::GAUSS:
    UnitList = &puq::cgs::UnitListGauss;
    break;
  case UnitSystem::EMU:
    UnitList = &puq::cgs::UnitListEMU;
    break;
#endif
#ifdef UNITS_SYSTEM_AU
  case UnitSystem::AU:
    UnitList = &puq::au::UnitList;
    break;
#endif
  }
}

UnitSystem::~UnitSystem() {
  if (!closed)
    close();
}

void UnitSystem::close() {
  puq::UnitList = previous;
  closed = true;
}

}
