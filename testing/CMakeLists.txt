# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# adding the Google_Tests_run target
set(SOURCE_FILES
        userTest.cpp
        )


add_executable(Google_tests ${SOURCE_FILES})

# linking Google_Tests_run with the libraries which will be tested
target_link_libraries(Google_tests RaceCondition_libc)
#target_link_libraries(Google_tests gtest gmock)
target_link_libraries(Google_tests gtest gmock gtest_main)
