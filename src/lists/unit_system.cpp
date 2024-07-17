#include "lists.h"

namespace puq {

  const UnitListType* UnitSystem::UnitList = &UnitList::SI;
  
  std::stack<const UnitListType *> UnitSystem::systemStack;
  
  UnitSystem::UnitSystem(const UnitListType& st): closed(false) {
    systemStack.push(UnitList);
    UnitList = &st;
  }
  
  UnitSystem::UnitSystem(const UnitListType* st): closed(false) {
    systemStack.push(UnitList);
    UnitList = st;
  }
  
  UnitSystem::~UnitSystem() {
    if (!closed)
      close();
  }

  void UnitSystem::close() {
    UnitList = systemStack.top();
    systemStack.pop();
    closed = true;
  }

}
