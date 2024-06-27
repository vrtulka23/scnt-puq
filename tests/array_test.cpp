#include <gtest/gtest.h>

#include "../src/puq.h"

#ifdef MAGNITUDE_ARRAYS

TEST(Array, Initialization) {

  Array a(3);
  EXPECT_EQ(a.to_string(), "3");

  a = Array({3,4});
  EXPECT_EQ(a.to_string(), "[3, 4]");

  a = Array({3,4,5});
  EXPECT_EQ(a.to_string(), "[3, 4, ...]");

  a = Array({3e12,4.34,5.23e2});
  EXPECT_EQ(a.to_string(), "[3e+12, 4.34, ...]");
  
}

TEST(Array, Arithmetics) {

  Array a, b, c;
  
  a = Array({3.1,4.2,5.3});
  b = Array({0.1,1.2,2.3});
  c = a + b;
  EXPECT_EQ(c.to_string(), "[3.2, 5.4, ...]");
  a += b;
  EXPECT_EQ(a.to_string(), "[3.2, 5.4, ...]");  

  a = Array({3.1,4.2,5.3});
  b = Array({0.1,1.2,2.3});
  c = a - b;
  EXPECT_EQ(c.to_string(), "[3, 3, ...]");
  a -= b;
  EXPECT_EQ(a.to_string(), "[3, 3, ...]");  

  a = Array({3.1,4.2,5.3});
  b = Array({0.1,1.2,2.3});
  c = a * b;
  EXPECT_EQ(c.to_string(), "[0.31, 5.04, ...]");
  a *= b;
  EXPECT_EQ(a.to_string(), "[0.31, 5.04, ...]");  

  a = Array({3.1,4.2,5.3});
  b = Array({0.1,1.2,2.3});
  c = a / b;
  EXPECT_EQ(c.to_string(), "[31, 3.5, ...]");
  a /= b;
  EXPECT_EQ(a.to_string(), "[31, 3.5, ...]");  
  
}

TEST(Array, Comparison) {

  Array a, b;

  a = Array({3.1,4.2,5.3});
  b = Array({0.1,1.2,2.3});

  EXPECT_EQ(a==a, true);
  EXPECT_EQ(a!=a, false);
  EXPECT_EQ(a==b, false);
  EXPECT_EQ(a!=b, true);

}

#endif // MAGNITUDE_ARRAYS
