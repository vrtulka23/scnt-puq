#include <gtest/gtest.h>
#include <set>

#include "../src/lists/lists.h"
#include "../src/value/value.h"

inline void check_symbol(std::set<std::string>& set, std::string symbol) {
  auto result = set.insert(symbol);
  EXPECT_EQ(result.second, true) << "Duplicated symbol: "+symbol;
}

void test_unit_symbols() {
  
  // unique prefixes
  std::set<std::string> prefixes;
  for (auto prefix: puq::UnitPrefixList) {
    check_symbol(prefixes, prefix.symbol);
  }
  // unique unit symbols
  std::set<std::string> units;
  for (auto unit: puq::UnitSystem::Data->UnitList) {
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

void test_unit_definitions() {
  
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    
    //std::cout << "hello " << unit.symbol << " " << std::bitset<8>((int)unit.utype) << std::endl;
    //if ((unit.utype & Utype::LIN)!=Utype::LIN) // check only linear units
    //  continue;
    if (unit.utype==puq::Utype::NUL) // ignore null units
      continue;
    if ((unit.utype & puq::Utype::BAS)==puq::Utype::BAS) // ignore base units
      continue;    
    
    puq::Dimensions dim1(unit.magnitude, unit.dimensions);
    std::string m1 = dim1.to_string();

    puq::UnitValue uv2(unit.definition);
    puq::Dimensions dim2 = uv2.baseunits.dimensions();
    dim2 = puq::Dimensions(uv2.magnitude*dim2.numerical, dim2.physical);
    std::string m2 = dim2.to_string();

#ifdef UNITS_LOGARITHMIC
    if (unit.utype == puq::Utype::LOG) {
      // For logarithmic units compare only the physical dimensionality
      m1 = dim1.to_string(puq::Dformat::PHYS);
      m2 = dim2.to_string(puq::Dformat::PHYS);
    }
#endif
    
    EXPECT_EQ(m1, m2) << "Numerical dimension of unit '" << unit.symbol
		      << "' does not match with its definition: "
		      << m1 << " != " << m2;
  }  
  
}

void test_quantities() {
  for (auto quantity: puq::UnitSystem::Data->QuantityList) {
    
    // check if quantity symbol is in the quantity name list
    EXPECT_FALSE(puq::QuantityNames.find(quantity.symbol)==puq::QuantityNames.end())
      << "Quantity symbol is not in a name list: " << quantity.symbol;
    
    // check if quantity definition expression is valid 
    EXPECT_NO_THROW(puq::UnitValue(quantity.definition));
    
  }  
}

TEST(Lists, QuantitySymbols) {

  std::set<std::string> quantities;
  for (auto quantity: puq::QuantityNames) {
    check_symbol(quantities, quantity.first);
  }  
  
}

TEST(Lists, UnitDefinitionsSI) {

  test_unit_symbols();
  test_unit_definitions();
  test_quantities();
  
}

#ifdef UNIT_SYSTEM_CGS

TEST(Lists, UnitDefinitionsESU) {

  puq::UnitSystem us(puq::SystemData::ESU);
  test_unit_symbols();
  test_unit_definitions();
  
}

TEST(Lists, UnitDefinitionsGauss) {

  puq::UnitSystem us(puq::SystemData::GAUSS);
  test_unit_symbols();
  test_unit_definitions();
  
}

TEST(Lists, UnitDefinitionsEMU) {

  puq::UnitSystem us(puq::SystemData::EMU);
  test_unit_symbols();
  test_unit_definitions();
    
}

#endif


#ifdef UNIT_SYSTEM_AU

TEST(Lists, UnitDefinitionsAU) {

  puq::UnitSystem us(puq::SystemData::AU);
  test_unit_symbols();
  test_unit_definitions();
  test_quantities();

}

#endif

#ifdef UNIT_SYSTEM_EUS

TEST(Lists, UnitDefinitionsIU) {

  puq::UnitSystem us(puq::SystemData::IU);
  test_unit_symbols();
  test_unit_definitions();

}

TEST(Lists, UnitDefinitionsUS) {

  puq::UnitSystem us(puq::SystemData::US);
  test_unit_symbols();
  test_unit_definitions();

}

#endif
