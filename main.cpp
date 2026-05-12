#include <iostream>
#include <string>
#include <assert.h>

#include "shard.h"
#include "linkedlist.h"

using namespace std;

int main(int argv, char *argc[])
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

  cout << "tests are successful!" << endl;

  return 0;
}