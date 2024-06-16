#include <gtest/gtest.h>
#include "../src/puq.h"

TEST(UnitSolver, Initialization) {

  UnitSolver solver;  

}

TEST(UnitSolver, Querying) {

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

  atom = solver.solve("3.2e4*kg*m*m/s/s");
  EXPECT_EQ(atom.value.to_string(), "32000*kg*m2*s-2");

  atom = solver.solve("m1:2*m-3:5");
  EXPECT_EQ(atom.value.to_string(), "1*m-1:10");

  atom = solver.solve("kg/(m*s)");
  EXPECT_EQ(atom.value.to_string(), "1*kg*m-1*s-1");

  atom = solver.solve("kg/(m*s)2*C");
  EXPECT_EQ(atom.value.to_string(), "1*kg*m-2*s-2*C");

  atom = solver.solve("kg/(m*s)-1:2*C");
  EXPECT_EQ(atom.value.to_string(), "1*kg*m1:2*s1:2*C");
  
  // TODO: uncertainities, solving something like this:
  // 2.233(23)e4*kg*m2/s2
  
}
