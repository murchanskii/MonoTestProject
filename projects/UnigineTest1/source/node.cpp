#include "node.h"
#include "source/logger.h"

void Node::SetPosition(float x, float y, float z) {
  posX_ = x;
  posY_ = y;
  posZ_ = z;
}

const float Node::GetPositionX() {
  return posX_;
}

const float Node::GetPositionY() {
  return posY_;
}

const float Node::GetPositionZ() {
  return posZ_;
}

void Node::SetName(const std::string& name) {
  name_ = name;
}

std::string Node::GetName() {
  return name_;
}

void Node::DoStart() {
  Logger::Write("Node::DoStart() from C++");
}

void Node::DoUpdate() {
  Logger::Write("Node::DoUpdate() from C++");
}

void* NodeWrapper::CreateNode() {
  return new Node();
}

void NodeWrapper::ReleaseNode(void* nodePtr) {
  delete nodePtr;
}

void NodeWrapper::NodeDoStart(void* nodePtr) {
  Node* node = static_cast<Node*>(nodePtr);
  node->DoStart();
}

void NodeWrapper::NodeDoUpdate(void* nodePtr) {
  Node* node = static_cast<Node*>(nodePtr);
  node->DoUpdate();
}

void NodeWrapper::NodeSetPosition(void* nodePtr, float x, float y, float z) {
  Node* node = static_cast<Node*>(nodePtr);
  node->SetPosition(x, y, z);
}

const float NodeWrapper::NodeGetPositionX(void* nodePtr) {
  Node* node = static_cast<Node*>(nodePtr);
  return node->GetPositionX();
}

const float NodeWrapper::NodeGetPositionY(void* nodePtr) {
  Node* node = static_cast<Node*>(nodePtr);
  return node->GetPositionY();
}

const float NodeWrapper::NodeGetPositionZ(void* nodePtr) {
  Node* node = static_cast<Node*>(nodePtr);
  return node->GetPositionZ();
}

void NodeWrapper::NodeSetName(void* nodePtr, char* name) {
  Node* node = static_cast<Node*>(nodePtr);
  return node->SetName(name);
}

int NodeWrapper::NodeGetName(void* nodePtr, char* name) {
  Node* node = static_cast<Node*>(nodePtr);
  std::string nodeName = node->GetName();
  strcpy_s(name, nodeName.length() + 1, nodeName.c_str());
  return nodeName.length() + 1;
}
