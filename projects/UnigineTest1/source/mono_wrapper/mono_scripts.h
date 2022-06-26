#pragma once
#include "source/mono_wrapper/mono_script.h"
#include "source/config.h"

#include <string>

class MonoScripts {
 public:
  static void InitializeMono(Config* config);
  static void ReleaseMono();
  static MonoScript* CreateMonoScript(const std::string& componentsOutDir, const std::string& scriptPath, const std::string& assemblyName,
                                      const std::string& nameSpace, const std::string& className);
};