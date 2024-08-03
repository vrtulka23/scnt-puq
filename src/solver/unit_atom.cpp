#include <regex>
#include <algorithm>

#include "../nostd.h"
#include "solver.h"

namespace puq {

  inline void _parse_number(std::string& expr, UnitValue& uv, const std::smatch& m) {
#ifdef MAGNITUDE_ERRORS
    // atom expression is a number with an uncertainty
    //std::cout << m[0] << "|" << m[1] << "|" << m[2] << "|" << m[3] << "|" << m[4] << "|" << m[5] << std::endl;
    //std::cout << m[6] << "|" << m[7] << "|" << m[8] << "|" << m[9] << "|" << m[10] << "|" << m[11] << std::endl;
    //std::cout << m[12] << "|" << m[13] << "|" << m[14] << "|" << m[15] << "|" << m[16] << "|" << m[17] << std::endl;
    if (m[6]=="") {
      uv.magnitude.value = nostd::to_number(expr);
    } else {
      std::string decimals = m[3].str()=="" ? "." : m[3].str();
      uv.magnitude.value = nostd::to_number(m[1].str()+decimals+m[8].str());
      if (m[10]=="")
	uv.magnitude.error = nostd::to_number(m[7]) * std::pow(10, 1-(int)decimals.size()); 
      else
	uv.magnitude.error = nostd::to_number(m[7]) * std::pow(10, 1-(int)decimals.size()+std::stoi(m[10]));
    }
#else
    // atom expression is a simple number
    uv.magnitude = nostd::to_number(expr);
#endif
  }

  inline void _parse_exponent(BaseUnit& bu, std::string& expr, const std::smatch& m) {
#ifdef EXPONENT_FRACTIONS
    bu.exponent = Exponent((m[2]==""?1:std::stoi(m[2])), (m[4]==""?1:std::stoi(m[4])));
#else
    bu.exponent = m[2]=="" ? 1 : std::stoi(m[2]);
#endif
    expr = std::string(m[1]);
  }
  
  inline void _parse_quantity(std::string& expr, UnitValue& uv, const std::smatch& m) {
    BaseUnit bu;
    _parse_exponent(bu, expr, m);
    bu.unit = expr;
    uv.magnitude = 1;
    uv.baseunits.append(bu);
  }
  
  inline void _parse_unit(std::string& expr, UnitValue& uv, const std::smatch& m, const std::string& expr_orig) {
    BaseUnit bu;
    _parse_exponent(bu, expr, m);
    // determine unit
    UnitStruct munit;  // current candidate unit
    for (auto unit: UnitSystem::Data->UnitList) {
      if (unit.symbol.size()>expr.size())           // symbol is longer than the expression
	continue;
      if (unit.symbol.size()<=munit.symbol.size())  // symbol is smaller or equal to the current candidate symbol
	continue;
      if (expr.compare(expr.size() - unit.symbol.size(), unit.symbol.size(), unit.symbol)==0) {
	munit = unit;
      }
    }
    if (munit.symbol=="") {
      throw AtomParsingExcept("Unknown unit base: "+expr_orig);
    } else {
      bu.unit = munit.symbol;
    }
    expr = expr.substr(0,expr.size()-bu.unit.size());
    // determine prefix
    if (expr.size()>0) {
      // no prefixes are allowed
      if (!munit.use_prefixes)
	throw AtomParsingExcept("Prefixes are not allowed for this unit: "+expr_orig);
      // is symbol in the prefix list
      if (UnitPrefixList.find(expr) == UnitPrefixList.end())
	throw AtomParsingExcept("Unknown prefix '"+expr+"' detected in unit: "+expr_orig);
      else
	bu.prefix = expr;
      // is prefix allowed
      if (munit.allowed_prefixes.size()>0) {
	if (std::find(munit.allowed_prefixes.begin(), munit.allowed_prefixes.end(), bu.prefix) == munit.allowed_prefixes.end()) {
	  std::stringstream ss;
	  ss << "Given prefix is not allowed in unit: "+expr_orig << std::endl;
	  ss << "Allowed prefixes are:";
	  for (auto prefix: munit.allowed_prefixes) {
	    ss << " " << prefix;
	  }
	  throw AtomParsingExcept(ss.str());
	}
      }
    }
    // fill UnitValue properties
    uv.magnitude = 1;
    uv.baseunits.append(bu);
  }
  
UnitValue UnitAtom::from_string(std::string expr_orig) {
  std::string expr = expr_orig;
  struct UnitValue uv;
  std::smatch m;
#ifdef EXPONENT_FRACTIONS
  std::regex rx_unit("^(\\[?[a-zA-Z0_%']+\\]?)([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)$");
  std::regex rx_quantity("^(\\<[a-zA-Z_]+\\>)([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)$");
#else
  std::regex rx_unit("^(\\[?[a-zA-Z0_%']+\\]?)([+-]?[0-9]*)$");
  std::regex rx_quantity("^(\\<[a-zA-Z_]+\\>)([+-]?[0-9]*)$");
#endif
#ifdef MAGNITUDE_ERRORS
  std::regex rx_number("^((\\+|-)?[0-9]+)(\\.(([0-9]+)?))?(\\(([0-9]+)\\))?((e|E)((\\+|-)?[0-9]+))?$");
#else
  std::regex rx_number("^((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?$");
#endif
  if (std::regex_match(expr, m, rx_number)) {
    _parse_number(expr, uv, m);
  }
  else if (std::regex_match(expr, m, rx_quantity)) {
    _parse_quantity(expr, uv, m);
  }
  else if (std::regex_match(expr, m, rx_unit)) { 
    _parse_unit(expr, uv, m, expr_orig);
  } else {
    throw AtomParsingExcept("Invalid unit expression: "+expr_orig);
  }
  return uv;
}

std::string UnitAtom::to_string() {
  return value.to_string();
}

void UnitAtom::math_power(EXPONENT_TYPE &e) {
  value.pow(e);
}

void UnitAtom::math_multiply(UnitAtom *other) {
  value *= other->value;
}

void UnitAtom::math_divide(UnitAtom *other) {
  value /= other->value;
}

}
