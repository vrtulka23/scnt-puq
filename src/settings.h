#ifndef PUQ_SETTINGS_H
#define PUQ_SETTINGS_H

#define SYMBOL_MULTIPLY "*"
#define SYMBOL_DIVIDE   "/"
#define SYMBOL_POWER    "^"
#define NUM_BASEDIM     8

#define MAGNITUDE_ERRORS
#define MAGNITUDE_ARRAYS
#define MAGNITUDE_PRECISION double

#define EXPONENT_FRACTIONS
#define EXPONENT_INT_PRECISION int
#define EXPONENT_REAL_PRECISION double

#ifdef MAGNITUDE_ARRAYS
  #define SYMBOL_ARRAY_START     "{"
  #define SYMBOL_ARRAY_END       "}"
  #define SYMBOL_ARRAY_SEPARATOR ","
  #define SYMBOL_ARRAY_MORE      "..."
#endif

#if defined(MAGNITUDE_ERRORS)
  #define MAGNITUDE_TYPE Magnitude
#elif defined(MAGNITUDE_ARRAYS)
  #define MAGNITUDE_TYPE Array
#else
  #define MAGNITUDE_TYPE MAGNITUDE_PRECISION
#endif

#ifdef EXPONENT_FRACTIONS
  #define EXPONENT_TYPE Exponent
  #define SYMBOL_FRACTION ":"
#else
  #define EXPONENT_TYPE EXPONENT_INT_PRECISION
#endif


#endif // PUQ_SETTINGS_H
