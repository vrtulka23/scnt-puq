#include "lists.h"

namespace puq {

UnitSystem::UnitSystem(Stype st): closed(false) {
  previous = UnitList;
  switch (st) {
  case UnitSystem::SI:
    UnitList = &puq::si::UnitList;
    break;
  case UnitSystem::ESU:
    UnitList = &puq::cgs::UnitListESU;
    break;
  case UnitSystem::GAUSS:
    UnitList = &puq::cgs::UnitListGauss;
    break;
  case UnitSystem::EMU:
    UnitList = &puq::cgs::UnitListEMU;
    break;
  case UnitSystem::AU:
    UnitList = &puq::au::UnitList;
    break;
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
