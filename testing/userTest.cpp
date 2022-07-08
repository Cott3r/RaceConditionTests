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


TEST(SUIT1, Test1)
{
  (new Worker())->doWork();
}

TEST(SUIT1, Test2)
{
  FAIL();
}

//int main(int argc, char **argv)
//{
//  ::testing::InitGoogleTest(&argc, argv);
//  bool result = RUN_ALL_TESTS();
//  printf("Result: %d  %s", result, result == 0 ? "All tests are successful\n" : "Some tests have failed\n");
//
//  return result;
//}