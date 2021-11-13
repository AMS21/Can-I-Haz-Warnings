#include <catch2/catch_test_macros.hpp>

#include <Application.hpp>
#include <iostream>
#include <sstream>

static constexpr const char* expected_cppcheck_output{
        R"(MallocLeak.c:6:1 (error): Memory leak: ptr [memleak]
NewLeak.cpp:6:1 (error): Memory leak: i [memleak]
IndexOutOfBounds.c:7:10 (error): Array 'a[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
strcpy.c:6:12 (error): Buffer is accessed out of bounds: x [bufferAccessOutOfBounds]
FileHandle.c:11:5 (error): Resource leak: handle [resourceLeak]
MissingClosingBracket.c:2:1 (error): Unmatched '{'. Configuration: ''. [syntaxError]
)"};

TEST_CASE("Livetest Cppcheck")
{
    std::ostringstream out;
    auto*              original = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    chw::Application app;

    char* argv[2] = {"", DATA_DIRECTORY "/CppCheck.output"};

    app.Run(2, argv);

    std::cout.rdbuf(original);

    CHECK(out.str() == expected_cppcheck_output);
}
