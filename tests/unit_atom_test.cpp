#include <gtest/gtest.h>
#include "../src/puq.h"

TEST(UnitAtom, Arithmetics) {

  UnitAtom a1({6.0,{{"a","b",1}}});
  UnitAtom a2({3.0,{{"c","d",3}}});
  
  a1.math_multiply(&a2); // 6 * 3 = 18
  EXPECT_EQ(a1.value.magnitude, 18);

  a1.math_divide(&a2);   // 18 / 3 = 6
  EXPECT_EQ(a1.value.magnitude, 6);
}

#ifdef FRACTIONAL_EXPONENTS

TEST(UnitAtom, ArithmeticsFractions) {

  UnitAtom a1({6.0,{{"c","m",1,2}}});
  UnitAtom a2({3.0,{{"k","g",3,4}}});
  
  a1.math_multiply(&a2); // Atom multiplication: 6 * 3 = 18
  EXPECT_EQ(a1.value.magnitude, 18); 
  EXPECT_EQ(a1.value.to_string(), "18*cm1:2*kg3:4");

  a1.math_divide(&a2);   // Atom division: 18 / 3 = 6
  EXPECT_EQ(a1.value.magnitude, 6);          
  EXPECT_EQ(a1.value.to_string(), "6*cm1:2");
}

#endif

TEST(UnitAtom, UnitValueFromString) {

  UnitValue v = UnitAtom::from_string("m");
  EXPECT_EQ(v.to_string(), "m");
  
}
