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
  Node *curr_node = map[key];
  list.move_to_back(curr_node);
  return curr_node->val;
}

void Shard::set(int key, int val)
{
  // if the key does NOT exist, create it and rearrange if needed
  if (map.find(key) != map.end())
  {
    if (map.size() == capacity)
    {
      list.pop_front();
    }
    try {
      Node *new_node = new Node(key, val);
      list.push_back(new_node);
      map[key] = new_node;
    }
    catch(const std::bad_alloc& e){
      std::cerr << "error allocating" << std::endl;
    }
    return;
  }

  // if the key DOES exist, update the value and order of linked list
  Node* curr_node = map[key];
  curr_node->val = val;

  list.move_to_back(curr_node);
}

void Shard::remove(int key){
  if (map.find(key) == map.end()){
    return;
  }
  Node* curr_node = map[key];
  list.delete_node(curr_node);
}