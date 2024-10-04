#include <gtest/gtest.h>

#include "../src/magnitude.h"

#ifdef MAGNITUDE_ERRORS

TEST(Magnitude, Initialization) {
  
  puq::Magnitude m;
  EXPECT_EQ(m.to_string(), "1");

  m = puq::Magnitude(0);
  EXPECT_EQ(m.to_string(), "0");

  m = puq::Magnitude(2.34);
  EXPECT_EQ(m.to_string(), "2.34");

  m = puq::Magnitude(2.34);
  EXPECT_EQ(m.to_string(), "2.34");

  m = puq::Magnitude(20, 10);
  EXPECT_EQ(m.to_string(), "2.0(10)e+01");

  m = puq::Magnitude(2, 1);
  EXPECT_EQ(m.to_string(), "2.0(10)");

  m = puq::Magnitude(2.34, 0.023);
  EXPECT_EQ(m.to_string(), "2.340(23)");

  m = puq::Magnitude(2.34e7, 2.3e4);
  EXPECT_EQ(m.to_string(), "2.3400(23)e+07");

  m = puq::Magnitude(2.34e-7, 2.3e-9);
  EXPECT_EQ(m.to_string(), "2.340(23)e-07");

  m = puq::Magnitude(3.234, 0.002);    
  std::stringstream ss;
  ss << m;                      // cast magnitude as a string into a stream
  EXPECT_EQ(ss.str(), "3.2340(20)");
  
}

TEST(Magnitude, ErrorConversion) {
  
  EXPECT_EQ(puq::Magnitude::abs_to_rel(30, 0.3), 1); // 0.3/30*100 = 1%

  EXPECT_EQ(puq::Magnitude::rel_to_abs(30, 20), 6);  // 30*20% = 30/5 = 6
 
}

TEST(Magnitude, Size) {
  
  puq::Magnitude m(puq::Array({2,3,4,5}));
  EXPECT_EQ(m.size(), 4);
  
}

#ifdef MAGNITUDE_ARRAYS

TEST(Magnitude, ErrorConversionArrays) {

  puq::Array a = puq::Magnitude::abs_to_rel(puq::Array({30,20}), puq::Array({0.3,0.4}));
  EXPECT_EQ(a.to_string(), "{1, 2}");

  a = puq::Magnitude::rel_to_abs(puq::Array({30,20}), puq::Array({20,10}));
  EXPECT_EQ(a.to_string(), "{6, 2}");
 
}

#endif

TEST(Magnitude, ArithmeticsAdd) {

  puq::Magnitude m1, m2, m3;

  m1 = puq::Magnitude(4, 0.01);
  m2 = puq::Magnitude(1, 0.005);
  m3 = m1 + m2;
  EXPECT_EQ(m3.to_string(), "5.000(15)");
  m1 += m2;
  EXPECT_EQ(m1.to_string(), "5.000(15)");

  m1 = puq::Magnitude(4, 0.01);
  m2 = puq::Magnitude(3);
  m3 = m1 + m2;
  EXPECT_EQ(m3.to_string(), "7.000(10)");
  m1 += m2;
  EXPECT_EQ(m1.to_string(), "7.000(10)");
  
}

TEST(Magnitude, ArithmeticsSubtract) {

  puq::Magnitude m1, m2, m3;

  m1 = puq::Magnitude(4, 0.01);
  EXPECT_EQ((-m1).to_string(), "-4.000(10)");
  
  m1 = puq::Magnitude(4, 0.01);
  m2 = puq::Magnitude(1, 0.005);
  m3 = m1 - m2;
  EXPECT_EQ(m3.to_string(), "3.000(15)");
  m1 -= m2;
  EXPECT_EQ(m1.to_string(), "3.000(15)");

  m1 = puq::Magnitude(4, 0.01);
  m2 = puq::Magnitude(3);
  m3 = m1 - m2;
  EXPECT_EQ(m3.to_string(), "1.000(10)");
  m1 -= m2;
  EXPECT_EQ(m1.to_string(), "1.000(10)");
  
}

TEST(Magnitude, ArithmeticsMultiply) {

  puq::Magnitude m1, m2, m3;

  m1 = puq::Magnitude(4.0, 0.05);
  m2 = puq::Magnitude(7, 0.1);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.800(75)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.800(75)e+01");

  m1 = puq::Magnitude(4.0, 0.05);
  m2 = puq::Magnitude(5, 0);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.000(25)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.000(25)e+01");

  m1 = puq::Magnitude(5, 0);
  m2 = puq::Magnitude(4.0, 0.05);
  m3 = m1 * m2;
  EXPECT_EQ(m3.to_string(), "2.000(25)e+01");
  m1 *= m2;
  EXPECT_EQ(m1.to_string(), "2.000(25)e+01");
  
}

TEST(Magnitude, ArithmeticsDivide) {

  puq::Magnitude m1, m2, m3;

  m1 = puq::Magnitude(12.0, 0.2);
  m2 = puq::Magnitude(4, 0.1);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "3.00(13)");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "3.00(13)");

  m1 = puq::Magnitude(12.0, 0.2);
  m2 = puq::Magnitude(6, 0);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "2.000(33)");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "2.000(33)");

  m1 = puq::Magnitude(6, 0);
  m2 = puq::Magnitude(12.0, 0.2);
  m3 = m1 / m2;
  EXPECT_EQ(m3.to_string(), "5.000(85)e-01");
  m1 /= m2;
  EXPECT_EQ(m1.to_string(), "5.000(85)e-01");
  
}

TEST(Magnitude, Comparison) {

  puq::Magnitude a, b;

  a = puq::Magnitude(1.234, 0.001);
  b = puq::Magnitude(2.345, 0.002);

  EXPECT_EQ(a==a, true);
  EXPECT_EQ(a!=a, false);
  EXPECT_EQ(a==b, false);
  EXPECT_EQ(a!=b, true);

}

#ifdef MAGNITUDE_ARRAYS

TEST(Magnitude, Arrays) {

  puq::Magnitude m1, m2, m3;

  m1 = puq::Magnitude(puq::Array({12.1, 22.2}), puq::Array({0.1, 0.2}));
  EXPECT_EQ(m1.to_string(), "{1.210(10)e+01, 2.220(20)e+01}");

  m1 = puq::Magnitude(puq::Array({12.1, 22.2, 32.3}), puq::Array({0.1, 0.2, 0.3}));
  EXPECT_EQ(m1.to_string(), "{1.210(10)e+01, 2.220(20)e+01, ...}");

}

#endif

#endif // MAGNITUDE_ERRORS
