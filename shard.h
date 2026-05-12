// shard.h

#ifndef SHARD_H
#define SHARD_H

#include <unordered_map>
#include "linkedlist.h"

class Shard
{
private:
  int capacity;

public:
  std::unordered_map<int, Node *> map;
  LinkedList list;
  Shard(int size);
  int get(int key);
  void set(int key, int val);
  void remove(int key);
};

#endif