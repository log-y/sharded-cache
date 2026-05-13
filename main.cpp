// main.cpp

#include <iostream>
#include <string>
#include <assert.h>
#include <thread>
#include <chrono>
#include <assert.h>
#include <random>

#include "cache.h"

using namespace std;

int OPS_PER_THREAD = 40000;
int THREADS = 60;
int NUM_SHARDS = 126;
int CAPACITY_PER_SHARD = 4098;
int READ_TO_WRITES = 0;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr(1, 1000);

void run_basic_tests();
void basic_cache_tests();
void stress_test_helper(Cache &cache, int num_operations, int thread_id);
void stress_test();
void stress_test_single_threaded();

int main(int argv, char *argc[])
{
  run_basic_tests();
  basic_cache_tests();

  auto start_single = chrono::high_resolution_clock::now();
  stress_test_single_threaded();
  auto end_single = chrono::high_resolution_clock::now();

  auto start_multi = chrono::high_resolution_clock::now();
  stress_test();
  auto end_multi = chrono::high_resolution_clock::now();

  auto duration_single = chrono::duration_cast<chrono::milliseconds>(end_single - start_single);
  auto duration_multi = chrono::duration_cast<chrono::milliseconds>(end_multi - start_multi);

  cout << "Time for single threaded ops: " << duration_single.count() << "ms" << endl;
  cout << "Time for multi threaded ops: " << duration_multi.count() << "ms" << endl;

  return 0;
}

void stress_test_single_threaded()
{
  Shard shard(NUM_SHARDS * CAPACITY_PER_SHARD);

  cout << "starting single threaded stress test" << endl;

  for (int i = 0; i < OPS_PER_THREAD * THREADS; i++)
  {
    int key = i;
    int val = i + (key * 1000);

    shard.set(key, val);
    int retrieved = shard.get(key);
    for (int j = 0; j < READ_TO_WRITES; j++){
      shard.get(key - j);
    }
    assert(retrieved == (i + (key * 1000)));
  }

  cout << "ending single threaded stress test" << endl;
}

void stress_test()
{
  Cache cache(NUM_SHARDS, CAPACITY_PER_SHARD);
  vector<thread> workers;

  cout << "starting stress test" << endl;

  for (int i = 0; i < THREADS; i++)
  {
    workers.emplace_back(stress_test_helper, ref(cache), OPS_PER_THREAD, i);
  }

  for (auto &t : workers)
  {
    t.join();
  }

  cout << "ending stress test" << endl;
}

void stress_test_helper(Cache &cache, int num_operations, int thread_id)
{
  for (int i = 0; i < num_operations; i++)
  {
    int key = i;
    int val = i + (key * 1000);

    cache.set(key, val);
    int retrieved = cache.get(key);
    for (int j = 0; j < READ_TO_WRITES; j++){
      cache.get(key - j);
    }
    assert(retrieved == (i + (key * 1000)));
  }
}

void run_basic_tests()
{
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

void basic_cache_tests()
{
  Cache cache = Cache(1, 2);

  cache.set(1, 10);
  cache.set(2, 20);

  assert(cache.get(1) == 10);
  assert(cache.get(2) == 20);

  cache.set(3, 30);

  assert(cache.get(2) == 20);
  assert(cache.get(1) == -1);
  assert(cache.get(3) == 30);

  cache.set(4, 40);

  assert(cache.get(2) == -1);
  assert(cache.get(3) == 30);
  assert(cache.get(4) == 40);

  cout << "basic cache tests are successful!" << endl;
}