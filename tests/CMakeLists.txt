project("Can-I-Haz-Warnings-Unittests" LANGUAGES CXX)

file(GLOB TEST_HEADERS "")
file(GLOB TEST_SOURCES "src/Parser/CppCheck.test.cpp" "src/Application.test.cpp" "src/Location.test.cpp" "src/Warning.test.cpp" "src/WarningDatabase.test.cpp")

add_executable(${PROJECT_NAME} ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Can-I-Haz-Warnings-lib Catch2::Catch2WithMain)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_test(NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
