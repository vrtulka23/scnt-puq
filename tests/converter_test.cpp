#include <gtest/gtest.h>

#include "../src/value/unit_value.h"
#include "../src/converter.h"

TEST(Converter, Initialization) {

  BaseUnits bu1("km/s");
  BaseUnits bu2("m/s");
  Converter con(bu1, bu2);   // using BaseUnits

  con = Converter("ms","s"); // using strings
  
}

TEST(Converter, LinearConv) {
  
  Converter con;
  
  con = Converter("erg", "J");       // different units
  EXPECT_EQ(con.convert(1,1).to_string(), "1e-07");

  con = Converter("kg*m2/s2", "J");  // different units with magnitudes
  EXPECT_EQ(con.convert(6,2).to_string(), "3");

  con = Converter("mg", "g");        // different prefixes
  EXPECT_EQ(con.convert(1,1).to_string(), "0.001");

  con = Converter("1/s", "kHz");     // different prefixes
  EXPECT_EQ(con.convert(6,2).to_string(), "0.003");
  
}

TEST(Converter, TemperatureConv) {

  Converter con;
  
  con = Converter("K", "Cel");
  EXPECT_EQ(con.convert(23,1).to_string(), "-250.15");
  con = Converter("K", "degF");
  EXPECT_EQ(con.convert(23,1).to_string(), "-418.27");
  con = Converter("K", "degR");
  EXPECT_EQ(con.convert(23,1).to_string(), "41.4");

  con = Converter("Cel", "K");
  EXPECT_EQ(con.convert(23,1).to_string(), "296.15");
  con = Converter("Cel", "degF");
  EXPECT_EQ(con.convert(23,1).to_string(), "73.4");
  con = Converter("Cel", "degR");
  EXPECT_EQ(con.convert(23,1).to_string(), "533.07");

  con = Converter("degF", "K");
  EXPECT_EQ(con.convert(23,1).to_string(), "268.15");
  con = Converter("degF", "Cel");
  EXPECT_EQ(con.convert(23,1).to_string(), "-5");
  con = Converter("degF", "degR");
  EXPECT_EQ(con.convert(23,1).to_string(), "482.67");
  
  con = Converter("degR", "K");
  EXPECT_EQ(con.convert(23,1).to_string(), "12.7778");
  con = Converter("degR", "Cel");
  EXPECT_EQ(con.convert(23,1).to_string(), "-260.372");
  con = Converter("degR", "degF");
  EXPECT_EQ(con.convert(23,1).to_string(), "-436.67");

  con = Converter("Cel", "kK");
  EXPECT_EQ(con.convert(2300,1).to_string(), "2.57315");
  
}
