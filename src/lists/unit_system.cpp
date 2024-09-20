#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "lists.h"
#include "../nostd/nostd.h"
#include "../solver/solver.h"

namespace puq {

  namespace SystemData {
    std::unordered_map<std::string, SystemDataType*> SystemMap = {
      {"SI",    &puq::SystemData::SI},
#ifdef UNIT_SYSTEM_CGS
      {"ESU",   &puq::SystemData::ESU},
      {"GAUSS", &puq::SystemData::GAUSS},
      {"EMU",   &puq::SystemData::EMU},
#endif
#ifdef UNIT_SYSTEM_EUS
      {"IU",    &puq::SystemData::IU},
      {"US",    &puq::SystemData::US},
#endif
#ifdef UNIT_SYSTEM_NUS
      {"AU",    &puq::SystemData::AU},
      {"PU",    &puq::SystemData::PU},
#endif
    };
  }

  SystemDataType* UnitSystem::Data = &SystemData::SI;
  std::stack<SystemDataType *> UnitSystem::systemStack;
 
  UnitSystem::UnitSystem(SystemDataType* st): closed(false) {
    systemStack.push(Data);
    Data = st;
  }
  
  UnitSystem::~UnitSystem() {
    if (!closed)
      close();
  }

  void UnitSystem::change(SystemDataType* st) {
    Data = systemStack.top();
    systemStack.pop();
    systemStack.push(Data);
    Data = st;
  }
  
  void UnitSystem::close() {
    Data = systemStack.top();
    systemStack.pop();
    closed = true;
  }

}
