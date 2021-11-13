#include <Application.hpp>
#include <WarningDatabase.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <vector>

// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t* data, std::size_t size)
{
    // Reject invalid inputs
    if (size <= 0)
    {
        return 0;
    }

    if (*(data + size - 1) != '\0')
    {
        return 0;
    }

    chw::Application app;

    int                      argc = 1;
    std::vector<const char*> argv{reinterpret_cast<const char*>(data)};
    std::size_t              count = size;
    for (; count > 0; --count, ++data)
    {
        if (*data == '\0' && count > 1)
        {
            argv.push_back(reinterpret_cast<const char*>(data) + 1);
            ++argc;
        }
    }

    // Disable standard output
    std::cout.setstate(std::ios_base::badbit);
    std::cerr.setstate(std::ios_base::badbit);

    app.Run(argc, const_cast<char**>(argv.data()));

    // Restore standard output
    std::cout.clear();
    std::cerr.clear();

    return 0;
}
