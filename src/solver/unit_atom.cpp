#include <regex>
#include <algorithm>

#include "../nostd.h"
#include "solver.h"

namespace puq {

UnitValue UnitAtom::from_string(std::string expr_orig) {
  std::string expr = expr_orig;
  struct UnitValue uv;
  std::smatch m;
#ifdef EXPONENT_FRACTIONS
  std::regex rx_unit("^(\\[?[a-zA-Z0_%']+\\]?)([+-]?[0-9]*)("+std::string(SYMBOL_FRACTION)+"([0-9]+)|)$");
#else
  std::regex rx_unit("^(\\[?[a-zA-Z0_%']+\\]?)([+-]?[0-9]*)$");
#endif
#ifdef MAGNITUDE_ERRORS
  std::regex rx_number("^((\\+|-)?[0-9]+)(\\.(([0-9]+)?))?(\\(([0-9]+)\\))?((e|E)((\\+|-)?[0-9]+))?$");
  if (std::regex_match(expr, m, rx_number)) {       // atom expression is a number with an uncertainty
    //std::cout << m[0] << "|" << m[1] << "|" << m[2] << "|" << m[3] << "|" << m[4] << "|" << m[5] << std::endl;
    //std::cout << m[6] << "|" << m[7] << "|" << m[8] << "|" << m[9] << "|" << m[10] << "|" << m[11] << std::endl;
    //std::cout << m[12] << "|" << m[13] << "|" << m[14] << "|" << m[15] << "|" << m[16] << "|" << m[17] << std::endl;
    if (m[6]=="") {
      uv.magnitude.value = nostd::ston(expr);
    } else {
      std::string decimals = m[3].str()=="" ? "." : m[3].str();
      uv.magnitude.value = nostd::ston(m[1].str()+decimals+m[8].str());
      if (m[10]=="")
	uv.magnitude.error = nostd::ston(m[7]) * std::pow(10, 1-(int)decimals.size()); 
      else
	uv.magnitude.error = nostd::ston(m[7]) * std::pow(10, 1-(int)decimals.size()+std::stoi(m[10]));
    }
  }
#else
  std::regex rx_number("^((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?$");
  if (std::regex_match(expr, rx_number)) {          // atom expression is a simple number
    uv.magnitude = nostd::ston(expr);
  }
#endif
  else if (std::regex_match(expr, m, rx_unit)) {  // atom expression has dimensions
    BaseUnit bu;
    // register exponent values
#ifdef EXPONENT_FRACTIONS
    bu.exponent = Exponent((m[2]==""?1:std::stoi(m[2])), (m[4]==""?1:std::stoi(m[4])));
#else
    bu.exponent = m[2]=="" ? 1 : std::stoi(m[2]);
#endif
    expr = m[1];
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
      if (!munit.use_prefixes)
	throw AtomParsingExcept("Prefixes are not allowed for this unit: "+expr_orig);
      for (auto prefix: UnitPrefixList) {	
	if (prefix.symbol==expr) {
	  bu.prefix = prefix.symbol;
	  break;
	}
      }
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
      if (bu.prefix.size()==0) {
	throw AtomParsingExcept("Unknown unit prefix: "+expr_orig);
      }
    }
    // fill UnitValue properties
    uv.magnitude = 1;
    uv.baseunits.append(bu);
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
