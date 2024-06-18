#include <gtest/gtest.h>

#include "../src/puq.h"

TEST(UnitValue, Initialization) {
  
  UnitValue value1 = {3.34e3,{{"k","m",-1}}};
  EXPECT_EQ(value1.to_string(), "3340*km-1");

  UnitValue value2(3.34e3,{{"k","m",-1}});
  EXPECT_EQ(value2.to_string(), "3340*km-1");

  BaseUnits bu;
  bu.append("k","m",-1);
  bu.append("","s",-2);
  UnitValue value3(3, bu);
  EXPECT_EQ(value3.to_string(), "3*km-1*s-2");
  
}

#ifdef EXPONENT_FRACTIONS

TEST(UnitValue, InitializationFractions) {
  
  UnitValue value1 = {3.34e3,{{"k","m",-1,2}}};
  EXPECT_EQ(value1.to_string(), "3340*km-1:2");

  UnitValue value2(3.34e3,{{"k","m",-1,2}});
  EXPECT_EQ(value2.to_string(), "3340*km-1:2");

  BaseUnits bu;
  bu.append("k","m",-1,2);
  bu.append("","s",-2,1);
  UnitValue value3(3, bu);
  EXPECT_EQ(value3.to_string(), "3*km-1:2*s-2");
  
}

#endif
