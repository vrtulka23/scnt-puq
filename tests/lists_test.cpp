#include <gtest/gtest.h>
#include <set>

#include "../src/lists/lists.h"
#include "../src/value/unit_value.h"

inline void check_symbol(std::set<std::string>& set, std::string symbol) {
  auto result = set.insert(symbol);
  EXPECT_EQ(result.second, true) << "Duplicated symbol: "+symbol;
}

TEST(Lists, UniqueSymbols) {
  
  // unique prefixes
  std::set<std::string> prefixes;
  for (auto prefix: UnitPrefixList) {
    check_symbol(prefixes, prefix.symbol);
  }

  // unique unit symbols
  std::set<std::string> units;
  for (auto unit: UnitList) {
    // unique unit symbol without a prefix
    check_symbol(units, unit.symbol);
    if (unit.use_prefixes) {
      if (unit.allowed_prefixes.size()>0) {
	// unique symbols with allowed prefixes
	for (auto prefix: unit.allowed_prefixes) {
	  check_symbol(units, std::string(prefix+unit.symbol));
	}	
      } else {
	// unique symbols with all prefixes
	for (auto prefix: prefixes) {
	  check_symbol(units, std::string(prefix+unit.symbol));
	}
      }
    }
  }
  
}

TEST(Lists, UnitDefinitions) {

  for (auto unit: UnitList) {
    
    //if ((unit.utype & Utype::LIN)!=Utype::LIN) // check only linear units
    //  continue;
    if ((unit.utype & Utype::BAS)==Utype::BAS) // ignore base units
      continue;

    Dimensions dim1(unit.magnitude, unit.dimensions);
    std::string m1 = dim1.to_string();

    UnitValue uv2(unit.definition);
    Dimensions dim2 = uv2.baseunits.dimensions();
    dim2 = Dimensions(uv2.magnitude*dim2.numerical, dim2.physical);
    std::string m2 = dim2.to_string();

#ifdef UNITS_LOGARITHMIC
    if (unit.utype == Utype::LOG) {
      // For logarithmic units compare only the physical dimensionality
      m1 = dim1.to_string(Dformat::PHYS);
      m2 = dim2.to_string(Dformat::PHYS);
    }
#endif
    
    EXPECT_EQ(m1, m2) << "Numerical dimension of unit '" << unit.symbol
		      << "' does not match with its definition: "
		      << m1 << " != " << m2;
  }  
  
}
