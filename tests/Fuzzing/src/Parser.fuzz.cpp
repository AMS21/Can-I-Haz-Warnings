#include <Parser/CppCheck.hpp>
#include <WarningDatabase.hpp>
#include <cstddef>
#include <cstdint>
#include <string_view>

// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t* data, std::size_t size)
{
    chw::WarningDatabase db;

    std::string_view source = std::string_view(reinterpret_cast<const char*>(data), size);

    // Parse it
    chw::ParseCppCheckOutput(source, db);

    return 0;
}
