#include <gtest/gtest.h>
#include <string>
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

TEST_F(LRUCacheTest, PutNonExist)
{
  cachePtr->put(1, "abc");
  cachePtr->put(2, "cde");
  cachePtr->put(3, "def");
  cachePtr->put(4, "efg");
  printCache(*cachePtr);
  EXPECT_EQ(4, cachePtr->size());
}

TEST_F(LRUCacheTest, PutExisting)
{
  cachePtr->put(3, "d");
  auto entries = cachePtr->entries();
  EXPECT_EQ(entries[0].first, 3);
  EXPECT_EQ(entries[0].second, "d");
  printCache(*cachePtr);
}

TEST_F(LRUCacheTest, Get)
{
  string output = "";
  cachePtr->get(2, output);
  auto entries = cachePtr->entries();
  EXPECT_EQ(entries[0].second, output);
  printCache(*cachePtr);
}

