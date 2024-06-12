#include <gtest/gtest.h>
#include "../src/puq.h"

// Test atom arithmetics
TEST(UnitSolver, AtomArithmetics) {

  UnitAtom a1({6.0,{{"a","b",1,2}}});
  UnitAtom a2({3.0,{{"c","d",3,4}}});
  
  a1.math_multiply(&a2); // 6 * 3 = 18
  EXPECT_EQ(a1.value.magnitude, 18);

  a1.math_divide(&a2);   // 18 / 3 = 6
  EXPECT_EQ(a1.value.magnitude, 6);
}

// Test unit value from string
TEST(UnitSolver, UnitValueFromString) {

  UnitValue v = UnitAtom::from_string("m");
  EXPECT_EQ(v.magnitude, 1);
  
}
