#include <gtest/gtest.h>

#include "../src/puq.h"

TEST(Dimensions, Initialization) {

  Dimensions d;
  EXPECT_EQ(d.to_string(), "");

  d = Dimensions(2.34);
  EXPECT_EQ(d.to_string(), "2.34");
  
  d = Dimensions(2.34,{0,1,2,3,4,5,6,7});
  EXPECT_EQ(d.to_string(), "2.34*g*s2*K3*C4*cd5*mol6*rad7");
  
}

#ifdef MAGNITUDE_ERRORS

TEST(Dimensions, InitializationErrors) {

  Dimensions d(2.34,0.23);
  EXPECT_EQ(d.to_string(), "2.34(23)");

  d = Dimensions(2.34,0.23,{0,1,2,3,4,5,6,7});
  EXPECT_EQ(d.to_string(), "2.34(23)*g*s2*K3*C4*cd5*mol6*rad7");
  
}
  
#endif

#ifdef EXPONENT_FRACTIONS

TEST(Dimensions, InitializationFractions) {

  Dimensions d(2.34,{1,{1,-2},0,0,0,0,0,0});
  EXPECT_EQ(d.to_string(), "2.34*m*g-1:2");

  d = Dimensions(2.34,BaseDimensions({Exponent(3,2),{1,-2},0,0,0,0,0,0}));
  EXPECT_EQ(d.to_string(), "2.34*m3:2*g-1:2");
  
}

#endif
