#include <gtest/gtest.h>

#include "../src/value/value.h"

TEST(BaseUnits, Initialization) {

  // Appending BaseUnit-s
  puq::BaseUnits bus;
  puq::BaseUnit bu1 = {"k","g",2};
  bus.append(bu1);
  puq::BaseUnit bu2("m","s",3);
  bus.append(bu2);
  bus.append("c","m",1);
  EXPECT_EQ(bus.size(), 3);
  EXPECT_EQ(bus.to_string(), "kg2*ms3*cm");

  // Using a string expression
  bus = puq::BaseUnits("kg*m2/s2");
  EXPECT_EQ(bus.to_string(), "kg*m2*s-2");
  
}

#ifdef EXPONENT_FRACTIONS

TEST(BaseUnits, InitializationFractions) {
  
  puq::BaseUnits bus;
  puq::BaseUnit bu1 = {"k","g",2,1};
  bus.append(bu1);
  puq::BaseUnit bu2("m","s",3,2);
  bus.append(bu2);
  bus.append("c","m",1,1);
  EXPECT_EQ(bus.size(), 3);
  EXPECT_EQ(bus.to_string(), "kg2*ms3:2*cm");

}

#endif

TEST(BaseUnits, RemoveZeroExponents) {
  
  puq::BaseUnits bus;
  bus.append("m","s",2);    // adding normal units
  bus.append("c","m",1);
  EXPECT_EQ(bus.size(), 2);
  EXPECT_EQ(bus.to_string(), "ms2*cm");
  
  bus.append("c","m",-1); // adding inverse unit
  EXPECT_EQ(bus.size(), 1);
  EXPECT_EQ(bus.to_string(), "ms2");

  bus.append("k","g",0);
  EXPECT_EQ(bus.size(), 1); // adding unit with a zero exponent
  EXPECT_EQ(bus.to_string(), "ms2");
 
}

#ifdef EXPONENT_FRACTIONS

TEST(BaseUnits, RemoveZeroExponentsFractions) {
  
  puq::BaseUnits bus;
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

#endif 

TEST(BaseUnits, Dimensions) {

  puq::BaseUnits bus;
  bus.append("k","m",1);
  bus.append("n","s",2);
  bus.append("m","g",3);
  EXPECT_EQ(bus.to_string(), "km*ns2*mg3");
  puq::Dimensions dim = bus.dimensions();
  EXPECT_EQ(dim.to_string(), "1e-24*m*g3*s2");

  puq::BaseUnits bus2;
  bus2.append("","au",2);;
  EXPECT_EQ(bus2.to_string(), "au2");
  dim = bus2.dimensions();
  EXPECT_EQ(dim.to_string(), "2.23795e+22*m2");
  
}
