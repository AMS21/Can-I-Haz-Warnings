project("Can-I-Haz-Warnings-Livetests" LANGUAGES CXX)

# Clang-tidy
find_program(
  CLANG_TIDY_EXECUTABLE
  NAMES clang-tidy
        clang-tidy-14
        clang-tidy-13
        clang-tidy-12
        clang-tidy-11
        clang-tidy-10
        clang-tidy-9
        clang-tidy-8
        clang-tidy-7
        clang-tidy-6.0
        clang-tidy-5.0
  DOC "clang-tidy executable")
mark_as_advanced(CLANG_TIDY_EXECUTABLE)

if(CLANG_TIDY_EXECUTABLE)
    execute_process(
        COMMAND ${CLANG_TIDY_EXECUTABLE} --version
        OUTPUT_VARIABLE CLANG_TIDY_VERSION
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Sample: "LLVM (http://llvm.org/): LLVM version 12.0.1 Optimized build. Default target: x86_64-pc-linux-gnu Host CPU: skylake"
    string(REGEX MATCH "LLVM version ([0-9]+)\.([0-9]+)\.([0-9]+)" CLANG_TIDY_VERSION ${CLANG_TIDY_VERSION})
    string(REPLACE "LLVM version " "" CLANG_TIDY_VERSION "${CLANG_TIDY_VERSION}")
    string(REPLACE "." ";" CLANG_TIDY_VERSION_COMPONENTS "${CLANG_TIDY_VERSION}")
    list(LENGTH CLANG_TIDY_VERSION_COMPONENTS CLANG_TIDY_VERSION_COMPONENTS_COUNT)

    # Major version
    if (CLANG_TIDY_VERSION_COMPONENTS_COUNT GREATER 0)
        list(GET CLANG_TIDY_VERSION_COMPONENTS 0 CLANG_TIDY_VERSION_MAJOR)
    else()
        set(CLANG_TIDY_VERSION_MAJOR 0)
    endif()

    # Minor version
    if (CLANG_TIDY_VERSION_COMPONENTS_COUNT GREATER 1)
        list(GET CLANG_TIDY_VERSION_COMPONENTS 1 CLANG_TIDY_VERSION_MINOR)
    else()
        set(CLANG_TIDY_VERSION_MINOR 0)
    endif()

    # Patch version
    if (CLANG_TIDY_VERSION_COMPONENTS_COUNT GREATER 2)
        list(GET CLANG_TIDY_VERSION_COMPONENTS 2 CLANG_TIDY_VERSION_PATCH)
    else()
        set(CLANG_TIDY_VERSION_PATCH 0)
    endif()

    message(STATUS "Found clang-tidy version ${CLANG_TIDY_VERSION}")

    add_custom_target(
        ClangTidyLiveOutput
        COMMENT "Generating clang-tidy live output"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/samples"
        COMMAND ${CLANG_TIDY_EXECUTABLE} -header-filter=.* */* > "${CMAKE_CURRENT_BINARY_DIR}/ClangTidy.output" 2>&1 || true)
else()
    message(STATUS "Did not find clang-tidy")
endif()

# CppCheck
find_program(
  CPPCHECK_EXECUTABLE
  NAMES cppcheck
  DOC "cppcheck executable")
mark_as_advanced(CPPCHECK_EXECUTABLE)

if(CPPCHECK_EXECUTABLE)
    execute_process(
        COMMAND ${CPPCHECK_EXECUTABLE} --version
        OUTPUT_VARIABLE CPPCHECK_VERSION
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Sample: "Cppcheck 2.6"
    string(REPLACE "Cppcheck " "" CPPCHECK_VERSION "${CPPCHECK_VERSION}")
    string(REPLACE "." ";" CPPCHECK_VERSION_COMPONENTS "${CPPCHECK_VERSION}")
    list(LENGTH CPPCHECK_VERSION_COMPONENTS CPPCHECK_VERSION_COMPONENTS_COUNT)

    # Major version
    if (CPPCHECK_VERSION_COMPONENTS_COUNT GREATER 0)
        list(GET CPPCHECK_VERSION_COMPONENTS 0 CPPCHECK_VERSION_MAJOR)
    else()
        set(CPPCHECK_VERSION_MAJOR 0)
    endif()

    # Minor version
    if (CPPCHECK_VERSION_COMPONENTS_COUNT GREATER 1)
        list(GET CPPCHECK_VERSION_COMPONENTS 1 CPPCHECK_VERSION_MINOR)
    else()
        set(CPPCHECK_VERSION_MINOR 0)
    endif()

    # Patch version
    if (CPPCHECK_VERSION_COMPONENTS_COUNT GREATER 2)
        list(GET CPPCHECK_VERSION_COMPONENTS 2 CPPCHECK_VERSION_PATCH)
    else()
        set(CPPCHECK_VERSION_PATCH 0)
    endif()

    message(STATUS "Found Cppcheck version ${CPPCHECK_VERSION}")

    add_custom_target(
        CppCheckLiveOutput
        COMMENT "Generating CppCheck live output"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/samples"
        COMMAND ${CPPCHECK_EXECUTABLE} . > "${CMAKE_CURRENT_BINARY_DIR}/CppCheck.output" 2>&1)
else()
    message(STATUS "Did not find Cppcheck")
endif()

# Tests
file(GLOB TEST_HEADERS "")
file(GLOB TEST_SOURCES "src/ClangTidy.live.test.cpp" "src/CppCheck.live.test.cpp")

add_executable(${PROJECT_NAME} ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Can-I-Haz-Warnings-lib Catch2::Catch2WithMain)
target_compile_definitions(${PROJECT_NAME} PRIVATE "DATA_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"")

add_dependencies(${PROJECT_NAME} ClangTidyLiveOutput CppCheckLiveOutput)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_test(NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
