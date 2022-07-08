FILE(GLOB RaceCondition_libcpp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

target_sources(RaceCondition_libc
        PRIVATE
        ${RaceCondition_libcpp_SOURCES})