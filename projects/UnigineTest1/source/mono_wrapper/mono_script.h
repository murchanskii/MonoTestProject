#pragma once
#include <mono/metadata/assembly.h>

#include "source/mono_wrapper/mono_script_instance.h"

#include <string>

class MonoScript {
 public:
  void Initialize(const std::string& componentsOutDir, const std::string& scriptPath, const std::string& assemblyName,
                  const std::string& nameSpace, const std::string& className);

  MonoScriptInstance* CreateInstance();

  std::string GetAssemblyName();
  std::string GetNamespace();
  std::string GetClassName();

 private:
  MonoImage* monoImage_;

  std::string componentsOutDir_;
  std::string assemblyName_;
  std::string nameSpace_;
  std::string className_;
};