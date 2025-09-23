#include <gtest/gtest.h>
#include <string>
#include <thread>
#include <atomic>
#include "libs/LRUCache.h"
#include "utils/print.h"

using namespace std;

const int numThreads = 5;
const int numOpsPerThread = 10000;

class LRUCacheTest : public ::testing::Test
{
public:
  void putFunc(int threadId, int numOps)
  {
    for(int i = 0; i < numOps; i++)
    {
      cachePtr->put(threadId * numOpsPerThread + i, to_string(threadId));
    }
  }

  void getFunc(int threadId, int numOps)
  {
    for(int i = 0; i < numOps; i++)
    {
      auto value = cachePtr->get(threadId * numOpsPerThread + i);
      if(value)
      {
        if(*value != to_string(threadId))
        {
          errorThread++;          
        }
      }
    }
  }

protected:
  atomic<int> errorThread = 0;
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
  auto output = cachePtr->get(2);
  auto entries = cachePtr->entries();
  if (output)
    EXPECT_EQ(entries[0].second, *output);
  printCacheEntries(*cachePtr);
}

TEST_F(LRUCacheTest, SizeAndEmpty2)
{
  EXPECT_EQ(cachePtr->size(), 4);
  EXPECT_FALSE(cachePtr->empty());
}

TEST_F(LRUCacheTest, Resize)
{
  cout << "Before shrinking:" << endl;
  printCacheEntries(*cachePtr);

  cout << "After shrinking to size 2:" << endl;
  cachePtr->resize(2);
  printCacheEntries(*cachePtr);
  EXPECT_EQ(cachePtr->size(), 2);
  EXPECT_EQ(cachePtr->entries()[0].first, 2);

  cout << "After expanding to size 3:" << endl;
  cachePtr->resize(3);
  cachePtr->put(5, "fgh");
  printCacheEntries(*cachePtr);
  EXPECT_EQ(cachePtr->entries()[0].first, 5);
}

TEST_F(LRUCacheTest, ThreadSafe)
{
  // launch writer and reader threads all together,
  // see if an issue arrises,
  // check the final size at the end of the test
  cachePtr->clear();
  cachePtr->resize(numThreads * numOpsPerThread + 10);
  vector<thread> threadVec;

  // put
  for(int i = 0; i < numThreads; i++)
  {
    threadVec.emplace_back(&LRUCacheTest::putFunc, this, i, numOpsPerThread);
  }

  // get
  for(int i = 0; i < numThreads; i++)
  {
    threadVec.emplace_back(&LRUCacheTest::getFunc, this, i, numOpsPerThread);
  }

  for(auto& thread : threadVec)
  {
    thread.join();
  }

  EXPECT_EQ(cachePtr->size(), numThreads * numOpsPerThread);
  cout << "Size of the cache: " << cachePtr->size() << endl;
  EXPECT_EQ(errorThread, 0);
}