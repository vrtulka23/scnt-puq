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

#endif // MAGNITUDE_ARRAYS
