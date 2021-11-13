#include "Parser/CppCheck.hpp"

#include "WarningDatabase.hpp"
#include <filesystem>
#include <iostream>
#include <regex>

namespace chw
{
    bool ParseCppCheckOutput(std::string_view output, WarningDatabase& database)
    {
        // https://regex101.com/r/tC2Umz/1
        static constexpr const char* regular_expression =
                R"((.+?):(\d+):(\d+): (.+?): (.+?) \[(.*?)\])";

        std::regex  regex(regular_expression);
        std::string str = std::string(output);

        for (auto it = std::sregex_iterator(str.begin(), str.end(), regex);
             it != std::sregex_iterator(); ++it)
        {
            std::smatch match = *it;

            // Extract elements
            std::string file_name =
                    std::filesystem::absolute(std::filesystem::path(match[1])).string();
            int line_number{0};
            int column_number{0};
            try
            {
                line_number   = std::stoi(match[2]);
                column_number = std::stoi(match[3]);
            }
            catch (std::exception& e)
            {
                return false;
            }
            std::string severity = match[4];
            std::string message  = match[5];
            std::string id       = match[6];

            // Construct warning
            Location location = Location(file_name, line_number, column_number);

            Warning warning = Warning(location, severity, id, message);

            // Add warning to database
            database.AddWarning(warning);
        }

        return true;
    }
} // namespace chw
