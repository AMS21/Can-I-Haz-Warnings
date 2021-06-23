cmake_minimum_required(VERSION 3.10.2)

project("Can-I-Haz-Warnings" LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add external
add_subdirectory(external)

# Add tools
file(GLOB CHW_HEADERS "include/Parser/CppCheck.hpp" "include/Application.hpp" "include/Location.hpp" "include/Warning.hpp" "include/WarningDatabase.hpp")
FILE(GLOB CHW_SOURCES "src/Parser/CppCheck.cpp" "src/Application.cpp" "src/Location.cpp" "src/Warning.cpp" "src/WarningDatabase.cpp")

add_library(${PROJECT_NAME}-lib STATIC ${CHW_SOURCES} ${CHW_HEADERS})
target_include_directories(${PROJECT_NAME}-lib PUBLIC "include")

add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)

set_property(TARGET ${PROJECT_NAME}-lib PROPERTY CXX_STANDARD 17)

# Tests
include(CTest)
add_subdirectory(tests)
