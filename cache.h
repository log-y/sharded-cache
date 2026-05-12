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
    struct Bucket{
      unique_ptr<mutex> lock;
      Shard shard;
      Bucket(int cap) : shard(cap) {}
      // Bucket(const Bucket&) = delete;
    };
    vector<Bucket> buckets;
    
    int shard_count;

    int get_idx(int key);

  public:
    Cache(int shard_count, int shard_size);
    int get(int key);
    void set(int key, int value);
    void remove(int key);
};

#endif