#include "utils.h"
#include <windows.h>

bool Utils::FileExists(const std::string& filePath) {
  DWORD ftyp = GetFileAttributesA(filePath.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES) {
    return false;
  }
  return ftyp;
}

bool Utils::DirExists(const std::string& dirPath) {
  return FileExists(dirPath) & FILE_ATTRIBUTE_DIRECTORY;
}

bool Utils::CreateDir(const std::string& dirPath) {
  return CreateDirectoryA(dirPath.c_str(), NULL) ||
         GetLastError() == ERROR_ALREADY_EXISTS;
}

bool Utils::StringStartsWith(const std::string& originStr, const std::string& substr) {
  return originStr.rfind(substr, 0) == 0;
}
