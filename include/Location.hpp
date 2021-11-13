#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

namespace chw
{
    class Location
    {
    public:
        Location(const std::filesystem::path& file_path, std::uint64_t line_number,
                 std::uint64_t column) noexcept;

        [[nodiscard]] const std::filesystem::path& GetFile() const noexcept;

        [[nodiscard]] std::string GetFilePath() const noexcept;

        [[nodiscard]] std::string GetFileName() const noexcept;

        [[nodiscard]] std::string GetFileStem() const noexcept;

        [[nodiscard]] std::string GetFileExtension() const noexcept;

        [[nodiscard]] std::uint64_t GetLineNumber() const noexcept;

        [[nodiscard]] std::uint64_t GetColumn() const noexcept;

    private:
        std::uint64_t         m_LineNumber;
        std::uint64_t         m_Column;
        std::filesystem::path m_FilePath;
    };
} // namespace chw
