#ifndef PUQ_SETTINGS_H
#define PUQ_SETTINGS_H

/*
 *  General settings
 */
#define NUM_BASEDIM     8
#define SYMBOL_PLUS     "+"
#define SYMBOL_MINUS    "-"
#define SYMBOL_MULTIPLY "*"
#define SYMBOL_DIVIDE   "/"
#define SYMBOL_POWER    "^"
#define SYMBOL_EXPONENT "e"
#define SYMBOL_QUANTITY_START "<"
#define SYMBOL_QUANTITY_END   ">"
#define SYMBOL_SIFACTOR_START "|"
#define SYMBOL_SIFACTOR_END   "|"

/*
 *  Numerical precision
 */
#define MAGNITUDE_PRECISION     double
#define EXPONENT_INT_PRECISION  int
#define EXPONENT_REAL_PRECISION double

/*
 *  Modules
 */
#define MAGNITUDE_ERRORS
#define MAGNITUDE_ARRAYS
#define EXPONENT_FRACTIONS
#define UNITS_TEMPERATURES
#define UNITS_LOGARITHMIC
#define UNIT_SYSTEM_CGS
#define UNIT_SYSTEM_AU
#define UNIT_SYSTEM_EUS
#define PREPROCESS_EXPRESSIONS

/*
 *  Module specific settings
 */
#ifdef MAGNITUDE_ARRAYS
  #define SYMBOL_ARRAY_START     "{"
  #define SYMBOL_ARRAY_END       "}"
  #define SYMBOL_ARRAY_SEPARATOR ","
  #define SYMBOL_ARRAY_MORE      "..."
#endif
#ifdef EXPONENT_FRACTIONS
  #define SYMBOL_FRACTION        ":"
#endif

/*
 *  Type settings 
 */
#if defined(MAGNITUDE_ERRORS)
  #define MAGNITUDE_TYPE Magnitude
  #ifdef MAGNITUDE_ARRAYS
    #define MAGNITUDE_VALUE Array
  #else
    #define MAGNITUDE_VALUE MAGNITUDE_PRECISION
  #endif
#elif defined(MAGNITUDE_ARRAYS)
  #define MAGNITUDE_TYPE Array
#else
  #define MAGNITUDE_TYPE MAGNITUDE_PRECISION
#endif

#ifdef EXPONENT_FRACTIONS
  #define EXPONENT_TYPE Exponent
#else
  #define EXPONENT_TYPE EXPONENT_INT_PRECISION
#endif

#endif // PUQ_SETTINGS_H
