#include <gtest/gtest.h>
#include <set>

#include "../src/lists/lists.h"
#include "../src/value/value.h"
#include "../src/solver/solver.h"

inline void check_symbol(std::set<std::string>& set, std::string symbol) {
  auto result = set.insert(symbol);
  EXPECT_EQ(result.second, true) << "Duplicated symbol: "+symbol;
}

void test_unit_symbols() {
  
  // unique prefixes
  std::set<std::string> prefixes;
  for (auto prefix: puq::UnitPrefixList) {
    check_symbol(prefixes, prefix.first);
  }
  // unique unit symbols
  std::set<std::string> units;
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    // unique unit symbol without a prefix
    check_symbol(units, unit.first);
    if (unit.second.use_prefixes) {
      if (unit.second.allowed_prefixes.size()>0) {
	// unique symbols with allowed prefixes
	for (auto& prefix: unit.second.allowed_prefixes) {
	  check_symbol(units, std::string(prefix+unit.first));
	}	
      } else {
	// unique symbols with all prefixes
	for (auto prefix: prefixes) {
	  check_symbol(units, std::string(prefix+unit.first));
	}
      }
    }
  }
  
}

void test_unit_definitions() {
  
  for (auto unit: puq::UnitSystem::Data->UnitList) {
    
    //std::cout << "hello " << unit.first << " " << std::bitset<8>((int)unit.second.utype) << std::endl;
    //if ((unit.second.utype & Utype::LIN)!=Utype::LIN) // check only linear units
    //  continue;
    if (unit.second.utype==puq::Utype::NUL) // ignore null units
      continue;
    if ((unit.second.utype & puq::Utype::BAS)==puq::Utype::BAS) // ignore base units
      continue;    

    puq::DimensionStruct dmap = puq::UnitSystem::Data->DimensionMap.at(unit.first);
#ifdef MAGNITUDE_ERRORS
    puq::MAGNITUDE_TYPE magnitude(dmap.magnitude, dmap.error);
#else
    puq::MAGNITUDE_TYPE magnitude(dmap.magnitude);
#endif
    puq::Dimensions dim1(magnitude, dmap.dimensions);
    std::string m1 = dim1.to_string();

    puq::UnitValue uv2(unit.second.definition);
    puq::Dimensions dim2 = uv2.baseunits.dimensions();
    dim2 = puq::Dimensions(uv2.magnitude*dim2.numerical, dim2.physical);
    std::string m2 = dim2.to_string();

#ifdef UNITS_LOGARITHMIC
    if (unit.second.utype == puq::Utype::LOG) {
      // For logarithmic units compare only the physical dimensionality
      m1 = dim1.to_string(puq::Dformat::PHYS);
      m2 = dim2.to_string(puq::Dformat::PHYS);
    }
#endif

    /*
    EXPECT_DOUBLE_EQ(unit.magnitude, dim2.numerical.value[0])
      << "Magnitude of unit '" << unit.first
      << "' does not match with its definition: "
      << puq::nostd::to_string(unit.magnitude) << " != "
      << puq::nostd::to_string(dim2.numerical);
    */
    EXPECT_EQ(m1, m2) << "Dimension of unit '" << unit.first
		      << "' do not match its definition: "
		      << m1 << " != " << m2;
  }  
  
}

void test_quantities() {
  for (auto quantity: puq::UnitSystem::Data->QuantityList) {
    
    // check if quantity symbol is in the quantity name list
    EXPECT_FALSE(puq::QuantityNames.find(quantity.first)==puq::QuantityNames.end())
      << "Quantity symbol is not in a name list: " << quantity.first;

    /*
    // check if quantity definition matches magnitude and dimensions
    puq::Dimensions dim1(quantity.second.magnitude, quantity.second.dimensions);
    std::string m1 = dim1.to_string();

    puq::UnitValue uv2(quantity.second.definition);
    puq::Dimensions dim2 = uv2.baseunits.dimensions();
    dim2 = puq::Dimensions(uv2.magnitude*dim2.numerical, dim2.physical);
    std::string m2 = dim2.to_string();

    EXPECT_EQ(m1, m2) << "Dimensions of quantity '" << quantity.first
		      << "' do not match its definition: "
		      << m1 << " != " << m2;
    */
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
  //test_unit_definitions();
  test_quantities();
  
}

#ifdef UNIT_SYSTEM_CGS

TEST(Lists, UnitDefinitionsESU) {

  puq::UnitSystem us(puq::SystemType::ESU);
  test_unit_symbols();
  //test_unit_definitions();
  
}

TEST(Lists, UnitDefinitionsGauss) {

  puq::UnitSystem us(puq::SystemType::GU);
  test_unit_symbols();
  //test_unit_definitions();
  
}

TEST(Lists, UnitDefinitionsEMU) {

  puq::UnitSystem us(puq::SystemType::EMU);
  test_unit_symbols();
  //test_unit_definitions();
    
}

#endif


#ifdef UNIT_SYSTEM_NUS

TEST(Lists, UnitDefinitionsAU) {

  puq::UnitSystem us(puq::SystemType::AU);
  test_unit_symbols();
  //test_unit_definitions();
  test_quantities();

}

#endif

#ifdef UNIT_SYSTEM_EUS

TEST(Lists, UnitDefinitionsIU) {

  puq::UnitSystem us(puq::SystemType::IU);
  test_unit_symbols();
  //test_unit_definitions();

}

TEST(Lists, UnitDefinitionsUS) {

  puq::UnitSystem us(puq::SystemType::US);
  test_unit_symbols();
  //test_unit_definitions();

}

#endif

TEST(List, DimensionMap) {

  auto it = puq::UnitSystem::Data->DimensionMap.find("<B>");
  EXPECT_TRUE(it!=puq::UnitSystem::Data->DimensionMap.end());
  
}

#ifdef MAGNITUDE_ERRORS
TEST(List, DimensionMapErrors) {

  auto it = puq::UnitSystem::Data->DimensionMap.find("[a_0]");
  EXPECT_TRUE(it!=puq::UnitSystem::Data->DimensionMap.end());
  EXPECT_FLOAT_EQ(it->second.magnitude, 5.2917721e-11);
  EXPECT_FLOAT_EQ(it->second.error, 8.2e-21);
  
}
#endif
