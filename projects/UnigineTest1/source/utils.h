#pragma once
#include <string>

namespace Utils {
bool FileExists(const std::string& filePath);
bool DirExists(const std::string& dirPath);
bool CreateDir(const std::string& dirPath);

bool StringStartsWith(const std::string& originStr, const std::string& substr);
}