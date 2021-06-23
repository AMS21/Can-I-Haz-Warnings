#ifndef INCG_CHW_PARSER_CPPCHECK_HPP
#define INCG_CHW_PARSER_CPPCHECK_HPP

#include <string_view>

namespace chw
{
    class WarningDatabase;

    // Exptects normal output format
    bool ParseCppCheckOutput(std::string_view output, WarningDatabase& database);
} // namespace chw

#endif // INCG_CHW_PARSER_CPPCHECK_HPP
