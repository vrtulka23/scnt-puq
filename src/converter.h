#ifndef PUQ_CONVERTER_H
#define PUQ_CONVERTER_H

#include <bitset>
#include <memory> 

#include "value/unit_value.h"

class ConvDimExcept: public std::exception {
private:
  std::string message;  
public:
  ConvDimExcept(std::string m) : message(m) {}
  ConvDimExcept(const Dimensions& dim1, const Dimensions& dim2) {
    message = "Incompatible physical dimensions: "+dim1.to_string(Dformat::PHYS)+" != "+dim2.to_string(Dformat::PHYS);
  }
  ConvDimExcept(const BaseUnits& bu1, const BaseUnits& bu2) {
    Dimensions dim1 = bu1.dimensions();
    Dimensions dim2 = bu2.dimensions();
    ConvDimExcept(dim1, dim2);
  }
  const char * what () const noexcept override {
    return message.c_str();
  }
};

class NoConvExcept: public std::exception {
private:
  std::string message;  
public:
  NoConvExcept() : message("This conversion is not available!") {}
  const char * what () const noexcept override {
    return message.c_str();
  }
};


class Converter {
private:
  BaseUnits baseunits1;
  BaseUnits baseunits2;
  Dimensions dimensions1;
  Dimensions dimensions2;
  MAGNITUDE_TYPE _convert_linear(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2);
  MAGNITUDE_TYPE _convert_temperature(MAGNITUDE_TYPE m);
public:
  Converter() {};
  Converter(const BaseUnits& bu1, const BaseUnits& bu2);
  Converter(const std::string& s1, const std::string& s2): Converter(BaseUnits(s1), BaseUnits(s2)) {};
  MAGNITUDE_TYPE convert(const MAGNITUDE_TYPE& m1, const MAGNITUDE_TYPE& m2);
};

#endif // PUQ_CONVERTER_H
