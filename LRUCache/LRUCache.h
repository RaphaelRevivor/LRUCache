#ifndef LRU_CACHE_H
#define LRU_CACHE_H

// for size_t
#include <cstddef>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename KeyType, typename ValueType>

class LRUCache
{
public:
  // for single argument initialization,
  // prevent unintended usage (e.g. implicit conversion)
  explicit LRUCache(size_t capacity);
  ~LRUCache() = default;

  size_t capacity;

  bool get(const KeyType& key, ValueType& value);
  void put(const KeyType& key, const ValueType& value);
  size_t size();
  vector<pair<KeyType, ValueType>> entries();

private:
  struct CacheBlock{
    KeyType key;
    ValueType value;
  };

  using ListIter = typename list<CacheBlock>::iterator;

  // here it stores the iterator pointing to the real CacheBlock in the list
  unordered_map<KeyType, ListIter> iterHashMap;
  // here list stores the real CacheBlock
  list<CacheBlock> cacheList;

  void moveToFront(typename list<CacheBlock>::iterator);
};

#include "LRUCache.tpp"

#endif