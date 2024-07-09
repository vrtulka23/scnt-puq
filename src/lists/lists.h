#ifndef PUQ_LISTS_H
#define PUQ_LISTS_H

#include <string>
#include <set>
#include <map>

#include "../settings.h"
#include "../magnitude.h"

namespace puq {

enum class Utype : std::uint8_t {
  NUL = 0b00000000,  // empty flag
  BAS = 0b00000001,  // base units
  LIN = 0b00000010,  // standard unit (linear conversion)
  LOG = 0b00000100,  // logarithmic unit
  TMP = 0b00001000,  // temperature unit
  CST = 0b00010000,  // constant
};

inline Utype operator|(Utype lhs, Utype rhs) {
    return static_cast<Utype>(
        static_cast<std::underlying_type_t<Utype>>(lhs) |
        static_cast<std::underlying_type_t<Utype>>(rhs)
    );
}

inline Utype operator&(Utype lhs, Utype rhs) {
    return static_cast<Utype>(
        static_cast<std::underlying_type_t<Utype>>(lhs) &
        static_cast<std::underlying_type_t<Utype>>(rhs)
    );
}

inline Utype operator^(Utype lhs, Utype rhs) {
    return static_cast<Utype>(
        static_cast<std::underlying_type_t<Utype>>(lhs) ^
        static_cast<std::underlying_type_t<Utype>>(rhs)
    );
}

struct UnitPrefixStruct {
  std::string symbol;
  MAGNITUDE_TYPE magnitude;
  std::string definition;
  std::string name;
};
extern std::vector<UnitPrefixStruct> UnitPrefixList;

typedef std::array<EXPONENT_TYPE, NUM_BASEDIM> BaseDimensions;
typedef std::set<std::string> AllowedPrefixes;
struct UnitStruct {
  std::string symbol;
  Utype utype;
  MAGNITUDE_PRECISION magnitude;
  BaseDimensions dimensions;
  std::string definition;
  std::string name;
  bool use_prefixes;
  AllowedPrefixes allowed_prefixes;
};
namespace si {
  extern std::vector<UnitStruct> UnitList;
}
namespace esu {
  extern std::vector<UnitStruct> UnitList;
}
namespace emu {
  extern std::vector<UnitStruct> UnitList;
}
namespace gauss {
  extern std::vector<UnitStruct> UnitList;
}

}
  
#endif // PUQ_LISTS_H
