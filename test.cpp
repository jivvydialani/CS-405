/*
Rajiv Dialani
CS-405
July 26, 2024
*/

// Uncomment the next line to use precompiled headers
 #include "pch.h"
// uncomment the next line if you do not use precompiled headers
// #include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
  ~Environment() override {}

  // Override this to define how to set up the environment.
  void SetUp() override
  {
    //  initialize random seed
    srand(time(nullptr));
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
  // create a smart point to hold our collection
  std::unique_ptr<std::vector<int>> collection;

  void SetUp() override
  { // create a new collection to be used in the test
    collection.reset( new std::vector<int>);
  }

  void TearDown() override
  { //  erase all elements in the collection, if any remain
    collection->clear();
    // free the pointer
    collection.reset(nullptr);
  }

  // helper function to add random values from 0 to 99 count times to the collection
  void add_entries(int count)
  {
    assert(count > 0);
    for (auto i = 0; i < count; ++i)
      collection->push_back(rand() % 100);
  }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
  // is the collection created
  ASSERT_TRUE(collection);

  // if empty, the size must be 0
  ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
  // is the collection empty?
  ASSERT_TRUE(collection->empty());

  // if empty, the size must be 0
  ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
  FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
  // is the collection empty?
  // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    
    add_entries(1);

  // is the collection still empty?
  // if not empty, what must the size be?
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterOrEqualToSize) 
{
    // Test for Empty Collection
    ASSERT_GE(collection->max_size(), collection->size());

    // Test for 1, 5, and 10 entries
    std::vector<int> testSizes = {1, 5, 10};
    for (int size : testSizes) {
        add_entries(size);
        ASSERT_GE(collection->max_size(), collection->size());
        collection->clear();
    }
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterOrEqualToSize)
{
    // Test for Empty Collection
    ASSERT_GE(collection->capacity(), collection->size());

    // Test for 1, 5, and 10 entries
    std::vector<int> testSizes = { 1, 5, 10 };
    for (int size : testSizes) {
        add_entries(size);
        ASSERT_GE(collection->capacity(), collection->size());
        collection->clear();
    }
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // add entries
    add_entries(1);

    // current size of collection and capacity
    auto baseSize = collection->size();
    auto baseCapacity = collection->capacity();

    // increase collection
    collection->resize(10);

    // Test for increase in capacity and collection
    ASSERT_EQ(collection->size(), baseSize + 9);
    ASSERT_GE(collection->capacity(), baseCapacity);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // add entries
    add_entries(10);

    // current size of collection
    auto baseSize = collection->size();

    // decrease collection
    collection->resize(5);

    // Test for decrease in size
    ASSERT_LT(collection->size(), baseSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeCollectionToZero)
{
    // add entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // Resize to 0 and Test for size = 0
    collection->resize(0);
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // add entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // Clear collection and Test for size = 0 and collection is empty
    collection->clear();
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // add entries
    add_entries(10);
    
    // erase collection
    collection->erase(collection->begin(), collection->end());

    // Tests for empty collection
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityOnly)
{
    auto initialCapacity = collection->capacity();

    // reserve
    collection->reserve(5);

    add_entries(1);

    // Test for size and capacity
    ASSERT_EQ(collection->size(), 1);
    ASSERT_GE(collection->capacity(), initialCapacity);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeThrowsException)
{
    // add entries
    add_entries(10);
    
    //  Test for out of range
    EXPECT_THROW(collection->at(11), std::out_of_range);
}
// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, SortCollection)
{
    add_entries(5);
    std::sort(collection->begin(), collection->end());

    // Test to ensure collection is sorted
    for (size_t i = 1; i < collection->size(); i++) {
        ASSERT_LE(collection->at(i - 1), collection->at(i));
    }
}
// Negative test
TEST_F(CollectionTest, NegativeIndexThrowsException)
{
    add_entries(5);
    EXPECT_THROW(collection->at(-1), std::out_of_range);
}