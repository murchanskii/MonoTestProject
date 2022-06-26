#pragma once
#include <string>
#include <vector>

class Config {
 public:
  static const std::string ConfigDefaultPath;

  bool Load(const std::string& configPath);

  std::string GetDomainName();
  std::string GetMcsPath();
  std::string GetMonoAssemblyDir();
  std::string GetMonoConfigDir();
  std::string GetAssetsDir();
  std::string GetComponentsOutDir();
  std::string GetComponentsCppName();
  std::string GetComponentsCSharpName();
  std::vector<std::string> GetCppComponents();
  std::vector<std::string> GetCSharpComponents();

 private:
  std::string domainName_;
  std::string mcsPath_;
  std::string monoAssemblyDir_;
  std::string monoConfigDir_;
  std::string assetsDir_;
  std::string outDir_;
  std::string cppDllName_;
  std::string csharpDllName_;
  std::vector<std::string> cppComponents_;
  std::vector<std::string> csharpComponents_;

  void Parse(const std::string& configPath);
};