#include "converter.h"

MAGNITUDE_TYPE Converter::_convert_linear(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2) {
  return (m1*dimensions1.numerical)/(m2*dimensions2.numerical);    
};

MAGNITUDE_TYPE Converter::_convert_temperature(MAGNITUDE_TYPE m) {
  std::string s1 = baseunits1[0].unit;
  std::string s2 = baseunits2[0].unit;
  MAGNITUDE_TYPE const9div5 = 9./5.;
  MAGNITUDE_TYPE const5div9 = 5./9.;
  if (s1==s2) {
    return m;
  } else {
    m = m * dimensions1.numerical;
  }
  if (s1=="K" && s2=="Cel") {
    m = m-(MAGNITUDE_TYPE)273.15;
  } else if (s1=="K" && s2=="degF") {
    m = (m-(MAGNITUDE_TYPE)273.15)*const9div5+(MAGNITUDE_TYPE)32;
  } else if (s1=="degR" && s2=="degF") {
    m = m*const9div5-(MAGNITUDE_TYPE)459.67;
  } else if (s1=="degR" && s2=="Cel") {
    m = (m*const9div5-(MAGNITUDE_TYPE)491.67)*const5div9;
  } else if (s1=="Cel" && s2=="K") {
    m = m+(MAGNITUDE_TYPE)273.15;
  } else if (s1=="Cel" && s2=="degF") {
    m = (m*const9div5)+(MAGNITUDE_TYPE)32;
  } else if (s1=="Cel" && s2=="degR") {
    m = ((m*const9div5)+(MAGNITUDE_TYPE)491.67)*const5div9;
  } else if (s1=="degF" && s2=="K") {
    m = ((m-(MAGNITUDE_TYPE)32)*const5div9)+(MAGNITUDE_TYPE)273.15;
    } else if (s1=="degF" && s2=="Cel") {
    m = (m-(MAGNITUDE_TYPE)32)*const5div9;
  } else if (s1=="degF" && s2=="degR") {
    m = (m+(MAGNITUDE_TYPE)459.67)*const5div9;
  } else {
    throw NoConvExcept();
  }
  return m / dimensions2.numerical;
}

Converter::Converter(const BaseUnits& bu1, const BaseUnits& bu2): baseunits1(bu1), baseunits2(bu2) {
  dimensions1 = bu1.dimensions();
  dimensions2 = bu2.dimensions();
  if (dimensions1!=dimensions2)
    throw ConvDimExcept(dimensions1, dimensions2);
};

MAGNITUDE_TYPE Converter::convert(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2) {
  //std::cout << baseunits1.to_string() << " " << baseunits2.to_string() << std::endl;
  //std::cout << std::bitset<8>((int)utype) << std::endl;
  if (((dimensions1.utype | dimensions2.utype) & Utype::TMP)==Utype::TMP) {
    if (baseunits1.size()==1 && baseunits2.size()==1 && m2==(MAGNITUDE_TYPE)1) {
      return _convert_temperature(m1);
    }  
  } else if (((dimensions1.utype & dimensions2.utype) & Utype::LIN)==Utype::LIN) {
    return _convert_linear(m1, m2);
  }
  throw NoConvExcept();
};

