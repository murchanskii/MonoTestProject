#pragma once
#include <string>

class Node {
 public:
  void SetPosition(float x, float y, float z);
  const float GetPositionX();
  const float GetPositionY();
  const float GetPositionZ();

  void SetName(const std::string& name);
  std::string GetName();

  void DoStart();
  void DoUpdate();

 private:
  std::string name_ = "";
  float posX_ = 0.0f;
  float posY_ = 0.0f;
  float posZ_ = 0.0f;
};

namespace NodeWrapper {
extern "C" __declspec(dllexport) void* CreateNode();
extern "C" __declspec(dllexport) void ReleaseNode(void* nodePtr);
extern "C" __declspec(dllexport) void NodeDoStart(void* nodePtr);
extern "C" __declspec(dllexport) void NodeDoUpdate(void* nodePtr);
extern "C" __declspec(dllexport) void NodeSetPosition(void* nodePtr, float x, float y, float z);
extern "C" __declspec(dllexport) const float NodeGetPositionX(void* nodePtr);
extern "C" __declspec(dllexport) const float NodeGetPositionY(void* nodePtr);
extern "C" __declspec(dllexport) const float NodeGetPositionZ(void* nodePtr);
extern "C" __declspec(dllexport) void NodeSetName(void* nodePtr, char* name);
extern "C" __declspec(dllexport) int NodeGetName(void* nodePtr, char* name);
}