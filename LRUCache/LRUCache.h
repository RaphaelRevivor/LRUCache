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
  size_t size();
  void resize(size_t capacity);
  bool empty();

  bool get(const KeyType& key, ValueType& value);
  void put(const KeyType& key, const ValueType& value);

  vector<pair<KeyType, ValueType>> entries() const;

  struct CacheBlock{
    KeyType key;
    ValueType value;
    CacheBlock(KeyType key, ValueType value) : key(key), value(value) {}
  };

  using iterator = typename list<CacheBlock>::iterator;
  using const_iterator = typename list<CacheBlock>::const_iterator;

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;


private:
  // here it stores the iterator pointing to the real CacheBlock in the list
  unordered_map<KeyType, iterator> iterHashMap;
  // here list stores the real CacheBlock
  list<CacheBlock> cacheList;

  void moveToFront(typename list<CacheBlock>::iterator);
};

#include "LRUCache.tpp"

#endif