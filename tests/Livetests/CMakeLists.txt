project("Can-I-Haz-Warnings-Livetests" LANGUAGES CXX)

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
file(GLOB TEST_SOURCES "src/CppCheck.live.test.cpp")

add_executable(${PROJECT_NAME} ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Can-I-Haz-Warnings-lib Catch2::Catch2WithMain)
target_compile_definitions(${PROJECT_NAME} PRIVATE "DATA_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"")

add_dependencies(${PROJECT_NAME} CppCheckLiveOutput)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_test(NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
