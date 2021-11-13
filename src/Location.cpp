#include "Location.hpp"

#include <filesystem>

namespace chw
{
    Location::Location(const std::filesystem::path& file_path, std::uint64_t line_number,
                       std::uint64_t column) noexcept
        : m_FilePath{file_path}
        , m_LineNumber{line_number}
        , m_Column{column}
    {}

    const std::filesystem::path& Location::GetFile() const noexcept
    {
        return m_FilePath;
    }

    std::string Location::GetFilePath() const noexcept
    {
        return m_FilePath.string();
    }

    std::string Location::GetFileName() const noexcept
    {
        return m_FilePath.filename().string();
    }

    std::string Location::GetFileStem() const noexcept
    {
        return m_FilePath.stem().string();
    }

    std::string Location::GetFileExtension() const noexcept
    {
        return m_FilePath.extension().string();
    }

    std::uint64_t Location::GetLineNumber() const noexcept
    {
        return m_LineNumber;
    }

    std::uint64_t Location::GetColumn() const noexcept
    {
        return m_Column;
    }
} // namespace chw
