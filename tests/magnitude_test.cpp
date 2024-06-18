#include <gtest/gtest.h>

#include "../src/puq.h"

#ifdef MAGNITUDE_ERRORS

TEST(Magnitude, Initialization) {

  Magnitude m;
  EXPECT_EQ(m.to_string(), "");

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

#endif // MAGNITUDE_ERRORS
