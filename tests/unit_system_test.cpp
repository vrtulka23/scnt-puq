#include <gtest/gtest.h>

#include "../src/quantity.h"
#include "../src/converter.h"

#ifdef UNIT_SYSTEM_CGS

TEST(UnitSystem, DirectSetting) {

  puq::Quantity q1, q2;
  
  q1 = puq::Quantity(34,"statA",puq::SystemData::ESU);  // explicitely state the unit system
  q2 = q1.convert("Fr/ms");
  EXPECT_EQ(q2.to_string(), "0.034*Fr*ms-1");

#ifdef PREPROCESS_SYSTEM
  q1 = puq::Quantity(34,"ESU_statA");    // state the unit system in the unit expression
  q2 = q1.convert("Fr/ms");
  EXPECT_EQ(q2.to_string(), "0.034*Fr*ms-1");  
#endif
  
}

TEST(UnitSystem, EnvironmentSetting) {
  
  puq::Quantity q1, q2;

  puq::UnitSystem us(puq::SystemData::ESU);           // set a default unit system environment

  q1 = puq::Quantity(34,"statA");                     // ESU units are available by default
  q2 = q1.convert("Fr/ms");
  EXPECT_EQ(q2.to_string(), "0.034*Fr*ms-1");  

  us.close();                                         // switch to previous system

  EXPECT_THROW(puq::Quantity(2,"statA"), puq::AtomParsingExcept);  // ESU is no more available
  
  q1 = puq::Quantity(2,"A");
  EXPECT_EQ(q1.to_string(), "2*A");                   // SI is available
  
}

TEST(UnitSystem, DirectConversionESU) {

  puq::Quantity q1, q2, q3;

  q1 = puq::Quantity(34, "J", puq::SystemData::SI);   // convert using expression
  q2 = q1.convert("erg", puq::SystemData::ESU); 
  EXPECT_EQ(q2.to_string(), "3.4e+08*erg");

  q1 = puq::Quantity(34, "J", puq::SystemData::SI);   // convert using Quantity/UnitValue
  q2 = puq::Quantity("erg", puq::SystemData::ESU); 
  q3 = q1.convert(q2); 
  EXPECT_EQ(q3.to_string(), "3.4e+08*erg");

#ifdef PREPROCESS_SYSTEM
  q1 = puq::Quantity(34, "J");       
  q2 = q1.convert("ESU_erg");                         // convert using prefix in the expression 
  EXPECT_EQ(q2.to_string(), "3.4e+08*erg");
#endif
  
}

TEST(UnitSystem, ContextConversionESU) {

  puq::Quantity q1, q2, q3;
  
  q1 = puq::Quantity(20,"statA", puq::SystemData::ESU);  
  q2 = q1.convert("A", puq::SystemData::SI, "I");           // specify conversion context
  EXPECT_EQ(q2.to_string(), "6.67128e-09*A");

  q1 = puq::Quantity("6.671282e-10*A", puq::SystemData::SI);  
  q2 = q1.convert("statA", puq::SystemData::ESU, "I");      // inverse conversion
  EXPECT_EQ(q2.to_string(), "2*statA");
  
  q1 = puq::Quantity("1.13412e-08*A", puq::SystemData::SI); // error without given context 
  EXPECT_THROW(q1.convert("statA", puq::SystemData::ESU), puq::ConvDimExcept);
  
  q1 = puq::Quantity(1,"statT", puq::SystemData::ESU);  
  q2 = q1.convert("T", puq::SystemData::SI, "B");          // specify conversion context
  EXPECT_EQ(q2.to_string(), "2.99792e+06*T"); 

  q1 = puq::Quantity(1,"erg", puq::SystemData::ESU);       // quantities that do not need a conversion context
  q2 = q1.convert("J", puq::SystemData::SI, "E");          // with a context
  EXPECT_EQ(q2.to_string(), "1e-07*J"); 
  q2 = q1.convert("J", puq::SystemData::SI);               // without a context
  EXPECT_EQ(q2.to_string(), "1e-07*J"); 
  
#ifdef PREPROCESS_SYSTEM
  q1 = puq::Quantity("6.671282e-10*A");
  q2 = q1.convert("ESU_statA", "I");                       // convert using prefix in the expression
  EXPECT_EQ(q2.to_string(), "2*statA");
#endif
  
}

#endif

#ifdef UNIT_SYSTEM_NUS

TEST(UnitSystem, ContextConversionSRU) {

  puq::Quantity q1, q2, q3;
  
  q1 = puq::Quantity(1,"<E>", puq::SystemData::SRU);  
  q2 = q1.convert("<E>", puq::SystemData::SI, "E");   
  EXPECT_EQ(q2.to_string(), "8.98755e+16*<E>");

  q1 = puq::Quantity(1,"<L_ome>", puq::SystemData::SRU);  
  q2 = q1.convert("<L_ome>", puq::SystemData::SI, "L_ome");   
  EXPECT_EQ(q2.to_string(), "2.99792e+08*<L_ome>");
  
}

TEST(UnitSystem, ContextConversionGRU) {

  puq::Quantity q1, q2, q3;
  
  q1 = puq::Quantity(1,"<E>", puq::SystemData::GRU);  
  q2 = q1.convert("<E>", puq::SystemData::SI, "E");   
  EXPECT_EQ(q2.to_string(), "1.60218e-10*<E>");

  q1 = puq::Quantity(1,"<L_ome>", puq::SystemData::GRU);  
  q2 = q1.convert("<L_ome>", puq::SystemData::SI, "L_ome");   
  EXPECT_EQ(q2.to_string(), "1.05457e-34*<L_ome>");
  
}


TEST(UnitSystem, ContextConversionGEO) {

  puq::Quantity q1, q2, q3;
  
  q1 = puq::Quantity(1,"m*[#c]2/[#G]", puq::SystemData::GEO);
  q1 = q1.convert(puq::Dformat::MKS);
  EXPECT_EQ(q1.to_string(), "1.346591(30)e+27*kg");

  q1 = puq::Quantity(1,"<E>", puq::SystemData::GEO);  
  q2 = q1.convert("<E>", puq::SystemData::SI, "E");   
  EXPECT_EQ(q2.to_string(), "1.210256(27)e+44*<E>");
  
  q1 = puq::Quantity(1,"<L_ome>", puq::SystemData::GEO);  
  q2 = q1.convert("<L_ome>", puq::SystemData::SI, "L_ome");   
  EXPECT_EQ(q2.to_string(), "4.036978(91)e+35*<L_ome>");
  
}

#endif
