#ifndef PUQ_SETTINGS_H
#define PUQ_SETTINGS_H

#define SYMBOL_MULTIPLY "*"
#define SYMBOL_DIVIDE   "/"
#define SYMBOL_POWER    "^"
#define NUM_BASEDIM     8

//#define MAGNITUDE_ERRORS
#define MAGNITUDE_ARRAYS
#define MAGNITUDE_PRECISION double

#define EXPONENT_FRACTIONS
#define EXPONENT_INT_PRECISION int
#define EXPONENT_REAL_PRECISION double

#ifdef MAGNITUDE_ERRORS
  #define MAGNITUDE_TYPE Magnitude
#else
  #ifdef MAGNITUDE_ARRAYS
    #define MAGNITUDE_TYPE Array
  #else
    #define MAGNITUDE_TYPE MAGNITUDE_PRECISION
  #endif
#endif

#ifdef EXPONENT_FRACTIONS
  #define EXPONENT_TYPE Exponent
  #define SYMBOL_FRACTION ":"
#else
  #define EXPONENT_TYPE EXPONENT_INT_PRECISION
#endif


#endif // PUQ_SETTINGS_H
