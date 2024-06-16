#include <gtest/gtest.h>
#include "../src/puq.h"

TEST(BaseUnits, Initialization) {
  
  BaseUnits bus;
  BaseUnit bu1 = {"k","g",2,1};
  bus.append(bu1);
  BaseUnit bu2("m","s",3,2);
  bus.append(bu2);
  bus.append("c","m",1,1);
  EXPECT_EQ(bus.size(), 3);
  EXPECT_EQ(bus.to_string(), "kg2*ms3:2*cm");
  
}

TEST(BaseUnits, RemoveZeroExponents) {
  
  BaseUnits bus;
  bus.append("m","s",2);    // adding normal units
  bus.append("c","m",1,2);
  EXPECT_EQ(bus.size(), 2);
  EXPECT_EQ(bus.to_string(), "ms2*cm1:2");
  
  bus.append("c","m",-1,2); // adding inverse unit
  EXPECT_EQ(bus.size(), 1);
  EXPECT_EQ(bus.to_string(), "ms2");

  bus.append("k","g",0,2);
  EXPECT_EQ(bus.size(), 1); // adding unit with a zero exponent
  EXPECT_EQ(bus.to_string(), "ms2");
  
}
