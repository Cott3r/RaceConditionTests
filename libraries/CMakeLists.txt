add_library(RaceCondition_libc)

target_include_directories(RaceCondition_libc
        PUBLIC
        header
        )



add_subdirectory(src)