#include "mono_script.h"

#include <mono/metadata/appdomain.h>
#include <mono/metadata/assembly.h>

#include "source/logger.h"

void MonoScript::Initialize(const std::string& componentsOutDir, const std::string& scriptPath, const std::string& assemblyName,
                            const std::string& nameSpace, const std::string& className) {
  componentsOutDir_ = componentsOutDir;
  assemblyName_ = assemblyName;
  nameSpace_ = nameSpace;
  className_ = className;

  MonoDomain* monoDomain = mono_domain_get();
  MonoAssembly* monoAssembly = mono_domain_assembly_open(monoDomain, &assemblyName[0]);

  MonoAssemblyName* assemblyNamePtr = mono_assembly_name_new(&assemblyName[0]);

  MonoImageOpenStatus imageOpenStatus;
  std::string assemblyPath = componentsOutDir + "/" + assemblyName;
  MonoAssembly* assembly = mono_domain_assembly_open(monoDomain, &assemblyPath[0]);
  mono_assembly_name_free(assemblyNamePtr);
  if (!assembly) {
    Logger::Error("MonoScript::Initialize()::mono_assembly_load_full() failed");
  }

  monoImage_ = mono_assembly_get_image(assembly);
  if (!monoImage_) {
    Logger::Error("MonoScript::Initialize()::mono_assembly_get_image() failed");
  }
}

MonoScriptInstance* MonoScript::CreateInstance() {
  MonoScriptInstance* instance = new MonoScriptInstance();
  instance->Initialize(componentsOutDir_, GetAssemblyName(), GetNamespace(), GetClassName());
  return instance;
}

std::string MonoScript::GetAssemblyName() {
  return assemblyName_;
}

std::string MonoScript::GetNamespace() {
  return nameSpace_;
}

std::string MonoScript::GetClassName() {
  return className_;
}
