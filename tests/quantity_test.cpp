#include <gtest/gtest.h>

#include "../src/quantity.h"
#include "../src/converter.h"

TEST(Quantity, Initialization) {

  puq::Quantity q;                        // default initialization
  EXPECT_EQ(q.to_string(), "1");
  
  q = puq::Quantity(1.23);                // magnitude
  EXPECT_EQ(q.to_string(), "1.23");

  q = puq::Quantity(1.2,{{"k","m",3}});   // magnitude and dimensions
  EXPECT_EQ(q.to_string(), "1.2*km3");
  
  puq::UnitValue uv(1.2,{{"k","m",3}});
  q = puq::Quantity(uv);                  // UnitValue
  EXPECT_EQ(q.to_string(), "1.2*km3");

  q = puq::Quantity("23.34*g/cm3");       // from a unit expression
  EXPECT_EQ(q.to_string(), "23.34*g*cm-3");
  
  q = puq::Quantity(1.23,"g/cm3");        // magnitude and a unit expression
  EXPECT_EQ(q.to_string(), "1.23*g*cm-3");

  q = puq::Quantity(1.23,"2*km3");        // magnitude and a unit expression with a number
  EXPECT_EQ(q.to_string(), "2.46*km3");

#ifdef PREPROCESS_SYMBOLS
  q = puq::Quantity("6.23537×10−12 C4⋅m4⋅J−3");
  EXPECT_EQ(q.to_string(), "6.23537e-12*C4*m4*J-3");

  q = puq::Quantity("6.23537×1012 C4⋅m4⋅J−3");
  EXPECT_EQ(q.to_string(), "6.23537e+12*C4*m4*J-3");
#endif
  
}
  
#ifdef MAGNITUDE_ERRORS
TEST(Quantity, InitializationErrors) {

  puq::Quantity q(1.23,0.01);             // magnitudes with errors
  EXPECT_EQ(q.to_string(), "1.230(10)");

  q = puq::Quantity(1.23,0.01,"km3");     // magnitude, errors and dimensions
  EXPECT_EQ(q.to_string(), "1.230(10)*km3");

  q = puq::Quantity(1.23,0.01,"2*km3");   // magnitude, errors and dimensions with a number
  EXPECT_EQ(q.to_string(), "2.460(20)*km3");

  q = puq::Quantity("3.40(10)*km3");      // unit expression
  EXPECT_EQ(q.to_string(), "3.40(10)*km3");

#ifdef PREPROCESS_SYMBOLS
  q = puq::Quantity("6.23537(39)×10−12 C4⋅m4⋅J−3");
  EXPECT_EQ(q.to_string(), "6.23537(39)e-12*C4*m4*J-3");

  q = puq::Quantity("8.8541878188(14)×10−12 F⋅m−1");
  EXPECT_EQ(q.to_string(), "8.8541878188(14)e-12*F*m-1");
#endif
  
}
#endif

#ifdef MAGNITUDE_ARRAYS
TEST(Quantity, InitializationArrays) {

  puq::Quantity q("{2,3.4,5e6}*km/s");                 // unit expression
  EXPECT_EQ(q.to_string(), "{2, 3.4, ...}*km*s-1");

  q = puq::Quantity(puq::Array({2,3.4,5e6}),"km2");    // magnitudes and units
  EXPECT_EQ(q.to_string(), "{2, 3.4, ...}*km2");

#ifdef PREPROCESS_SYMBOLS
  q = puq::Quantity("{2,3.4,5×106} C4⋅m4⋅J−3");
  EXPECT_EQ(q.to_string(), "{2, 3.4, ...}*C4*m4*J-3");
#endif
  
}
#endif

TEST(Quantity, UnitConversion) {

  puq::Quantity q;

  q = puq::Quantity(6,"cm").convert("km");
  EXPECT_EQ(q.to_string(), "6e-05*km");
  
  q = puq::Quantity(1,"au").convert("km");
  EXPECT_EQ(q.to_string(), "1.49598e+08*km");

}

TEST(Quantity, ArithmeticsAdd) {

  puq::Quantity q1,q2,q3;

  q1 = puq::Quantity(6,"cm");   // same units
  q2 = puq::Quantity(3,"cm");
  q3 = q1 + q2;
  EXPECT_EQ(q3.to_string(), "9*cm");
  q1 += q2;
  EXPECT_EQ(q1.to_string(), "9*cm");

  q3 = puq::Quantity(3,"cm2");  // different units
  EXPECT_THROW(q1+q3,  puq::ConvDimExcept);

  q1 = +puq::Quantity(6,"cm");  // unary addition
  EXPECT_EQ(q1.to_string(), "6*cm");
  
}

TEST(Quantity, ArithmeticsSubtract) {

  puq::Quantity q1,q2,q3;

  q1 = puq::Quantity(6,"cm");
  q2 = puq::Quantity(3,"cm");
  q3 = q1 - q2;
  EXPECT_EQ(q3.to_string(), "3*cm");
  q1 -= q2;
  EXPECT_EQ(q1.to_string(), "3*cm");

  q3 = puq::Quantity(3,"cm2");
  EXPECT_THROW(q1-q3,  puq::ConvDimExcept);

  q1 = -puq::Quantity(6,"cm");  // unary subtraction
  EXPECT_EQ(q1.to_string(), "-6*cm");
  
}

TEST(Quantity, ArithmeticsMultiply) {

  puq::Quantity q1,q2,q3;

  q1 = puq::Quantity(6,"cm3");
  q2 = puq::Quantity(3,"g2");
  q3 = q1 * q2;
  EXPECT_EQ(q3.to_string(), "18*cm3*g2");
  q1 *= q2;
  EXPECT_EQ(q1.to_string(), "18*cm3*g2");
}

TEST(Quantity, ArithmeticsDivide) {

  puq::Quantity q1,q2,q3;
  
  q1 = puq::Quantity(6,"cm3");
  q2 = puq::Quantity(3,"g2");
  q3 = q1 / q2;
  EXPECT_EQ(q3.to_string(), "2*cm3*g-2");
  q1 /= q2;
  EXPECT_EQ(q1.to_string(), "2*cm3*g-2");  

}


