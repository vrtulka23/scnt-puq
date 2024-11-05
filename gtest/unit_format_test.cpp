#include <gtest/gtest.h>

#include "../src/quantity.h"
#include "../src/value/value.h"

TEST(UnitFormat, ExponentFormat) {

  puq::UnitFormat format(puq::MathFormat::ASCII);
 
  puq::Exponent e = puq::Exponent(-2);
  EXPECT_EQ(e.to_string(format), "⁻²");    // integer exponents
  
#ifdef EXPONENT_FRACTIONS
  e = puq::Exponent(3,2);    
  EXPECT_EQ(e.to_string(format), "³ᐟ²");   // positive fractional exponents
  
  e = puq::Exponent(-3,2);    
  EXPECT_EQ(e.to_string(format), "⁻³ᐟ²");  // negative fractional exponents
#endif
  
}

TEST(UnitFormat, DimensionsFormat) {

  puq::UnitFormat format;
  puq::Dimensions d(2.340342349349823e6,{1,2,3,0,0,0,0,0});
  
  format = puq::UnitFormat(10);                               // increased output precision
  EXPECT_EQ(d.to_string(format), "2340342.349*m*g2*s3");

  format = puq::UnitFormat(puq::MathFormat::ASCII);           // ASCII math format
  EXPECT_EQ(d.to_string(format), "2.34034×10⁰⁶⋅m⋅g²⋅s³");
  
  format = puq::UnitFormat(puq::DisplayFormat::MAGNITUDE);    // display only magnitudes
  EXPECT_EQ(d.to_string(format), "2.34034e+06");
  
  format = puq::UnitFormat(puq::DisplayFormat::UNITS);        // display only units
  EXPECT_EQ(d.to_string(format), "m*g2*s3");
  
  format = puq::UnitFormat(puq::BaseFormat::CGS);             // change unit base
  EXPECT_EQ(d.to_string(format), "2.34034e+08*cm*g2*s3");

  format = puq::UnitFormat({          // change unit base and show only magnitude
      puq::BaseFormat::CGS,   
      puq::DisplayFormat::MAGNITUDE
    });
  EXPECT_EQ(d.to_string(format), "2.34034e+08");

  format = puq::UnitFormat({          // change unit base and show only units
      puq::BaseFormat::CGS, 
      puq::DisplayFormat::UNITS
    }); 
  EXPECT_EQ(d.to_string(format), "cm*g2*s3");
  
}

TEST(UnitFormat, BaseUnitsFormat) {

  puq::UnitFormat format(puq::MathFormat::ASCII);
  puq::BaseUnits bus;
  
  bus = puq::BaseUnits("kg*m2/s2");               // integer exponents
  EXPECT_EQ(bus.to_string(format), "kg⋅m²⋅s⁻²");

#ifdef EXPONENT_FRACTIONS
  bus = puq::BaseUnits("m*kg-2:3");               // fractional exponents
  EXPECT_EQ(bus.to_string(format), "m⋅kg⁻²ᐟ³");  
#endif
  
}


TEST(UnitFormat, MagnitudeFormat) {

  puq::Magnitude m;
  puq::UnitFormat format;

  format = puq::UnitFormat(puq::MathFormat::ASCII);
  m = puq::Magnitude(3.234019394939e12);          // without errors
  EXPECT_EQ(m.to_string(format), "3.23402×10¹²");

  format = puq::UnitFormat(10);
  m = puq::Magnitude(3.2340342349349823e3);       // increased precision
  EXPECT_EQ(m.to_string(format), "3234.034235");
  
#ifdef MAGNITUDE_ERRORS
  format = puq::UnitFormat(puq::MathFormat::ASCII);
  m = puq::Magnitude(3.234019394939e12, 2.34e8);  // with errors
  EXPECT_EQ(m.to_string(format), "3.23402(23)×10¹²");
#endif
  
}

TEST(UnitFormat, UnitValueFormat) {
  
  puq::UnitValue value;
  puq::UnitFormat format;
  
  format = puq::UnitFormat(puq::MathFormat::ASCII);
  value = puq::UnitValue("3*km-2*m/s2");                    // normal units
  EXPECT_EQ(value.to_string(format), "3⋅km⁻²⋅m⋅s⁻²");

  value = puq::UnitValue("3.234019394939e12*km-2");         // decimal orders
  EXPECT_EQ(value.to_string(format), "3.23402×10¹²⋅km⁻²");
  
  format = puq::UnitFormat(10);
  value = puq::UnitValue("3.2340342349349823e3*m/s2");      // higher precision
  EXPECT_EQ(value.to_string(format), "3234.034235*m*s-2");

  format = puq::UnitFormat(puq::MathFormat::ASCII, 10);     // precision and ASCII format
  value = puq::UnitValue("3.2340342349349823e3*km-2");
  EXPECT_EQ(value.to_string(format), "3234.034235⋅km⁻²");

  format = puq::UnitFormat(puq::DisplayFormat::MAGNITUDE);  // display only magnitude
  value = puq::UnitValue("3*km/s");                         
  EXPECT_EQ(value.to_string(format), "3");
  
  format = puq::UnitFormat(puq::DisplayFormat::UNITS);      // display only magnitude
  value = puq::UnitValue("3*km/s");                         
  EXPECT_EQ(value.to_string(format), "km*s-1");
  
}

TEST(UnitFormat, SystemFormat) {

  puq::UnitFormat format(puq::SystemFormat::SHOW);
  puq::Quantity q("23*cm2");
  EXPECT_EQ(q.to_string(format), "SI_23*cm2");

  format = puq::UnitFormat(puq::SystemFormat::SHOW, puq::MathFormat::ASCII);
  q = puq::Quantity("23*ft2", puq::SystemType::US);
  EXPECT_EQ(q.to_string(format), "US 23⋅ft²");

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
