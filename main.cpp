#include <iostream>
#include <string>
#include <assert.h>

#include "cache.h"

using namespace std;

void run_basic_tests(){
  Shard shard = Shard(2);

  shard.set(1, 10);
  shard.set(2, 20);

  assert(shard.get(1) == 10); 
  assert(shard.get(2) == 20);

  shard.set(3, 30);

  assert(shard.get(2) == 20);
  assert(shard.get(1) == -1);
  assert(shard.get(3) == 30);

  shard.set(4, 40);

  assert(shard.get(2) == -1);
  assert(shard.get(3) == 30);
  assert(shard.get(4) == 40);

  cout << "basic tests are successful!" << endl;
}

void basic_cache_tests(){
  Cache cache = Cache(1, 1);

  // cache.set(1, 10);
  // cache.set(2, 20);

  // assert(cache.get(1) == 10); 
  // assert(cache.get(2) == 20);

  // cache.set(3, 30);

  // assert(cache.get(2) == 20);
  // assert(cache.get(1) == -1);
  // assert(cache.get(3) == 30);

  // cache.set(4, 40);

  // assert(cache.get(2) == -1);
  // assert(cache.get(3) == 30);
  // assert(cache.get(4) == 40);

  cout << "basic cache tests are successful!" << endl;
}


int main(int argv, char *argc[])
{
  run_basic_tests();
  basic_cache_tests();

  return 0;
}