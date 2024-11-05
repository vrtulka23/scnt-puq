#include <gtest/gtest.h>

#include "../src/quantity.h"
#include "../src/value/value.h"

TEST(UnitFormat, ExponentFormat) {

  puq::UnitFormat oformat(puq::MathFormat::ASCII);
 
  puq::Exponent e = puq::Exponent(-2);
  EXPECT_EQ(e.to_string(oformat), "⁻²");    // integer exponents
  
#ifdef EXPONENT_FRACTIONS
  e = puq::Exponent(3,2);    
  EXPECT_EQ(e.to_string(oformat), "³ᐟ²");   // positive fractional exponents
  
  e = puq::Exponent(-3,2);    
  EXPECT_EQ(e.to_string(oformat), "⁻³ᐟ²");  // negative fractional exponents
#endif
  
}

TEST(UnitFormat, DimensionsFormat) {

  puq::UnitFormat oformat;
  puq::Dimensions d;
  
  oformat = puq::UnitFormat(10);            // increased output precision
  d = puq::Dimensions(2.340342349349823e3,{0,1,2,3,4,5,6,7});
  EXPECT_EQ(d.to_string(puq::Dformat::NUM, oformat), "2340.342349");

}

TEST(UnitFormat, BaseUnitsFormat) {

  puq::UnitFormat oformat(puq::MathFormat::ASCII);
  puq::BaseUnits bus;
  
  bus = puq::BaseUnits("kg*m2/s2");               // integer exponents
  EXPECT_EQ(bus.to_string(oformat), "kg⋅m²⋅s⁻²");

#ifdef EXPONENT_FRACTIONS
  bus = puq::BaseUnits("m*kg-2:3");               // fractional exponents
  EXPECT_EQ(bus.to_string(oformat), "m⋅kg⁻²ᐟ³");  
#endif
  
}


TEST(UnitFormat, MagnitudeFormat) {

  puq::Magnitude m;
  puq::UnitFormat oformat;

  oformat = puq::UnitFormat(puq::MathFormat::ASCII);
  m = puq::Magnitude(3.234019394939e12);          // without errors
  EXPECT_EQ(m.to_string(oformat), "3.23402×10¹²");

  oformat = puq::UnitFormat(10);
  m = puq::Magnitude(3.2340342349349823e3);       // increased precision
  EXPECT_EQ(m.to_string(oformat), "3234.034235");
  
#ifdef MAGNITUDE_ERRORS
  oformat = puq::UnitFormat(puq::MathFormat::ASCII);
  m = puq::Magnitude(3.234019394939e12, 2.34e8);  // with errors
  EXPECT_EQ(m.to_string(oformat), "3.23402(23)×10¹²");
#endif
  
}

TEST(UnitFormat, UnitValueFormat) {
  
  puq::UnitValue value;
  puq::UnitFormat oformat;
  
  oformat = puq::UnitFormat(puq::MathFormat::ASCII);
  value = puq::UnitValue("3*km-2*m/s2");                    // normal units
  EXPECT_EQ(value.to_string(oformat), "3⋅km⁻²⋅m⋅s⁻²");

  value = puq::UnitValue("3.234019394939e12*km-2");         // decimal orders
  EXPECT_EQ(value.to_string(oformat), "3.23402×10¹²⋅km⁻²");
  
  oformat = puq::UnitFormat(10);
  value = puq::UnitValue("3.2340342349349823e3*m/s2");      // higher precision
  EXPECT_EQ(value.to_string(oformat), "3234.034235*m*s-2");

  oformat = puq::UnitFormat(puq::MathFormat::ASCII, 10);    // precision and ASCII format
  value = puq::UnitValue("3.2340342349349823e3*km-2");
  EXPECT_EQ(value.to_string(oformat), "3234.034235⋅km⁻²");
  
}

TEST(UnitFormat, SystemFormat) {

  puq::UnitFormat oformat(puq::SystemFormat::SHOW);
  puq::Quantity q("23*cm2");
  EXPECT_EQ(q.to_string(oformat), "SI_23*cm2");

  oformat = puq::UnitFormat(puq::SystemFormat::SHOW, puq::MathFormat::ASCII);
  q = puq::Quantity("23*ft2", puq::SystemType::US);
  EXPECT_EQ(q.to_string(oformat), "US 23⋅ft²");

}

#ifdef PREPROCESS_SYSTEM
TEST(UnitFormat, PreprocessSystem) {
  
  puq::Quantity q1, q2;
  
  q1 = puq::Quantity(34,"ESU_statA");    // state the unit system in the unit expression
  q2 = q1.convert("Fr/ms",puq::SystemType::ESU);
  EXPECT_EQ(q2.to_string(), "0.034*Fr*ms-1");
  
  q1 = puq::Quantity(34,"US ft");        // same but without the underscore
  EXPECT_EQ(q1.to_string(), "34*ft");
  EXPECT_EQ(q1.unit_system(), "US");
  
}
#endif

#ifdef PREPROCESS_SYMBOLS
TEST(UnitFormat, PreprocessSymbols) {
  
  puq::Quantity q;

  q = puq::Quantity("6.23537×10−12*C4⋅m4⋅J−3");      // symbols
  EXPECT_EQ(q.to_string(), "6.23537e-12*C4*m4*J-3");

  q = puq::Quantity("6.23537×1012*C4⋅m4⋅J−3");
  EXPECT_EQ(q.to_string(), "6.23537e+12*C4*m4*J-3");

  q = puq::Quantity("6.23537×10⁻²⋅C³");              // exponents
  EXPECT_EQ(q.to_string(), "0.0623537*C3");
  
}
#endif
