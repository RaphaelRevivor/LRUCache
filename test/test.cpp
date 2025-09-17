#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "LRUCache/LRUCache.h"
#include "utils/print.h"

using namespace std;

class LRUCacheTest : public ::testing::Test
{
protected:
  static void SetUpTestSuite()
  {
    cachePtr = make_shared<LRUCache<int, string>>(4);
  }

  static void TearDownTestSuite()
  {
    cachePtr.reset();
  }

  static shared_ptr<LRUCache<int, string>> cachePtr;
};

std::shared_ptr<LRUCache<int, std::string>> LRUCacheTest::cachePtr = nullptr;

TEST_F(LRUCacheTest, BasicAssetion)
{
  EXPECT_EQ(4, 2*2);
}

TEST_F(LRUCacheTest, SizeAndEmpty1)
{
  EXPECT_EQ(cachePtr->size(), 0);
  EXPECT_TRUE(cachePtr->empty());
}

TEST_F(LRUCacheTest, PutNonExist)
{
  cachePtr->put(1, "abc");
  cachePtr->put(2, "cde");
  cachePtr->put(3, "def");
  cachePtr->put(4, "efg");
  printCacheEntries(*cachePtr);
  EXPECT_EQ(4, cachePtr->size());
}

TEST_F(LRUCacheTest, PutExisting)
{
  cachePtr->put(3, "d");
  auto entries = cachePtr->entries();
  EXPECT_EQ(entries[0].first, 3);
  EXPECT_EQ(entries[0].second, "d");
  printCacheEntries(*cachePtr);
}

TEST_F(LRUCacheTest, Get)
{
  string output = "";
  cachePtr->get(2, output);
  auto entries = cachePtr->entries();
  EXPECT_EQ(entries[0].second, output);
  printCacheEntries(*cachePtr);
}

TEST_F(LRUCacheTest, SizeAndEmpty2)
{
  EXPECT_EQ(cachePtr->size(), 4);
  EXPECT_FALSE(cachePtr->empty());
}

TEST_F(LRUCacheTest, Iterators)
{
  // normal iterators
  cout << "Using iterators..." << endl;
  ostringstream oss1;
  ostringstream oss2;
  streambuf* oldBuf;
  {
    oldBuf = cout.rdbuf(oss1.rdbuf());
    printCacheEntries(*cachePtr);
    cout.rdbuf(oldBuf);
  }
  {
    oldBuf = cout.rdbuf(oss2.rdbuf());
    int i = 0;
    cout << "The LRU cache contains:" << endl;
    for(const auto& [k,v] : *cachePtr)
    {
      if (i == 0)
      {
        EXPECT_EQ(k, 2);
        EXPECT_EQ(v, "cde");
      }
      cout << i << ", " << k << ":" << v << endl;
      i++;
    }
    cout.rdbuf(oldBuf);
  }
  EXPECT_EQ(oss1.str(), oss2.str());
  cout << oss1.str() << endl;
  cout << oss2.str() << endl;
  oss1.str("");
  oss1.clear();
  oss2.str("");
  oss2.clear();

  // const iterators
  cachePtr->put(4, "e");
  auto cachePtrConst = make_shared<const LRUCache<int, string>>(*cachePtr);
  cout << "Using const iterators..." << endl;
  {
    oldBuf = cout.rdbuf(oss1.rdbuf());
    printCacheEntries(*cachePtrConst);
    cout.rdbuf(oldBuf);
  }
  {
    oldBuf = cout.rdbuf(oss2.rdbuf());
    printCache(*cachePtrConst);
    cout.rdbuf(oldBuf);
  }
  EXPECT_EQ(oss1.str(), oss2.str());
  cout << oss1.str() << endl;
  cout << oss2.str() << endl;
}

TEST_F(LRUCacheTest, Resize)
{
  cout << "Before shrinking:" << endl;
  printCache(*cachePtr);

  cout << "After shrinking to size 2:" << endl;
  cachePtr->resize(2);
  printCache(*cachePtr);
  EXPECT_EQ(cachePtr->size(), 2);
  EXPECT_EQ(cachePtr->entries()[0].first, 4);

  cout << "After expanding to size 3:" << endl;
  cachePtr->resize(3);
  cachePtr->put(5, "fgh");
  printCache(*cachePtr);
  EXPECT_EQ(cachePtr->entries()[0].first, 5);
}