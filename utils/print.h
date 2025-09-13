#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include "LRUCache/LRUCache.h"

template<typename KeyType, typename ValueType>
void printCache(LRUCache<KeyType, ValueType> &cache)
{
  auto entries = cache.entries();
  int i = 0;
  cout << "The LRU cache contains:" << endl;
  for(const auto& ele : entries)
  {
    cout << i << ", " << ele.first << ":" << ele.second << endl;
    i++;
  }
}
#endif