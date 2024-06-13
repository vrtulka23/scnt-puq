#include <gtest/gtest.h>
#include "../src/puq.h"

// Solver initialization
TEST(UnitSolver, Initialization) {

  UnitSolver solver;
  
  UnitAtom atom = solver.solve("3*(20/5)");
  EXPECT_EQ(atom.value.to_string(), "12");

  atom = solver.solve("s");
  EXPECT_EQ(atom.value.to_string(), "1*s");

  atom = solver.solve("mC");
  EXPECT_EQ(atom.value.to_string(), "1*mC");

  atom = solver.solve("kg2");
  EXPECT_EQ(atom.value.to_string(), "1*kg2");
  
  atom = solver.solve("km-2:3");
  EXPECT_EQ(atom.value.to_string(), "1*km-2:3");

  atom = solver.solve("2.4*km/s");
  EXPECT_EQ(atom.value.to_string(), "2.4*km*s-1");

}
