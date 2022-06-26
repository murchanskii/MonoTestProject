#pragma once
#include <mono/metadata/object.h>

#include <string>

class MonoScriptInstance {
 public:
  void Initialize(const std::string& componentsOutDir, const std::string& assemblyName,
                  const std::string& nameSpace, const std::string& className);
  void InvokeMethod(const std::string& methodName, const std::string& methodSignature, void** args);

 private:
  MonoObject* monoObject_;
};