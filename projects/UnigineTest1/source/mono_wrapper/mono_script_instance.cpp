#include "mono_script_instance.h"

#include <mono/jit/jit.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include "source/logger.h"

void MonoScriptInstance::Initialize(const std::string& componentsOutDir, const std::string& assemblyName, const std::string& nameSpace,
                                    const std::string& className) {
  MonoDomain* monoDomain = mono_domain_get();
  MonoAssemblyName* assemblyNamePtr = mono_assembly_name_new(&assemblyName[0]);
  MonoImageOpenStatus imageOpenStatus;
  MonoAssembly* monoAssembly = mono_assembly_load_full(assemblyNamePtr, componentsOutDir.c_str(), &imageOpenStatus, false);
  mono_assembly_name_free(assemblyNamePtr);
  if (imageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK) {
    Logger::Error("MonoScriptInstance::Initialize()::mono_assembly_load_full() failed");
    return;
  }
  MonoImage* monoImage = mono_assembly_get_image(monoAssembly);

  MonoClass* monoClass = mono_class_from_name(monoImage, &nameSpace[0], &className[0]);
  if (!monoClass) {
    Logger::Error("MonoScriptInstance::Initialize()::mono_class_from_name() failed");
    return;
  }

  monoObject_ = mono_object_new(monoDomain, monoClass);
  if (!monoClass) {
    Logger::Error("MonoScriptInstance::Initialize()::mono_object_new failed");
    return;
  }

  mono_runtime_object_init(monoObject_);
}

void MonoScriptInstance::InvokeMethod(const std::string& methodName, const std::string& methodSignature, void** args) {
  MonoClass* monoClass = mono_object_get_class(monoObject_);
  std::string className = mono_class_get_name(monoClass);
  std::string nameSpace = mono_class_get_namespace(monoClass);

  std::string methodDescStr = nameSpace + (nameSpace.empty() ? "" : ":") +
                              className + ":" +
                              methodName + methodSignature;
  MonoMethodDesc* methodDesc = mono_method_desc_new(&methodDescStr[0], true);
  if (!methodDesc) {
    Logger::Error("MonoScriptInstance::InvokeMethod()::mono_method_desc_new failed");
    return;
  }

  MonoImage* monoImage = mono_class_get_image(monoClass);
  MonoMethod* method;
  method = mono_method_desc_search_in_image(methodDesc, monoImage);
  if (!method) {
    Logger::Error("MonoScriptInstance::InvokeMethod()::mono_method_desc_search_in_image failed");
    return;
  }

  if (methodSignature == "(string)") { // only for testing purposes
    MonoDomain* monoDomain = mono_domain_get();
    std::string str = (char*)args[0];
    MonoString* monoString = mono_string_new(monoDomain, str.c_str());
    void* monoArgs[1] = {
      monoString
    };
    mono_runtime_invoke(method, monoObject_, monoArgs, nullptr);
  } else {
    mono_runtime_invoke(method, monoObject_, args, nullptr);
  }
}
