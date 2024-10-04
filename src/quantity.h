#ifndef PUQ_QUANTITY_H
#define PUQ_QUANTITY_H

#include "settings.h"
#include "value/value.h"
#include "solver/solver.h"

namespace puq {
  
  class Quantity {
    void preprocess(std::string& expression, SystemType& system) const;
    UnitValue _convert_without_context(UnitSystem& us, const SystemType stt) const;
    UnitValue _convert_with_context(UnitSystem& us, const SystemType stt, QuantityListType::iterator& qs1, QuantityListType::iterator& qs2, const std::string& q) const;
  public:
    SystemType stype;
    UnitValue value;
    Quantity(): stype(UnitSystem::System) {};
    Quantity(std::string s, const SystemType system = SystemType::NONE);
    Quantity(const UnitValue& v, const SystemType system = UnitSystem::System);
    Quantity(const MAGNITUDE_TYPE& m, std::string s, const SystemType system = SystemType::NONE);
    Quantity(const MAGNITUDE_TYPE& m, const SystemType system = UnitSystem::System);
    Quantity(const MAGNITUDE_TYPE& m, const BaseUnitsList& bu, const SystemType system = UnitSystem::System);
#ifdef MAGNITUDE_ERRORS
    Quantity(const MAGNITUDE_PRECISION& m, std::string s, const SystemType system = SystemType::NONE);
    Quantity(const MAGNITUDE_PRECISION& m, const SystemType system = UnitSystem::System);
    Quantity(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bu, const SystemType system = UnitSystem::System);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, std::string s, const SystemType system = SystemType::NONE);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const SystemType system = UnitSystem::System);
    Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bu, const SystemType system = UnitSystem::System);
#ifdef MAGNITUDE_ARRAYS
    Quantity(const Array& m, std::string s, const SystemType system = SystemType::NONE);
    Quantity(const Array& m, const SystemType system = UnitSystem::System);
    Quantity(const Array& m, const BaseUnitsList& bu, const SystemType system = UnitSystem::System);
    Quantity(const Array& m, const Array& e, std::string s, const SystemType system = SystemType::NONE);
    Quantity(const Array& m, const Array& e, const SystemType system = UnitSystem::System);
    Quantity(const Array& m, const Array& e, const BaseUnitsList& bu, const SystemType system = UnitSystem::System);
#endif
#endif
    std::string unit_system() const;
    std::size_t size() const;
    std::string to_string(int precision=std::cout.precision()) const;
    // quantity operations
    friend Quantity operator+(const Quantity& q1, const Quantity& q2);
    friend Quantity operator-(const Quantity& q1, const Quantity& q2);
    friend Quantity operator*(const Quantity& q1, const Quantity& q2);
    friend Quantity operator/(const Quantity& q1, const Quantity& q2);
    // scalar operations
    friend Quantity operator+(const MAGNITUDE_PRECISION& m, const Quantity& q);
    friend Quantity operator-(const MAGNITUDE_PRECISION& m, const Quantity& q);
    friend Quantity operator*(const MAGNITUDE_PRECISION& m, const Quantity& q);
    friend Quantity operator/(const MAGNITUDE_PRECISION& m, const Quantity& q);
    friend Quantity operator+(const Quantity& q, const MAGNITUDE_PRECISION& m);
    friend Quantity operator-(const Quantity& q, const MAGNITUDE_PRECISION& m);
    friend Quantity operator*(const Quantity& q, const MAGNITUDE_PRECISION& m);
    friend Quantity operator/(const Quantity& q, const MAGNITUDE_PRECISION& m);
#ifdef MAGNITUDE_ARRAYS
    // array operations
    friend Quantity operator+(const Array& a, const Quantity& q);
    friend Quantity operator-(const Array& a, const Quantity& q);
    friend Quantity operator*(const Array& a, const Quantity& q);
    friend Quantity operator/(const Array& a, const Quantity& q);
    friend Quantity operator+(const Quantity& q, const Array& a);
    friend Quantity operator-(const Quantity& q, const Array& a);
    friend Quantity operator*(const Quantity& q, const Array& a);
    friend Quantity operator/(const Quantity& q, const Array& a);
#endif
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
    Quantity convert(std::string s, SystemType system = SystemType::NONE, const std::string& q = "") const;
    Quantity rebase_prefixes();
  };  
  
}

#endif // PUQ_QUANTITY_H
