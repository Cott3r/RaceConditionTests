//
// Created by testing on 08.07.22.
//
// This program uses the googletest Framework in order to run
// The googletest Framework can be found here: https://github.com/google/googletest
// The googletest Framework Licence is here: ./lib/LICENSE
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Worker.h"
#include "Factory.h"

using namespace std;

// The fixture for testing class FactoryTest.
class FactoryTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    Factory* factory;

    FactoryTest() {
      // You can do set-up work for each test here.
      factory = new Factory();
    }

    ~FactoryTest() override {
      // You can do clean-up work that doesn't throw exceptions here.
      delete factory;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    void TearDown() override {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};


TEST_F(FactoryTest, Test1)
{
  if(!factory->runTest())
  {
    FAIL() << factory->toString();
  }
}

TEST_F(FactoryTest, Test2)
{
  FAIL();
}