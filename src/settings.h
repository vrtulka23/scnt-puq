#ifndef PUQ_SETTINGS_H
#define PUQ_SETTINGS_H

#define SYMBOL_MULTIPLY "*"
#define SYMBOL_DIVIDE   "/"
#define SYMBOL_POWER    "^"
#define NUM_BASEDIM     8

//#define UNCERTAINTIES
#define FRACTIONAL_EXPONENTS

#ifdef UNCERTAINTIES
  #define MAGNITUDE_TYPE Magnitude
#else
  #define MAGNITUDE_TYPE double
#endif

#ifdef FRACTIONAL_EXPONENTS
  #define SYMBOL_FRACTION ":"
  #define EXPONENT_TYPE Exponent
#else
  #define EXPONENT_TYPE int
#endif

#endif // PUQ_SETTINGS_H
