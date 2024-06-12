#include <gtest/gtest.h>
#include "../src/puq.h"

// Solver initialization
TEST(UnitSolver, Initialization) {

  UnitSolver solver;
  
  UnitAtom atom = solver.solve("3*(20/5)");
  EXPECT_EQ(atom.value.magnitude, 12);
  EXPECT_EQ(atom.value.baseunits.size(), 0);

  atom = solver.solve("s");
  EXPECT_EQ(atom.value.to_string(), "1*s");
  EXPECT_EQ(atom.value.magnitude, 1);
  EXPECT_EQ(atom.value.baseunits[0].to_string(), "s");
  EXPECT_EQ(atom.value.baseunits[0].prefix, "");
  EXPECT_EQ(atom.value.baseunits[0].unit, "s");
  EXPECT_EQ(atom.value.baseunits[0].numerator, 1);
  EXPECT_EQ(atom.value.baseunits[0].denominator, 1);

  atom = solver.solve("mC");
  EXPECT_EQ(atom.value.to_string(), "1*mC");
  EXPECT_EQ(atom.value.magnitude, 1);
  EXPECT_EQ(atom.value.baseunits[0].to_string(), "mC");
  EXPECT_EQ(atom.value.baseunits[0].prefix, "m");
  EXPECT_EQ(atom.value.baseunits[0].unit, "C");
  EXPECT_EQ(atom.value.baseunits[0].numerator, 1);
  EXPECT_EQ(atom.value.baseunits[0].denominator, 1);

  atom = solver.solve("kg2");
  EXPECT_EQ(atom.value.to_string(), "1*kg2");
  EXPECT_EQ(atom.value.magnitude, 1);
  EXPECT_EQ(atom.value.baseunits[0].to_string(), "kg2");
  EXPECT_EQ(atom.value.baseunits[0].prefix, "k");
  EXPECT_EQ(atom.value.baseunits[0].unit, "g");
  EXPECT_EQ(atom.value.baseunits[0].numerator, 2);
  EXPECT_EQ(atom.value.baseunits[0].denominator, 1);
  
  atom = solver.solve("km-2:3");
  EXPECT_EQ(atom.value.to_string(), "1*km-2:3");
  EXPECT_EQ(atom.value.magnitude, 1);
  EXPECT_EQ(atom.value.baseunits[0].to_string(), "km-2:3");
  EXPECT_EQ(atom.value.baseunits[0].prefix, "k");
  EXPECT_EQ(atom.value.baseunits[0].unit, "m");
  EXPECT_EQ(atom.value.baseunits[0].numerator, -2);
  EXPECT_EQ(atom.value.baseunits[0].denominator, 3);

  atom = solver.solve("2.4*km/s");
  EXPECT_EQ(atom.value.to_string(), "2.4*km*s-1");

}
