#include <gtest/gtest.h>

#include "../src/value/unit_value.h"

TEST(UnitValue, Initialization) {

  UnitValue value;
  
  value = {3.34e3,{{"k","m",-1}}};           // list initialization
  EXPECT_EQ(value.to_string(), "3340*km-1");

  value = UnitValue(3.34e3,"km-1");          // assigning UnitValue
  EXPECT_EQ(value.to_string(), "3340*km-1");
		    
  BaseUnits bu("km-1/s2");
  value = UnitValue(3, bu);                  // from BaseUnits
  EXPECT_EQ(value.to_string(), "3*km-1*s-2");

  value = UnitValue("3*km/s");               // from a string
  EXPECT_EQ(value.to_string(), "3*km*s-1");
  
}

#ifdef EXPONENT_FRACTIONS

TEST(UnitValue, InitializationFractions) {
  
  UnitValue value1 = {3.34e3,{{"k","m",-1,2}}};
  EXPECT_EQ(value1.to_string(), "3340*km-1:2");

  UnitValue value2(3.34e3,"km-1:2");
  EXPECT_EQ(value2.to_string(), "3340*km-1:2");

  BaseUnits bu("km-1:2/s2");
  UnitValue value3(3, bu);
  EXPECT_EQ(value3.to_string(), "3*km-1:2*s-2");
  
}

#endif

TEST(UnitValue, UnitConversion) {

  UnitValue v1, v2, v3;

  v1 = UnitValue("2*cm2");
  v2 = UnitValue("3*m2");
  v3 = v1.convert(v2);          // conversion using UnitValue
  EXPECT_EQ(v3.to_string(), "0.0002*m2");

  BaseUnits bu("m2");
  v1 = UnitValue("2*cm2");
  v2 = v1.convert(bu);          // conversion using BaseUnits
  EXPECT_EQ(v2.to_string(), "0.0002*m2");  
  
}
