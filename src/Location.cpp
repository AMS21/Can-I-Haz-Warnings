#include "Location.hpp"

namespace chw
{
    Location::Location(const std::string& file_name, std::uint64_t line_number,
                       std::uint64_t column) noexcept
        : m_FileName{file_name}
        , m_LineNumber{line_number}
        , m_Column{column}
    {}

    const std::string& Location::GetFileName() const noexcept
    {
        return m_FileName;
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
