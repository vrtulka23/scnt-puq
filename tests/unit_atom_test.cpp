#include <gtest/gtest.h>

#include "../src/puq.h"

TEST(UnitAtom, FromString) {

  UnitValue value = UnitAtom::from_string("1");
  EXPECT_EQ(value.to_string(), "");             // unit

  value = UnitAtom::from_string("2");
  EXPECT_EQ(value.to_string(), "2");            // integer numbers

  value = UnitAtom::from_string("1.23");
  EXPECT_EQ(value.to_string(), "1.23");         // floating point numbers
  
  value = UnitAtom::from_string("1.23e6");
  EXPECT_EQ(value.to_string(), "1.23e+06");     // numbers in scientific notation
  
  value = UnitAtom::from_string("s");
  EXPECT_EQ(value.to_string(), "s");            // units without prefixes

  value = UnitAtom::from_string("mC");
  EXPECT_EQ(value.to_string(), "mC");           // allowed all prefixes

  value = UnitAtom::from_string("mrad");
  EXPECT_EQ(value.to_string(), "mrad");         // allowed specific prefix
  
  EXPECT_THROW(UnitAtom::from_string("kau"),  std::invalid_argument);  // prefixes are not allowed
  
  EXPECT_THROW(UnitAtom::from_string("crad"), std::invalid_argument);  // unit prefix is not allowed
  
  EXPECT_THROW(UnitAtom::from_string("Bm"),   std::invalid_argument);  // unknown unit prefix

  value = UnitAtom::from_string("kg2");
  EXPECT_EQ(value.to_string(), "kg2");          // units with exponents

  value = UnitAtom::from_string("cm-2");
  EXPECT_EQ(value.to_string(), "cm-2");         // negative exponents

}

#ifdef MAGNITUDE_ERRORS

TEST(UnitAtom, FromStringErrors) {
  // TODO: uncertainities, solving something like this:
  // 2(1)
  // 2.233(23)
  // 2.233(23)e4
}
  
#endif

#ifdef EXPONENT_FRACTIONS

TEST(UnitAtom, FromStringFractions) {

  UnitValue value = UnitAtom::from_string("kg4:2");
  EXPECT_EQ(value.to_string(), "kg2");          // reduced fractions

  value = UnitAtom::from_string("kg-2:3");
  EXPECT_EQ(value.to_string(), "kg-2:3");       // full fractions
  
}

#endif

TEST(UnitAtom, Arithmetics) {

  UnitAtom a1({6.0,{{"a","b",1}}});
  UnitAtom a2({3.0,{{"c","d",3}}});
  
  a1.math_multiply(&a2); // 6 * 3 = 18
  EXPECT_EQ(a1.value.to_string(), "18*ab*cd3");

  a1.math_divide(&a2);   // 18 / 3 = 6
  EXPECT_EQ(a1.value.to_string(), "6*ab");
  
}

#ifdef EXPONENT_FRACTIONS

TEST(UnitAtom, ArithmeticsFractions) {

  UnitAtom a1({6.0,{{"c","m",1,2}}});
  UnitAtom a2({3.0,{{"k","g",3,4}}});
  
  a1.math_multiply(&a2); // Atom multiplication: 6 * 3 = 18
  EXPECT_EQ(a1.value.to_string(), "18*cm1:2*kg3:4");

  a1.math_divide(&a2);   // Atom division: 18 / 3 = 6
  EXPECT_EQ(a1.value.to_string(), "6*cm1:2");
  
}

#endif
