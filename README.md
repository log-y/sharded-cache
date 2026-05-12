# sharded-cache

compile and run: 
g++ main.cpp cache.cpp shard.cpp linkedlist.cpp node.cpp -o lru_cache

compile with debug symbols:
g++ -g main.cpp shard.cpp linkedlist.cpp node.cpp -o lru_cache
gdb ./lru_cache

run with ./lru_cache

compiling indiviual files:
g++ -c node.cpp
g++ -c linkedlist.cpp
g++ -c shard.cpp

how to compile just main:
g++ -c main.cpp

how to link them together:
g++ main.o shard.o linkedlist.o node.o -o lru_cache

one-liner to compile & run:
g++ -c main.cpp && g++ main.o shard.o linkedlist.o node.o -o lru_cache && ./lru_cache