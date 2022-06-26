#include "logger.h"
#include <iostream>

void Logger::Write(const std::string& str) {
  std::cout << str << std::endl;
}

void Logger::Error(const std::string& str) {
  std::cerr << str << std::endl;
}
