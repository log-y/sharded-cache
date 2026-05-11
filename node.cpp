// node.cpp

#include "node.h"

Node::Node(int k, int v){
  key = k;
  val = v;
  next = nullptr;
  prev = nullptr;
}