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
#include "ThreadHelper.h"
#include "Assignment.h"
#include "Assignment1.h"

using namespace std;

// The fixture for testing class FactoryTest.
class FactoryTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
//    Factory* factory;

    FactoryTest() {
      // You can do set-up work for each test here.
//      factory = new Factory();
    }

    ~FactoryTest() override {
      // You can do clean-up work that doesn't throw exceptions here.
//      delete factory;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
      // Code here will be called immediately after the constructor (right
      // before each test).
      ThreadHelper::SetUp();
    }

    void TearDown() override {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite


    // Run Tests
    void runTest(Assignment* assignment)
    {
      if(!ThreadHelper::runTest(assignment))
      {
        string fail_message = assignment->name() + " Test Failed";
        delete assignment;

        FAIL() << fail_message << endl;
      }

      delete assignment;
    }
};


TEST_F(FactoryTest, Assignment1)
{
  FactoryTest::runTest(new Assignment1(10));
}

TEST_F(FactoryTest, Assignment1_100)
{
  FactoryTest::runTest(new Assignment1(100));
}

TEST_F(FactoryTest, Assignment1_1000)
{
  FactoryTest::runTest(new Assignment1(1000));
}