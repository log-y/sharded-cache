// cache.cpp

#include "cache.h"

Cache::Cache(int shard_count, int shard_size){
  // initialize shards
  for(int i = 0; i < shard_count; i++){
    shards.push_back(Shard(shard_size));
    locks.push_back(make_unique<mutex>());
  }
  shard_count = shard_count;
}

int Cache::get_idx(int key){
  return (unsigned int)(key) % shard_count;
}

int Cache::get(int key){
  int idx = get_idx(key);
  locks[idx]->lock();
  int res = shards[idx].get(key);
  locks[idx]->unlock();
  return res;
}

void Cache::set(int key, int value){
  int idx = get_idx(key);
  locks[idx]->lock();
  shards[idx].set(key, value);
  locks[idx]->unlock();
}

void Cache::remove(int key){
  int idx = get_idx(key);
  locks[idx]->lock();
  shards[idx].remove(key);
  locks[idx]->unlock();
}