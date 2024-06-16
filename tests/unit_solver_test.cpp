#include <gtest/gtest.h>
#include "../src/puq.h"

TEST(UnitSolver, Initialization) {

  UnitSolver solver;  

}

TEST(UnitSolver, Solve) {

  UnitSolver solver;  
  UnitAtom atom = solver.solve("3*(2.0e1/5.0)");     // only numbers
  EXPECT_EQ(atom.value.to_string(), "12");
  
  atom = solver.solve("s");
  EXPECT_EQ(atom.value.to_string(), "s");            // units without prefixes

  atom = solver.solve("mC");
  EXPECT_EQ(atom.value.to_string(), "mC");           // units with prefixes

  atom = solver.solve("kg2");
  EXPECT_EQ(atom.value.to_string(), "kg2");          // units with exponents
  
  atom = solver.solve("2.4*km/s");
  EXPECT_EQ(atom.value.to_string(), "2.4*km*s-1");   // simple arithmetics

  atom = solver.solve("3.2e4*kg*m*m/s/s");           // exponent reduction
  EXPECT_EQ(atom.value.to_string(), "32000*kg*m2*s-2");

  atom = solver.solve("1.3453e22*m/s");              // scientific notation
  EXPECT_EQ(atom.value.to_string(), "1.3453e+22*m*s-1");
  
  atom = solver.solve("kg/(m*s)");                   // simple parentheses
  EXPECT_EQ(atom.value.to_string(), "kg*m-1*s-1");

  atom = solver.solve("kg/(m*s)2*C");                // parentheses with eponents
  EXPECT_EQ(atom.value.to_string(), "kg*m-2*s-2*C");

  // TODO: uncertainities, solving something like this:
  // 2.233(23)e4*kg*m2/s2
  
}

#ifdef FRACTIONAL_EXPONENTS

TEST(UnitSolver, SolveFractions) {

  UnitSolver solver;  
  UnitAtom atom = solver.solve("km-2:3"); // units with fractions
  EXPECT_EQ(atom.value.to_string(), "km-2:3");

  atom = solver.solve("m1:2*m-3:5");      // reduction of fractions
  EXPECT_EQ(atom.value.to_string(), "m-1:10");
  
  atom = solver.solve("kg/(m*s)-1:2*C");  // parentheses with fractions
  EXPECT_EQ(atom.value.to_string(), "kg*m1:2*s1:2*C");
  
}

#endif
