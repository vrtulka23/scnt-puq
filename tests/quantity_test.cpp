#include <gtest/gtest.h>

#include "../src/puq.h"

TEST(Quantity, Initialization) {

  Quantity q;                        // default initialization
  EXPECT_EQ(q.to_string(), "1");
  
  q = Quantity(1.23);                // magnitude
  EXPECT_EQ(q.to_string(), "1.23");

  q = Quantity(1.2,{{"k","m",3}});   // magnitude and dimensions
  EXPECT_EQ(q.to_string(), "1.2*km3");
  
  UnitValue uv(1.2,{{"k","m",3}});
  q = Quantity(uv);                  // UnitValue
  EXPECT_EQ(q.to_string(), "1.2*km3");

  q = Quantity(1.23,"g/cm3");        // magnitude and a unit expression
  EXPECT_EQ(q.to_string(), "1.23*g*cm-3");

  q = Quantity(1.23,"2*km3");        // magnitude and a unit expression with a number
  EXPECT_EQ(q.to_string(), "2.46*km3");
  
}

TEST(Quantity, ArithmeticsAdd) {

  Quantity q1,q2,q3;

  q1 = Quantity(6,"cm");
  q2 = Quantity(3,"cm");
  q3 = q1 + q2;
  EXPECT_EQ(q3.to_string(), "9*cm");
  q1 += q2;
  EXPECT_EQ(q1.to_string(), "9*cm");

  q3 = Quantity(3,"cm2");
  EXPECT_THROW(q1+q3,  std::invalid_argument);
  
}

TEST(Quantity, ArithmeticsSubtract) {

  Quantity q1,q2,q3;

  q1 = Quantity(6,"cm");
  q2 = Quantity(3,"cm");
  q3 = q1 - q2;
  EXPECT_EQ(q3.to_string(), "3*cm");
  q1 -= q2;
  EXPECT_EQ(q1.to_string(), "3*cm");

  q3 = Quantity(3,"cm2");
  EXPECT_THROW(q1-q3,  std::invalid_argument);
  
}

TEST(Quantity, ArithmeticsMultiply) {

  Quantity q1,q2,q3;

  q1 = Quantity(6,"cm3");
  q2 = Quantity(3,"g2");
  q3 = q1 * q2;
  EXPECT_EQ(q3.to_string(), "18*cm3*g2");
  q1 *= q2;
  EXPECT_EQ(q1.to_string(), "18*cm3*g2");
}

TEST(Quantity, ArithmeticsDivide) {

  Quantity q1,q2,q3;
  
  q1 = Quantity(6,"cm3");
  q2 = Quantity(3,"g2");
  q3 = q1 / q2;
  EXPECT_EQ(q3.to_string(), "2*cm3*g-2");
  q1 /= q2;
  EXPECT_EQ(q1.to_string(), "2*cm3*g-2");  

}

#ifdef MAGNITUDE_ERRORS

TEST(Quantity, InitializationErrors) {

  Quantity q(1.23,0.01);             // magnitudes with errors
  EXPECT_EQ(q.to_string(), "1.230(10)");

  q = Quantity(1.23,0.01,"km3");     // magnitude, errors and dimensions
  EXPECT_EQ(q.to_string(), "1.230(10)*km3");

  q = Quantity(1.23,0.01,"2*km3");   // magnitude, errors and dimensions with a number
  EXPECT_EQ(q.to_string(), "2.460(20)*km3");

}

#endif
