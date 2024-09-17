#include <iostream>

#include "quantity.h"

namespace puq {

  void Quantity::preprocess(std::string& s, SystemDataType*& stt) const {
#ifdef PREPROCESS_SYSTEM
    for (auto system: SystemData::SystemMap) {
      std::string symbol = system.first+SYMBOL_SYSTEM;
      if (s.rfind(symbol, 0) == 0) {
	s = s.substr(symbol.size(), s.size()-symbol.size());
	stt = system.second;
	break;
      }
    }
#endif
#ifdef PREPROCESS_SYMBOLS
    // replace non standard symbols
    std::unordered_map<std::string, std::string> dict {
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
#endif
  }
  
  Quantity::Quantity(std::string s, SystemDataType& st) {
    SystemDataType* stt = &st;
    preprocess(s, stt);
    stype = stt;
    UnitSystem us(stype);
    value = UnitValue(s);
  }
  
  Quantity::Quantity(const UnitValue& v, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = v;
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE& m, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m);
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE& m, const BaseUnitsList& bu, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, bu);
  }
  
  Quantity::Quantity(const MAGNITUDE_TYPE &m, std::string s, SystemDataType& st) {
    SystemDataType* stt = &st;
    preprocess(s, stt);
    stype = stt;
    UnitSystem us(stype); 
    value = UnitValue(m, s);
  }
  
#ifdef MAGNITUDE_ERRORS
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const BaseUnitsList& bu, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, bu);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, std::string s, SystemDataType& st) {
    SystemDataType* stt = &st;
    preprocess(s, stt);
    stype = stt;
    UnitSystem us(stype);
    Magnitude mag(m);
    value = UnitValue(mag, s);
  }

  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, e);
  }
  
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, const BaseUnitsList& bu, SystemDataType& st): stype(&st) {
    UnitSystem us(stype);
    value = UnitValue(m, e, bu);
  }
 
  Quantity::Quantity(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e, std::string s, SystemDataType& st) {
    SystemDataType* stt = &st;
    preprocess(s, stt);
    stype = stt;
    UnitSystem us(stype);
    Magnitude mag(m,e);
    value = UnitValue(mag, s);
  }
  
#endif
  
  std::string Quantity::to_string(int precision) {
    UnitSystem us(stype);
    return value.to_string(precision);
  }
  
  Quantity operator+(const Quantity& q1, const Quantity& q2) {
    UnitSystem us(q1.stype);
    if (q1.stype==q2.stype) {
      return Quantity(q1.value+q2.value);
    } else {
      Quantity q3 = q2.convert(q1.value.baseunits, *q1.stype);
      return Quantity(q1.value+q3.value);
    }
  }
  
  Quantity operator-(const Quantity& q1, const Quantity& q2) {
    UnitSystem us(q1.stype);
    if (q1.stype==q2.stype) {
      return Quantity(q1.value-q2.value);
    } else {
      Quantity q3 = q2.convert(q1.value.baseunits, *q1.stype);
      return Quantity(q1.value-q3.value);
    }
  }
  
  Quantity operator*(const Quantity& q1, const Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value*q2.value);
  }
  
  Quantity operator/(const Quantity& q1, const Quantity& q2) {
    if (q1.stype!=q2.stype)
      throw UnitSystemExcept(&q1, &q2);
    UnitSystem us(q1.stype);
    return Quantity(q1.value/q2.value);
  }
  
  Quantity operator+(const Quantity& q) {
    return Quantity(+q.value);
  }
  
  Quantity operator-(const Quantity& q) {
    return Quantity(-q.value);
  }
  
  void Quantity::operator+=(Quantity& q) {
    UnitSystem us(stype);
    if (stype==q.stype) {
      value += q.value;
    } else {
      Quantity qc = q.convert(value.baseunits, *stype);
      value += qc.value;
    }
  }
  
  void Quantity::operator-=(Quantity& q) {
    UnitSystem us(stype);
    if (stype==q.stype) {
      value -= q.value;
    } else {
      Quantity qc = q.convert(value.baseunits, *stype);
      value -= qc.value;
    }
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

  UnitValue Quantity::_convert_without_context(UnitSystem& us, SystemDataType* stt) const {
    Dimensions dim = value.baseunits.dimensions();
    us.change(stt);         // change the unit system
    return UnitValue(value.magnitude, dim);
  }

  UnitValue Quantity::_convert_with_context(UnitSystem& us, SystemDataType* stt,
					    QuantityListType::iterator& qs1, QuantityListType::iterator& qs2,
					    const std::string& q) const {
    UnitValue uv = value;
    if (qs1->second.sifactor != "")
      uv *= UnitValue(SYMBOL_SIFACTOR_START+q+SYMBOL_SIFACTOR_END);
    uv = uv.convert(SYMBOL_QUANTITY_START+q+SYMBOL_QUANTITY_END);
    us.change(stt);    
    uv = UnitValue(uv.magnitude, SYMBOL_QUANTITY_START+q+SYMBOL_QUANTITY_END);
    if (qs2->second.sifactor != "") {
      uv /= UnitValue(SYMBOL_SIFACTOR_START+q+SYMBOL_SIFACTOR_END);
    }
    return uv;
  }  

  // convert using quantity
  Quantity Quantity::convert(const Quantity& q) const {
    return convert(q.value, *q.stype);
  }

  // convert using unit value
  Quantity Quantity::convert(const UnitValue& uv1) const {
    UnitSystem us(stype);
    UnitValue uv2 = value.convert(uv1);
    return Quantity(uv2);
  }

  Quantity Quantity::convert(const UnitValue& uv1, SystemDataType& st, const std::string& q) const {
    SystemDataType* stt = &st;
    UnitSystem us(stype);
    if (stype == stt) {
      return convert(uv1);
    } else if (q == "") {
      UnitValue uv2 = _convert_without_context(us, stt);
      return Quantity(uv2.convert(uv1), *stt);
    } else {
      QuantityListType::iterator qs1 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs1==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stt);       
      QuantityListType::iterator qs2 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs2==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stype);
      if (qs1->second.sifactor == "" && qs2->second.sifactor == "") {
	UnitValue uv2 = _convert_without_context(us, stt);
	return Quantity(uv2.convert(uv1), *stt);
      } else {
	UnitValue uv2 = _convert_with_context(us, stt, qs1, qs2, q);
	return Quantity(uv2.convert(uv1), *stt);
      }
    }
  }

  // convert using base units
  Quantity Quantity::convert(const BaseUnits& bu) const {
    UnitSystem us(stype);
    UnitValue uv = value.convert(bu);
    return Quantity(uv);
  }

  Quantity Quantity::convert(const BaseUnits& bu, SystemDataType& st, const std::string& q) const {
    SystemDataType* stt = &st;
    UnitSystem us(stype);
    if (stype == stt) {
      return convert(bu);
    } else if (q == "") {
      UnitValue uv = _convert_without_context(us, stt);
      return Quantity(uv.convert(bu), *stt);
    } else {
      QuantityListType::iterator qs1 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs1==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stt);       
      QuantityListType::iterator qs2 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs2==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stype);
      if (qs1->second.sifactor == "" && qs2->second.sifactor == "") {
	UnitValue uv = _convert_without_context(us, stt);
	return Quantity(uv.convert(bu), *stt);
      } else {
	UnitValue uv = _convert_with_context(us, stt, qs1, qs2, q);
	return Quantity(uv.convert(bu), *stt);
      }
    }
  }
  
  // convert using string expression
  Quantity Quantity::convert(std::string s, const std::string& q) const {
    SystemDataType* stt = NULL;
    preprocess(s, stt);
    if (stt!=NULL) {
      return convert(s, *stt, q);
    } else {
      UnitSystem us(stype);
      UnitValue uv = value.convert(s);
      return Quantity(uv);
    }
  }

  Quantity Quantity::convert(std::string s, SystemDataType& st, const std::string& q) const {
    SystemDataType* stt = &st;
    preprocess(s, stt);
    UnitSystem us(stype);
    if (stype == stt) {
      return convert(s);
    } else if (q == "") {
      UnitValue uv = _convert_without_context(us, stt);
      return Quantity(uv.convert(s), *stt);
    } else {      
      QuantityListType::iterator qs1 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs1==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stt);  
      QuantityListType::iterator qs2 = puq::UnitSystem::Data->QuantityList.find(q);
      if (qs2==puq::UnitSystem::Data->QuantityList.end())
	throw UnitSystemExcept("Quantity symbol not found: "+q);
      us.change(stype);
      if (qs1->second.sifactor == "" && qs2->second.sifactor == "") {
	UnitValue uv = _convert_without_context(us, stt);
	return Quantity(uv.convert(s), *stt);
      } else {
	UnitValue uv = _convert_with_context(us, stt, qs1, qs2, q);
	return Quantity(uv.convert(s), *stt);
      }
    }
  }
    
}
