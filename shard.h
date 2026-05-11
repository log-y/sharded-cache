// shard.h

#ifndef SHARD_H
#define SHARD_H

#include <unordered_map>
#include "linkedlist.h"

class Shard {
  private:
    int capacity;
    std::unordered_map<int, int> map;
    LinkedList* list;

  public:
    Shard(int size);
    int get(int key);
    void set(int key, int val);
};

#endif