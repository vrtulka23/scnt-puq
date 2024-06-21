#include <gtest/gtest.h>

#include "../src/puq.h"

#ifdef MAGNITUDE_ERRORS

TEST(Magnitude, Initialization) {
  
  Magnitude m;
  EXPECT_EQ(m.to_string(), "1");

  m = Magnitude(0);
  EXPECT_EQ(m.to_string(), "0");

  m = Magnitude(2.34);
  EXPECT_EQ(m.to_string(), "2.34");

  m = Magnitude(2.34);
  EXPECT_EQ(m.to_string(), "2.34");

  m = Magnitude(20, 10);
  EXPECT_EQ(m.to_string(), "2.0(10)e+01");

  m = Magnitude(2, 1);
  EXPECT_EQ(m.to_string(), "2.0(10)");

  m = Magnitude(2.34, 0.023);
  EXPECT_EQ(m.to_string(), "2.340(23)");

  m = Magnitude(2.34e7, 2.3e4);
  EXPECT_EQ(m.to_string(), "2.3400(23)e+07");

  m = Magnitude(2.34e-7, 2.3e-9);
  EXPECT_EQ(m.to_string(), "2.340(23)e-07");
  
}

TEST(Magnitude, ErrorConversion) {
  
  EXPECT_EQ(Magnitude::abs_to_rel(30, 0.3), 1); // 0.3/30*100 = 1%

  EXPECT_EQ(Magnitude::rel_to_abs(30, 20), 6);  // 30*20% = 30/5 = 6
 
}

TEST(Magnitude, ArithmeticsMultiply) {

  Magnitude m1, m2, m3;

  m1 = Magnitude(4.0, 0.05);
  m2 = Magnitude(7, 0.1);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.800(75)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.800(75)e+01");

  m1 = Magnitude(4.0, 0.05);
  m2 = Magnitude(5, 0);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.000(25)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.000(25)e+01");

  m1 = Magnitude(5, 0);
  m2 = Magnitude(4.0, 0.05);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.000(25)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.000(25)e+01");
  
}

TEST(Magnitude, ArithmeticsDivide) {

  Magnitude m1, m2, m3;

  m1 = Magnitude(12.0, 0.2);
  m2 = Magnitude(4, 0.1);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "3.00(13)");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "3.00(13)");

  m1 = Magnitude(12.0, 0.2);
  m2 = Magnitude(6, 0);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "2.000(33)");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "2.000(33)");

  m1 = Magnitude(6, 0);
  m2 = Magnitude(12.0, 0.2);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "5.000(85)e-01");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "5.000(85)e-01");
  
}

#endif // MAGNITUDE_ERRORS
