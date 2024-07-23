#include "lists.h"

namespace puq {

  const SystemDataType* UnitSystem::Data = &SystemData::SI;
  
  std::stack<const SystemDataType *> UnitSystem::systemStack;
  
  UnitSystem::UnitSystem(const SystemDataType& st): closed(false) {
    systemStack.push(Data);
    Data = &st;
  }
  
  UnitSystem::UnitSystem(const SystemDataType* st): closed(false) {
    systemStack.push(Data);
    Data = st;
  }
  
  UnitSystem::~UnitSystem() {
    if (!closed)
      close();
  }

  void UnitSystem::change(const SystemDataType* st) {
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
