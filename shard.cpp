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
  if (map.find(key) == map.end())
  {
    return -1;
  }
  Node *curr_node = map[key];
  list.move_to_back(curr_node);
  return curr_node->val;
}

void Shard::set(int key, int val)
{
  // if it DOES exist, move it to the back 
  if (map.find(key) != map.end())
  {
    Node *node = map[key];
    list.move_to_back(node);
    map[key]->val = val;
    return;
  }

  // if size is full, delete the front
  if (map.size() == capacity)
  {
    Node *front = list.get_front();
    map.erase(front->key);
    list.pop_front();
  }

  // add new node to back
  Node *new_node = new Node(key, val);
  list.push_back(new_node);
  map[key] = new_node;
}

void Shard::remove(int key)
{
  if (map.find(key) == map.end())
  {
    return;
  }
  Node *curr_node = map[key];
  list.delete_node(curr_node);
  map.erase(key);
}