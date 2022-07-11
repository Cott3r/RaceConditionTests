cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)

project(RaceConditionTests)

add_subdirectory(testing)
add_subdirectory(libraries)

add_executable(RaceConditionTests main.cpp)
target_link_libraries(RaceConditionTests RaceCondition_libc)

find_package( Threads )
target_link_libraries( RaceConditionTests ${CMAKE_THREAD_LIBS_INIT} )
