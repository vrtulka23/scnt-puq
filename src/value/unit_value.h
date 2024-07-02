#ifndef PUQ_VALUE_H
#define PUQ_VALUE_H

#include <vector>

#include "../settings.h"
#include "../lists/lists.h"

typedef std::array<EXPONENT_TYPE, NUM_BASEDIM> PhysicalDimensions;
class Dimensions {
public:
  MAGNITUDE_TYPE numerical; 
  PhysicalDimensions physical;
  std::vector<std::string> symbols;
  Utype utype;
  Dimensions();
  Dimensions(const MAGNITUDE_TYPE& n);
  Dimensions(const MAGNITUDE_TYPE& n, const PhysicalDimensions& p): utype(Utype::NUL), numerical(n), physical(p) {};
#ifdef MAGNITUDE_ERRORS
  Dimensions(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e);
  Dimensions(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const PhysicalDimensions& p): utype(Utype::NUL), numerical(m,e), physical(p) {};
#endif
  std::string to_string(char which='a') const;
  bool operator==(const Dimensions& d) const;
  bool operator!=(const Dimensions& d) const;
};

class BaseUnit {
public:
  std::string prefix;
  std::string unit;
  EXPONENT_TYPE exponent;
  BaseUnit() {};
  BaseUnit(const EXPONENT_INT_PRECISION& n): exponent(n) {};
#ifdef EXPONENT_FRACTIONS
  BaseUnit(const EXPONENT_INT_PRECISION& n, const EXPONENT_INT_PRECISION& d): exponent(n,d) {};
#endif
  BaseUnit(const std::string& p, const std::string& u, const EXPONENT_TYPE& e): prefix(p), unit(u), exponent(e) {};
#ifdef EXPONENT_FRACTIONS
  BaseUnit(const std::string& p, const std::string& u, const EXPONENT_INT_PRECISION& n, const EXPONENT_INT_PRECISION& d): prefix(p), unit(u), exponent(n,d) {};
#endif
  std::string to_string();
};

typedef std::vector<BaseUnit> BaseUnitsList;
class BaseUnits {
private:
  BaseUnitsList baseunits;
public:
  BaseUnits() {}
  BaseUnits(const std::string& s);
  BaseUnits(const BaseUnitsList& bu): baseunits(bu) {}
  void append(BaseUnit bu);
  void append(std::string p, std::string u, EXPONENT_TYPE e);
#ifdef EXPONENT_FRACTIONS
  void append(std::string p, std::string u, EXPONENT_INT_PRECISION n, EXPONENT_INT_PRECISION d);
#endif
  std::string to_string() const;
  const BaseUnit& operator[] (int index) const;
  friend BaseUnits operator+(const BaseUnits& bu1, const BaseUnits& bu2);
  friend BaseUnits operator-(const BaseUnits& bu1, const BaseUnits& bu2);
  void operator+=(const BaseUnits& bu);
  void operator-=(const BaseUnits& bu);
  void operator*=(const EXPONENT_TYPE& e);
  BaseUnitsList::const_iterator begin() const;
  BaseUnitsList::const_iterator end() const;
  std::size_t size() const;
  void rebase();
  Dimensions dimensions() const;
};

class ConversionException: public std::exception {
private:
  std::string message;  
public:
  ConversionException(std::string m) : message(m) {}
  ConversionException(const Dimensions& dim1, const Dimensions& dim2) {
    message = "Incompatible physical dimensions: "+dim1.to_string('p')+" != "+dim2.to_string('p');
  }
  ConversionException(const BaseUnits& bu1, const BaseUnits& bu2) {
    Dimensions dim1 = bu1.dimensions();
    Dimensions dim2 = bu2.dimensions();
    ConversionException(dim1, dim2);
  }
  const char * what () const noexcept override {
    return message.c_str();
  }
};

class UnitValue {
public:
  MAGNITUDE_TYPE magnitude;
  BaseUnits baseunits;
  UnitValue(): magnitude(1) {}
  UnitValue(const std::string& s);
  UnitValue(const MAGNITUDE_TYPE& m): magnitude(m) {}
  UnitValue(const MAGNITUDE_TYPE& m, const std::string& s);
  UnitValue(const MAGNITUDE_TYPE& m, const BaseUnits& bu): magnitude(m), baseunits(bu) {}
  UnitValue(const MAGNITUDE_TYPE& m, const BaseUnitsList& bul): magnitude(m), baseunits(bul) {}
#ifdef MAGNITUDE_ERRORS
  UnitValue(const MAGNITUDE_PRECISION& m, const BaseUnits& bu): magnitude(m), baseunits(bu) {}
  UnitValue(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bul): magnitude(m), baseunits(bul) {}
  UnitValue(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e): magnitude(m,e) {}
  UnitValue(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnits& bu): magnitude(m,e), baseunits(bu) {}
  UnitValue(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bul): magnitude(m,e), baseunits(bul) {}
#endif
  std::string to_string() const;
  friend UnitValue operator+(const UnitValue& v1, const UnitValue& v2);
  friend UnitValue operator-(const UnitValue& v1, const UnitValue& v2);
  friend UnitValue operator*(const UnitValue& v1, const UnitValue& v2);
  friend UnitValue operator/(const UnitValue& v1, const UnitValue& v2);
  void operator+=(const UnitValue& v);
  void operator-=(const UnitValue& v);
  void operator*=(const UnitValue& v);
  void operator/=(const UnitValue& v);
  void pow(const EXPONENT_TYPE& e);
  UnitValue convert(const std::string& s) const;
  UnitValue convert(const BaseUnits& bu) const;
  UnitValue convert(const UnitValue& v) const;
};

#endif // PUQ_VALUE_H
