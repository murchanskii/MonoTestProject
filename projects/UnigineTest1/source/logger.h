#pragma once
#include <string>

class Logger {
 public:
  static void Write(const std::string& str);
  static void Error(const std::string& str);
};