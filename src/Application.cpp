#include "Application.hpp"

#include "Location.hpp"
#include "Parser/CppCheck.hpp"
#include "Warning.hpp"
#include "WarningDatabase.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

namespace chw
{
    [[nodiscard]] std::optional<std::string> ReadFileContent(
            const std::string_view& file_path) noexcept
    {
        std::FILE* file = fopen(file_path.data(), "r");

        if (file != nullptr)
        {
            std::fseek(file, 0, SEEK_END);

            long size = std::ftell(file);
            if (size > std::string().max_size())
            {
                return {};
            }

            if (size != -1L)
            {
                std::rewind(file);

                // Create empty string of desired size
                std::string str(size, '\0');

                // Read data
                std::fread(&str[0], sizeof(std::string::value_type), size, file);

                std::fclose(file);

                return std::move(str);
            }
            else
            {
                std::fclose(file);
                return {};
            }
        }

        return {};
    }

    void PrintDatabase(WarningDatabase& database) noexcept
    {
        for (const Warning& warn : database.m_Warnings)
        {
            const Location& loc = warn.GetLocation();
            // Location
            std::cout << loc.GetFileName() << ":" << loc.GetLineNumber() << ":" << loc.GetColumn();
            // Warnings
            std::cout << " (" << warn.GetSeverity() << "): " << warn.GetMessage() << " ["
                      << warn.GetId() << "]\n";
        }
    }

    int Application::Run(int argc, char* argv[])
    {
        if (argc < 2)
        {
            // TODO: print usage

            return 0;
        }

        // Treat first input as the file we want to check
        const char* file_name = argv[1];

        auto file_content_opt = ReadFileContent(file_name);
        if (!file_content_opt)
        {
            std::cerr << "Failed to open file \"" << file_name << "\"\n";
            return -1;
        }

        std::string file_content = file_content_opt.value();

        // Create warning database
        WarningDatabase database;

        ParseCppCheckOutput(file_content, database);

        PrintDatabase(database);

        return 0;
    }
} // namespace chw
