// cache.cpp

#include "cache.h"

Cache::Cache(int shard_count, int shard_size){
  // initialize shards
  buckets.reserve(shard_count);
  for(int i = 0; i < shard_count; i++){
    buckets.emplace_back(shard_size);
  }
  this->shard_count = shard_count;
}

int Cache::get_idx(int key){
  return (unsigned int)(key) % shard_count;
}

int Cache::get(int key){
  int idx = get_idx(key);
  buckets[idx].lock->lock();
  int res = buckets[idx].shard.get(key);
  buckets[idx].lock->unlock();
  return res;
}

void Cache::set(int key, int value){
  int idx = get_idx(key);
  buckets[idx].lock->lock();
  buckets[idx].shard.set(key, value);
  buckets[idx].lock->unlock();
}

void Cache::remove(int key){
  int idx = get_idx(key);
  buckets[idx].lock->lock();
  buckets[idx].shard.remove(key);
  buckets[idx].lock->unlock();
}