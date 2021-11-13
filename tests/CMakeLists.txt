project("Can-I-Haz-Warnings-Tests" LANGUAGES CXX)

add_subdirectory(Unittests)

if (${CHW_BUILD_LIVETESTS})
    add_subdirectory(Livetests)
endif()

if (${CHW_BUILD_FUZZER})
    add_subdirectory(Fuzzing)
endif()
