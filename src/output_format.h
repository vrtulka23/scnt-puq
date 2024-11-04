#ifndef PUQ_OUTPUT_FORMAT_H
#define PUQ_OUTPUT_FORMAT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>

#include "settings.h"

namespace puq {

  template<typename T, typename... Args>
  std::optional<T> get_option(const Args&... args) {
    std::optional<T> result;    
    ([&](const auto& arg) {
      if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, T>) {
	result = arg;
      }
    }(args), ...);
    return result;
  };
  
  enum class SystemFormat {HIDE, SHOW};
  enum class MathFormat {BASIC, PRETTY, LATEX};
  
  class OutputFormat {
  public:
    SystemFormat system;
    int precision;
    MathFormat math;
    
    OutputFormat(const auto&... args) {
      math = get_option<MathFormat>(args...).value_or(MathFormat::BASIC);
      precision = get_option<int>(args...).value_or(std::cout.precision());
      system = get_option<SystemFormat>(args...).value_or(SystemFormat::HIDE);
    };

    std::string format_exponents(std::string normal_str) const {
      if (math==MathFormat::BASIC) {
	return normal_str;
      } else {
	std::unordered_map<char, std::string> superscript_map = {
	  {'0', "\u2070"}, {'1', "\u00B9"}, {'2', "\u00B2"},
	  {'3', "\u00B3"}, {'4', "\u2074"}, {'5', "\u2075"},
	  {'6', "\u2076"}, {'7', "\u2077"}, {'8', "\u2078"},
	  {'9', "\u2079"}, {SYMBOL_MINUS[0], "\u207B"}, {SYMBOL_FRACTION[0], SYMBOL_FRACTION2},
	};	
	std::string superscript_str;
	for (char c : normal_str) {
	  superscript_str += superscript_map[c];
	}
	return superscript_str;
      }
    }

    std::string multiply_symbol() const {
      if (math==MathFormat::PRETTY) {
	return SYMBOL_MULTIPLY2;
      } else {
	return SYMBOL_MULTIPLY;
      }
    }

    std::string format_order(std::string normal_str) const {
      if (math==MathFormat::BASIC) {
	return normal_str;
      } else {
	size_t pos = normal_str.find(SYMBOL_EXPONENT);
	if (pos != std::string::npos) {
	  std::string exponent_str = normal_str.substr(pos+std::string(SYMBOL_EXPONENT).size(), normal_str.size());
	  normal_str = normal_str.substr(0, pos) + std::string(SYMBOL_EXPONENT2) + format_exponents(exponent_str);
	}	
	return normal_str;
      }
    }
  };
  
}

#endif // PUQ_OUTPUT_FORMAT_H
