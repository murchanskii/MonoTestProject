#include "mono_scripts.h"

#include <mono/jit/jit.h>

#include "source/logger.h"

void MonoScripts::InitializeMono(Config* config) {
  mono_set_dirs(config->GetMonoAssemblyDir().c_str(), config->GetMonoConfigDir().c_str());
  MonoDomain* domain;
  domain = mono_jit_init(config->GetDomainName().c_str());
  if (!domain) {
    Logger::Error("MonoWrapper::Initialize()::mono_jit_init() failed");
  }
}

void MonoScripts::ReleaseMono() {
  MonoDomain* domain = mono_domain_get();
  mono_jit_cleanup(domain);
}

MonoScript* MonoScripts::CreateMonoScript(const std::string& componentsOutDir,
    const std::string& scriptPath, const std::string& assemblyName,
    const std::string& nameSpace, const std::string& className) {
  if (scriptPath.empty()) {
    Logger::Error("MonoScripts::CreateMonoScript()::scriptContents empty");
    return nullptr;
  }
  MonoScript* script = new MonoScript();
  script->Initialize(componentsOutDir, scriptPath, assemblyName, nameSpace, className);
  return script;
}
