#include <gtest/gtest.h>

#include "../src/calc/calc.h"

TEST(Calculator, Initialization) {

  puq::Calculator calc;
  
  puq::CalculatorAtom atom = calc.solve("");        // empty string
  EXPECT_EQ(atom.value.to_string(), "1");

}

TEST(Calculator, Arithmetics) {

  puq::Calculator calc;
  
  puq::CalculatorAtom atom = calc.solve("12*cm + 3*m");  // addition
  EXPECT_EQ(atom.value.to_string(), "312*cm");

  atom = calc.solve("4*cm - 3*mm");              // subtration
  EXPECT_EQ(atom.value.to_string(), "3.7*cm");

  atom = calc.solve("2*cm * 3*m");               // multiplication
  EXPECT_EQ(atom.value.to_string(), "6*cm*m");
  EXPECT_EQ(atom.value.rebase_prefixes().to_string(), "600*cm2");
  
  atom = calc.solve("6*cm / 2*g");               // division
  EXPECT_EQ(atom.value.to_string(), "3*cm*g-1");

  atom = calc.solve("2*g * ( 6*m2/s2 - 3*cm2 / 1.5*s2 )");  // parentheses
  EXPECT_EQ(atom.value.to_string(), "11.9996*g*m2*s-2");
  
}
