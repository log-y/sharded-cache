// shard.cpp

#include "shard.h"

#include <iostream>
#include <unordered_map>

Shard::Shard(int size)
{
  capacity = size;
}

int Shard::get(int key)
{
  if (map.find(key) != map.end())
  {
    return -1;
  }

  return map[key];
}

void Shard::set(int key, int val)
{
}