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
  
const Utype UT_LIN_BAS     = Utype::LIN|Utype::BAS;
const Utype UT_LIN_BAS_CST = Utype::LIN|Utype::BAS|Utype::CST;
const Utype UT_LIN_BAS_TMP = Utype::LIN|Utype::BAS|Utype::TMP;
const Utype UT_LIN_TMP     = Utype::LIN|Utype::TMP;
const Utype UT_LIN_CST     = Utype::LIN|Utype::CST;
const Utype UT_LIN_LOG     = Utype::LIN|Utype::LOG;
  
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

// System of units
  
template<typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2){
  std::vector<T> vr(std::begin(v1), std::end(v1));
  vr.insert(std::end(vr), std::begin(v2), std::end(v2));
  return vr;
}
  
#ifdef EXPONENT_FRACTIONS
typedef EXPONENT_INT_PRECISION FRC[2];
#endif
typedef std::vector<UnitStruct> UnitListType;
  
namespace si {
  extern const UnitListType UnitList;
}
  
#ifdef UNITS_SYSTEM_CGS
namespace cgs {
  extern const UnitListType UnitListCGS;
  extern const UnitListType UnitListESU;
  extern const UnitListType UnitListEMU;
  extern const UnitListType UnitListGauss;  
};
#endif
  
#ifdef UNITS_SYSTEM_AU
namespace au {
  extern const UnitListType UnitList;
}
#endif
  
// Default sytem of units
extern const UnitListType* UnitList;

// Changing unit systems
class UnitSystem {
  const UnitListType* previous;
  bool closed;
public:
  enum Stype {
    SI,
#ifdef UNITS_SYSTEM_CGS
    ESU, GAUSS, EMU,
#endif
#ifdef UNITS_SYSTEM_AU
    AU
#endif
  };
  UnitSystem(Stype st);
  ~UnitSystem();
  void close();
};
  
}
  
#endif // PUQ_LISTS_H
