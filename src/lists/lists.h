#ifndef PUQ_LISTS_H
#define PUQ_LISTS_H

#include <string>
#include <set>
#include <map>

#include "../settings.h"
#include "../exponent.h"
#include "../array.h"
#include "../magnitude.h"

struct UnitPrefixStruct {
  std::string symbol;
  MAGNITUDE_TYPE magnitude;
  std::string definition;
  std::string name;
};
extern std::vector<UnitPrefixStruct> UnitPrefixList;

struct UnitStruct {
  std::string symbol;
  MAGNITUDE_TYPE magnitude;
  EXPONENT_TYPE dimensions[NUM_BASEDIM];
  std::string definition;
  std::string name;
  bool use_prefixes;
  std::set<std::string> allowed_prefixes;
};
extern std::vector<UnitStruct> UnitList;

#endif // PUQ_LISTS_H
