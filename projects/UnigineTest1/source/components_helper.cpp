#include "components_helper.h"
#include "source/utils.h"
#include "source/logger.h"

ComponentsHelper::ComponentsHelper(Config* config) {
  config_ = config;
}

void ComponentsHelper::BuildComponents() {
  Logger::Write(" === Start building components ===");

  // create directory for components dlls
  if (!Utils::DirExists(config_->GetComponentsOutDir())) {
    Utils::CreateDir(config_->GetComponentsOutDir());
  }

  // load and compile cs scripts (from cpp dllexport)
  std::string cppScriptsPath;
  std::vector<std::string> cppScriptsPaths = config_->GetCppComponents();
  for (auto it = cppScriptsPaths.begin(); it != cppScriptsPaths.end(); ++it) {
    cppScriptsPath += config_->GetAssetsDir() + "/" + (*it) + " ";
  }
  std::string cppCommandBuild = "\"" + config_->GetMcsPath() + "\"" + " " + cppScriptsPath + " -target:library -out:" +
                                config_->GetComponentsOutDir() + "/" + config_->GetComponentsCppName();
  //Compile scripts
  system(cppCommandBuild.c_str());

  // load and compile cs scripts
  std::string csharpScriptsPath = cppScriptsPath + " ";
  std::vector<std::string> csharpScriptsPaths = config_->GetCSharpComponents();
  for (auto it = csharpScriptsPaths.begin(); it != csharpScriptsPaths.end(); ++it) {
    csharpScriptsPath += config_->GetAssetsDir() + "/" + (*it) + " ";
  }
  std::string csharpCommandBuild = "\"" + config_->GetMcsPath() + "\"" + " " + csharpScriptsPath + " -target:library -out:" +
                                   config_->GetComponentsOutDir() + "/" + config_->GetComponentsCSharpName();
  //Compile scripts
  system(csharpCommandBuild.c_str());

  Logger::Write(" === End building components ===");
}
