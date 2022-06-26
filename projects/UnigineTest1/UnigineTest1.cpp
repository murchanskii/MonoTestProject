#include "source/mono_wrapper/mono_scripts.h"
#include "source/logger.h"
#include "source/config.h"
#include "source/components_helper.h"

int main(int argc, char* argv[]) {
  std::string configPath = Config::ConfigDefaultPath;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      if (i + 1 < argc &&
          (strcmp(argv[i], "-c") == 0 ||
           strcmp(argv[i], "--config") == 0)) {
        configPath = argv[i + 1];
      }
    }
  }

  Config config;
  if (!config.Load(configPath)) {
    return 1;
  }

  ComponentsHelper componentsHelper(&config);
  componentsHelper.BuildComponents();
  MonoScripts::InitializeMono(&config);

  {
    MonoScript* scriptCpp = MonoScripts::CreateMonoScript(config.GetComponentsOutDir(), config.GetCppComponents()[0],
                            config.GetComponentsCppName(), "", "Node");
    MonoScriptInstance* scriptCppInstance0 = scriptCpp->CreateInstance();

    float posX0 = 1.0f;
    float posY0 = 1453.0f;
    float posZ0 = -431.0f;

    void* args0[3] = {
      &posX0,
      &posY0,
      &posZ0
    };

    float posX1 = -42043.0f;
    float posY1 = 30.0f;
    float posZ1 = 10.0f;

    void* args1[3] = {
      &posX1,
      &posY1,
      &posZ1
    };

    char name[] = "name";
    void* argsName[1] = {
      name
    };

    char name1[] = "hdjfskhfjk fsdfs";
    void* argsName1[1] = {
      name1
    };

    Logger::Write(" === Cpp class object #0 ===");
    scriptCppInstance0->InvokeMethod("SetPosition", "(single,single,single)", args0);
    scriptCppInstance0->InvokeMethod("Start", "()", nullptr);
    scriptCppInstance0->InvokeMethod("PrintPosition", "()", nullptr);
    scriptCppInstance0->InvokeMethod("SetName", "(string)", argsName);
    scriptCppInstance0->InvokeMethod("PrintName", "()", nullptr);
    Logger::Write(" ");

    Logger::Write(" === Cpp class object #1 ===");
    MonoScriptInstance* scriptCppInstance1 = scriptCpp->CreateInstance();
    scriptCppInstance1->InvokeMethod("Update", "()", nullptr);
    scriptCppInstance1->InvokeMethod("SetPosition", "(single,single,single)", args1);
    scriptCppInstance1->InvokeMethod("PrintPosition", "()", nullptr);
    scriptCppInstance1->InvokeMethod("SetName", "(string)", argsName1);
    scriptCppInstance1->InvokeMethod("PrintName", "()", nullptr);
    Logger::Write(" ");

    delete scriptCppInstance1;
    delete scriptCppInstance0;
    delete scriptCpp;
  }

  {
    MonoScript* scriptCSharp = MonoScripts::CreateMonoScript(config.GetComponentsOutDir(), config.GetCSharpComponents()[0],
                               config.GetComponentsCSharpName(), "", "MyNode");
    MonoScriptInstance* scriptCSharpInstance = scriptCSharp->CreateInstance();
    Logger::Write(" === Csharp class object #0 ===");
    scriptCSharpInstance->InvokeMethod("Start", "()", nullptr);

    float posX = 1.654f;
    float posY = 2.21f;
    float posZ = 3.4324f;

    void* args[3] = {
      &posX,
      &posY,
      &posZ
    };
    scriptCSharpInstance->InvokeMethod("SetPosition", "(single,single,single)", args);
    scriptCSharpInstance->InvokeMethod("PrintPosition", "()", nullptr);
    Logger::Write(" ");

    delete scriptCSharpInstance;
    delete scriptCSharp;
  }

  MonoScripts::ReleaseMono();

  return 0;
}