// cache.h

#ifndef CACHE_H
#define CACHE_H

#include "shard.h"
#include <mutex>
#include <memory>
#include <vector>

using namespace std;

class Cache{
  private:
    
    vector<unique_ptr<mutex>> locks;
    vector<Shard> shards;
    int shard_count;

    int get_idx(int key);

  public:
    Cache(int shard_count, int shard_size);
    int get(int key);
    void set(int key, int value);
    void remove(int key);
};

#endif