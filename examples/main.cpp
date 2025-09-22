#include "main.h"

int main()
{
  LRUCache<int, string> cache(4);
  cache.put(1, "abc");
  cache.put(2, "cde");
  cache.put(3, "def");
  cache.put(4, "efg");
  printCache(cache);

  cache.put(5, "fgh");
  printCache(cache);

  cache.put(3, "d");
  printCache(cache);

  string output = "";
  cache.get(2, output);
  cout << "2's value: " << output << endl;
  printCache(cache);

  return 0;
}