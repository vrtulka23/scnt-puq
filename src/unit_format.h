#ifndef PUQ_UNIT_FORMAT_H
#define PUQ_UNIT_FORMAT_H

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
  enum class MathFormat   {BASIC, ASCII, MATH, HTML};
  enum class PartFormat   {BOTH, NUMBER, UNITS};
  enum class BaseFormat   {UNITS, MGS, MKS, CGS, FPS};
  
  class UnitFormat {
    static const std::unordered_map<char, std::string> superscript_map;	
    static const std::unordered_map<std::string, std::string> symbol_map;
  public:
    SystemFormat system;
    int precision;
    MathFormat math;
    PartFormat part;
    BaseFormat base;
    
    UnitFormat(const auto&... args) {
      math = get_option<MathFormat>(args...).value_or(MathFormat::BASIC);
      precision = get_option<int>(args...).value_or(std::cout.precision());
      system = get_option<SystemFormat>(args...).value_or(SystemFormat::HIDE);
      part = get_option<PartFormat>(args...).value_or(PartFormat::BOTH);
      base = get_option<BaseFormat>(args...).value_or(BaseFormat::UNITS);
    };

    static bool preprocess_system(std::string& expression, const std::string& abbrev);
    static void preprocess_symbols(std::string& expression);
    std::string multiply_symbol() const;
    std::string format_exponents(std::string expression) const;
    std::string format_order(std::string expression) const;
    std::string format_system(std::string expression, const std::string& abbrev) const;
    
  };
  
}

#endif // PUQ_UNIT_FORMAT_H
