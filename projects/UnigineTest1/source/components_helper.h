#pragma once
#include "source/config.h"

class ComponentsHelper {
 public:
  ComponentsHelper(Config* config);
  void BuildComponents();

 private:
  Config* config_;
};