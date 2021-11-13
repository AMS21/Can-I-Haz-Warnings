#include <catch2/catch_test_macros.hpp>

#include <Application.hpp>
#include <iostream>
#include <sstream>

static constexpr const char* expected_clang_tidy_output{
        R"(MallocLeak.c:1:10 (warning): inclusion of deprecated C++ header 'stdlib.h'; consider using 'cstdlib' instead [hicpp-deprecated-headers,modernize-deprecated-headers]
MallocLeak.c:5:5 (warning): initializing non-owner 'void *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]
MallocLeak.c:5:11 (warning): Value stored to 'ptr' during its initialization is never read [clang-analyzer-deadcode.DeadStores]
MallocLeak.c:5:17 (warning): do not manage memory manually; consider a container or a smart pointer [cppcoreguidelines-no-malloc,hicpp-no-malloc]
MallocLeak.c:6:1 (warning): Potential leak of memory pointed to by 'ptr' [clang-analyzer-unix.Malloc]
NewLeak.cpp:5:5 (warning): initializing non-owner 'int *' with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]
NewLeak.cpp:5:10 (warning): Value stored to 'i' during its initialization is never read [clang-analyzer-deadcode.DeadStores]
NewLeak.cpp:6:1 (warning): Potential leak of memory pointed to by 'i' [clang-analyzer-cplusplus.NewDeleteLeaks]
IndexOutOfBounds.c:3:5 (warning): do not declare C-style arrays, use std::array<> instead [cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays]
IndexOutOfBounds.c:7:9 (warning): do not use array subscript when the index is not an integer constant expression; use gsl::at() instead [cppcoreguidelines-pro-bounds-constant-array-index]
strcpy.c:1:10 (warning): inclusion of deprecated C++ header 'string.h'; consider using 'cstring' instead [hicpp-deprecated-headers,modernize-deprecated-headers]
strcpy.c:5:5 (warning): do not declare C-style arrays, use std::array<> instead [cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays]
strcpy.c:6:5 (warning): Call to function 'strcpy' is insecure as it does not provide bounding of the memory buffer. Replace unbounded copy functions with analogous functions that support length arguments such as 'strlcpy'. CWE-119 [clang-analyzer-security.insecureAPI.strcpy]
strcpy.c:6:12 (warning): do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast instead [cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay]
FileHandle.c:1:10 (warning): inclusion of deprecated C++ header 'stdio.h'; consider using 'cstdio' instead [hicpp-deprecated-headers,modernize-deprecated-headers]
FileHandle.c:5:5 (warning): initializing non-owner 'FILE *' (aka '_IO_FILE *') with a newly created 'gsl::owner<>' [cppcoreguidelines-owning-memory]
FileHandle.c:6:10 (warning): implicit conversion 'FILE *' (aka '_IO_FILE *') -> bool [readability-implicit-bool-conversion]
ModerinzeUseUsing.c:1:1 (warning): use 'using' instead of 'typedef' [modernize-use-using]
ReservedIdentifer.c:3:9 (warning): declaration uses identifier '__reserved_name', which is a reserved identifier [bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp]
MissingClosingBracket.c:2:2 (error): expected '}' [clang-diagnostic-error]
MissingIncludeFile.c:1:10 (error): 'ThisFileDoesNotExist.h' file not found [clang-diagnostic-error]
)"};

TEST_CASE("Livetest Clang-Tidy")
{
    std::ostringstream out;
    auto*              original = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    chw::Application app;

    char* argv[2] = {"", DATA_DIRECTORY "/ClangTidy.output"};

    app.Run(2, argv);

    std::cout.rdbuf(original);

    CHECK(out.str() == expected_clang_tidy_output);
}
