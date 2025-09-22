#ifndef LRU_CACHE_TPP
#define LRU_CACHE_TPP

template<typename KeyType, typename ValueType>
LRUCache<KeyType, ValueType>::LRUCache(size_t capacity) : capacity(capacity)
{
}

// This function is used to read the value from the list 
template<typename KeyType, typename ValueType>
bool LRUCache<KeyType, ValueType>::get(const KeyType& key, ValueType& value)
{
  // for LRU cache, get and put are both "write" ops
  lock_guard<mutex> lock(m);
  auto iter = iterHashMap.find(key);
  if (iter != iterHashMap.end())
  {
    value = iter->second->value;
    // and the got CacheBlock needs to be moved to the beginning of the list
    moveToFront(iter->second);
    return true;
  }
  else
  {
    return false;
  }
}

// This function is used to write a key-value pair to the list 
template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::put(const KeyType& key, const ValueType& value)
{
  lock_guard<mutex> lock(m);
  auto iter = iterHashMap.find(key);
  // found, update the value
  if (iter != iterHashMap.end())
  {
    iter->second->value = value;
    moveToFront(iter->second);
  }
  // not found, new key-value
  else
  {
    if (cacheList.size() >= capacity)
    {
      // remove the least recently used key-pair in both list and hash map
      iterHashMap.erase(cacheList.back().key);
      cacheList.pop_back();
    }
    CacheBlock cacheBlock = {key, value};
    cacheList.push_front(cacheBlock);
    iterHashMap[key] = cacheList.begin();
  }
}

// private function to move a certain CacheBlock to the front
template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::moveToFront(ListIter iter)
{
  cacheList.splice(cacheList.begin(), cacheList, iter);
}

// function to return size
template<typename KeyType, typename ValueType>
size_t LRUCache<KeyType, ValueType>::size()
{
  return cacheList.size();
}

// function to compress the contents of the list into a vector of key:value pair
template<typename KeyType, typename ValueType>
vector<pair<KeyType, ValueType>> LRUCache<KeyType, ValueType>::entries()
{
  vector<pair<KeyType, ValueType>> output = {};
  for(const auto& item : cacheList)
  {
    output.emplace_back(make_pair(item.key, item.value));
  }

  return output;
}

// function to check if empty
template<typename KeyType, typename ValueType>
bool LRUCache<KeyType, ValueType>::empty()
{
  return cacheList.empty();
}

#endif