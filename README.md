# sharded-cache

## Overview

This is an implementation of a multi-sharded cache, alongside testing and benchmarks against a single-threaded cache to show performance gains.

**Goal** 

In a standard single-threaded LRU cache, a high-frequency stream of GET/SET requests will be serialized and executed one at a time, causing higher average latency per request at scale. A popular and somewhat easy way to fix this is through sharding, or splitting up your cache into multiple smaller caches so GET/SET requests on different keys can run concurrently, greatly increasing throughput of the server. 

The idea is that even though you might have an increased amount of overhead on the same number of key-value pairs due to creating and managing many shards in memory, the speed improvements you get by reducing lock contentions will make it worthwhile.

**Implementation**

I built a standard LRU using a hashmap and a linked list. Then, I created an orchestator class for this (see cache.cpp), where I created a number of LRUs and a mutex responsible for each. I grouped these pairs into a Bucket struct to improve cache locality. Then, I made get, set, and remove wrappers, first hashing the requested key over the number of buckets and then running the operation under a lock_guard. This capitalizes on C++'s best practices, using RAII to reduce code redundancies while maintaining thread safety. The locks ensure that threads accessing the same shard will not over-write each other and corrupt data, but threads accessing different shards can run simultaneously.

Deeper explanation: If thread A and thread B access a cache at the same time, thread A will run and thread B will be slept. When thread A's lock_guard implicitly runs unlock() after it's done, thread B will then wake up and run its operation. This introduces a performance bottleneck because sleeping and waking up threads can be CPU-intensive. If we change our design and create many shards, thread A and thread B will have a high chance of requesting different shards. If you run operations on different shards, neither thread will be slept and they can both run simultaneously. There is a chance that they will still hit the same shard, in which case one will have to be slept. But assuming we make enough shards, we can reduce this likelihood to maintain overall performance.

**Testing**

I stress tested this program by creating a multi-sharded cache and querying it over many threads concurrently running a stream of GET/SET requests. I then compared this to a single shard with the same overall capacity answering the same amount of total requests. I then validated my threads were actually running concurrently by checking 'htop' on a large number of requests and checking manually if all my CPU cores were being used at once. I tested this on a few million requests on each type of cache (single vs multi-sharded). Results are below.

**Results**

Benchmark output:
- Time for 3 million single threaded ops: 873ms
- Time for 3 million multi threaded ops over 128 shards: 114ms
- Speedup: 7.7x using 80 threads

## Compiling and running

**Compile and link all features** 

g++ main.cpp cache.cpp shard.cpp linkedlist.cpp node.cpp -o lru_cache

./lru_cache

**Compile with debug symbols**

g++ -g main.cpp cache.cpp shard.cpp linkedlist.cpp node.cpp -o lru_cache
gdb ./lru_cache

**Compiling indiviual files:**

g++ -c node.cpp
g++ -c linkedlist.cpp
g++ -c shard.cpp

**Compiling and running main for testing**

g++ -c main.cpp

g++ main.o shard.o linkedlist.o node.o -o lru_cache

**one-liner to compile & run**

g++ -c main.cpp && g++ main.o shard.o linkedlist.o node.o -o lru_cache && ./lru_cache