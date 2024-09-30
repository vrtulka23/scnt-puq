#ifndef PUQ_QUANTITY_H
#define PUQ_QUANTITY_H

#include "settings.h"
#include "value/value.h"
#include "solver/solver.h"

namespace puq {
  
  class Quantity {
    void preprocess(std::string& expression, SystemType& stt) const;
    UnitValue _convert_without_context(UnitSystem& us, const SystemType stt) const;
    UnitValue _convert_with_context(UnitSystem& us, const SystemType stt, QuantityListType::iterator& qs1, QuantityListType::iterator& qs2, const std::string& q) const;
  public:
    SystemType stype;
    UnitValue value;
    Quantity();
    Quantity(std::string s, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const UnitValue& v, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_TYPE& m, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_TYPE& m, const BaseUnitsList& bu, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_TYPE& m, std::string s, const SystemType system = UnitSystem::DefaultSystem);
#ifdef MAGNITUDE_ERRORS
    Quantity(const MAGNITUDE_PRECISION& m, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bu, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_PRECISION& m, std::string s, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bu, const SystemType system = UnitSystem::DefaultSystem);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, std::string s, const SystemType system = UnitSystem::DefaultSystem);
#endif
    std::string unit_system() const;
    std::string to_string(int precision=std::cout.precision()) const;
    friend Quantity operator+(const Quantity& q1, const Quantity& q2);
    friend Quantity operator-(const Quantity& q1, const Quantity& q2);
    friend Quantity operator*(const Quantity& q1, const Quantity& q2);
    friend Quantity operator/(const Quantity& q1, const Quantity& q2);
    friend Quantity operator+(const Quantity& q);
    friend Quantity operator-(const Quantity& q);
    friend std::ostream& operator<<(std::ostream& os, const Quantity& q);
    void operator+=(Quantity& q);
    void operator-=(Quantity& q);
    void operator*=(Quantity& q);
    void operator/=(Quantity& q);
    Quantity convert(const Dformat& format) const;
    Quantity convert(const Quantity& q) const;
    Quantity convert(const UnitValue& uv) const;
    Quantity convert(const UnitValue& uv, const SystemType system, const std::string& q = "") const;
    Quantity convert(const BaseUnits& bu) const;
    Quantity convert(const BaseUnits& bu, const SystemType system, const std::string& q = "") const;
    Quantity convert(std::string s, const SystemType system = SystemType::NONE, const std::string& q = "") const;
  };  
  
}

#endif // PUQ_QUANTITY_H
