#include <iostream>

#include "quantity.h"

namespace puq {

#ifdef PREPROCESS_EXPRESSIONS
  void Quantity::preprocess(std::string& s) {
    // replace non standard symbols
    std::map<std::string, std::string> dict {
      {"\u00D710", SYMBOL_EXPONENT},  // ×10 -> e
      {"\u2212",   SYMBOL_MINUS},     // −   -> -
      {"\u22C5",   SYMBOL_MULTIPLY},  // ⋅   -> *
      {" ",        SYMBOL_MULTIPLY},  //     -> *
    };
    for (auto item: dict) {
      size_t pos = s.find(item.first);
      while (pos != std::string::npos) {
	s.replace(pos, item.first.size(), item.second);
	pos = s.find(item.first, pos + item.first.size());
      }
    }
  }
#endif
  
  Quantity::Quantity(std::string s, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
#ifdef PREPROCESS_EXPRESSIONS
    preprocess(s);
#endif
    value = UnitValue(s);
  }
  
  Quantity::Quantity(const UnitValue& v, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = v;
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE& m, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m);
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE& m, const BaseUnitsList& bu, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, bu);
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE &m, std::string s, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype); 
#ifdef PREPROCESS_EXPRESSIONS
    preprocess(s);
#endif
    value = UnitValue(m, s);
  }
  
#ifdef MAGNITUDE_ERRORS
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bu, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, bu);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, std::string s, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    Magnitude mag(m);
#ifdef PREPROCESS_EXPRESSIONS
    preprocess(s);
#endif
    value = UnitValue(mag, s);
  }

  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, e);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bu, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, e, bu);
  }
 
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, std::string s, const SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    Magnitude mag(m,e);
#ifdef PREPROCESS_EXPRESSIONS
    preprocess(s);
#endif
    value = UnitValue(mag, s);
  }
  
#endif
  
  std::string Quantity::to_string() {
    UnitSystem us(stype);
    return value.to_string();
  }
  
  Quantity operator+(Quantity& q1, Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value+q2.value);
  }
  
  Quantity operator-(Quantity& q1, Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value-q2.value);
  }
  
  Quantity operator*(Quantity& q1, Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value*q2.value);
  }
  
  Quantity operator/(Quantity& q1, Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value/q2.value);
  }
  
  void Quantity::operator+=(Quantity& q) {
    if (stype!=q.stype)
      throw UnitSystemExcept(this, &q);
    UnitSystem us(stype);
    value += q.value;
  }
  
  void Quantity::operator-=(Quantity& q) {
    if (stype!=q.stype)
      throw UnitSystemExcept(this, &q);
    UnitSystem us(stype);
    value -= q.value;
  }
  
  void Quantity::operator*=(Quantity& q) {
    if (stype!=q.stype)
      throw UnitSystemExcept(this, &q);
    UnitSystem us(stype);
    value *= q.value;
  }
  
  void Quantity::operator/=(Quantity& q) {
    if (stype!=q.stype)
      throw UnitSystemExcept(this, &q);
    UnitSystem us(stype);
    value /= q.value;
  }

  Quantity Quantity::convert(const Quantity& q) const {
    return convert(q.value, *q.stype);
  }
  
  Quantity Quantity::convert(const std::string& s) const {
    UnitSystem us(stype);
    UnitValue uv = value.convert(s);
    return Quantity(uv);
  }
  
  Quantity Quantity::convert(const std::string& s, const SystemDataType& st) const {
    if (stype == &st) {
      return convert(s);
    } else {
      UnitSystem us(stype);
      Dimensions dim = value.baseunits.dimensions();
      us.change(&st);         // change the unit system
      UnitValue uv(value.magnitude, dim);
      return Quantity(uv.convert(s));
    }
  }
  
  Quantity Quantity::convert(const UnitValue& uv1) const {
    UnitSystem us(stype);
    UnitValue uv2 = value.convert(uv1);
    return Quantity(uv2);
  }
  
  Quantity Quantity::convert(const UnitValue& uv1, const SystemDataType& st) const {
    if (stype == &st) {
      return convert(uv1);
    } else {
      UnitSystem us(stype);
      Dimensions dim = value.baseunits.dimensions();
      us.change(&st);        // change the unit system
      UnitValue uv2(value.magnitude, dim);
      return Quantity(uv2.convert(uv1));
    }
  }
  
}
