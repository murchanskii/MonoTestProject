#include "config.h"

#include <json/json.hpp>

#include "source/utils.h"
#include "source/logger.h"

#include <fstream>

const std::string Config::ConfigDefaultPath = "config.json";

bool Config::Load(const std::string& configPath) {
  if (!Utils::FileExists(configPath)) {
    Logger::Error("Config::Initialize() config not found");
    return false;
  }
  Parse(configPath);
  return true;
}

void Config::Parse(const std::string& configPath) {
  std::ifstream file(configPath);
  std::string contents;
  std::string str;
  while (std::getline(file, str)) {
    contents += str;
  }

  json::JSON jsonObj = json::JSON::Load(contents);

  domainName_ = jsonObj["domainName"].ToString();
  mcsPath_ = jsonObj["mcsPath"].ToString();
  monoAssemblyDir_ = jsonObj["monoAssemblyDir"].ToString();
  monoConfigDir_ = jsonObj["monoConfigDir"].ToString();
  assetsDir_ = jsonObj["assetsDir"].ToString();
  outDir_ = jsonObj["outDir"].ToString();
  cppDllName_ = jsonObj["cppDllName"].ToString();
  csharpDllName_ = jsonObj["csharpDllName"].ToString();

  json::JSON cppComponentsJson = jsonObj["cppComponents"];
  for (int i = 0; i < cppComponentsJson.length(); ++i) {
    cppComponents_.push_back(cppComponentsJson.at(i).ToString());
  }
  json::JSON csharpComponentsJson = jsonObj["csharpComponents"];
  for (int i = 0; i < csharpComponentsJson.length(); ++i) {
    csharpComponents_.push_back(csharpComponentsJson.at(i).ToString());
  }
}

std::string Config::GetDomainName() {
  return domainName_;
}

std::string Config::GetMcsPath() {
  return mcsPath_;
}

std::string Config::GetMonoAssemblyDir() {
  return monoAssemblyDir_;
}

std::string Config::GetMonoConfigDir() {
  return monoConfigDir_;
}

std::string Config::GetAssetsDir() {
  return assetsDir_;
}

std::string Config::GetComponentsOutDir() {
  return outDir_;
}

std::string Config::GetComponentsCppName() {
  return cppDllName_;
}

std::string Config::GetComponentsCSharpName() {
  return csharpDllName_;
}

std::vector<std::string> Config::GetCppComponents() {
  return cppComponents_;
}

std::vector<std::string> Config::GetCSharpComponents() {
  return csharpComponents_;
}
