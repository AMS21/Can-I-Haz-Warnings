#pragma once

#include <string_view>

namespace chw
{
    class WarningDatabase;

    // Exptects normal output format
    bool ParseCppCheckOutput(std::string_view output, WarningDatabase& database);
} // namespace chw
