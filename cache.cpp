// cache.cpp

#include "cache.h"
#include <iostream>

using namespace std;

Cache::Cache(int shard_count, int shard_size){
  // initialize shards
  buckets.reserve(shard_count);
  for(int i = 0; i < shard_count; i++){
    buckets.emplace_back(shard_size);
  }
  this->shard_count = shard_count;
}

uint32_t hash_int(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

int Cache::get_idx(int key){
  // uint32_t hash = hash_int(key);
  // return hash % this->shard_count;
  return (unsigned int)key % this->shard_count;
}

int Cache::get(int key){
  int idx = get_idx(key);
  lock_guard<mutex> lock(*(buckets[idx].lock));
  int res = buckets[idx].shard.get(key);
  return res;
}

void Cache::set(int key, int value){
  int idx = get_idx(key);
  lock_guard<mutex> lock(*(buckets[idx].lock));
  buckets[idx].shard.set(key, value);
}

void Cache::remove(int key){
  int idx = get_idx(key);
  lock_guard<mutex> lock(*(buckets[idx].lock));
  buckets[idx].shard.remove(key);
}