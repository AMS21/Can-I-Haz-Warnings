#ifndef INCG_CHW_LOCATION_HPP
#define INCG_CHW_LOCATION_HPP

#include <cstdint>
#include <string>

namespace chw
{
    class Location
    {
    public:
        Location(const std::string& file_name, std::uint64_t line_number,
                 std::uint64_t column) noexcept;

        const std::string& GetFileName() const noexcept;
        std::uint64_t      GetLineNumber() const noexcept;
        std::uint64_t      GetColumn() const noexcept;

    private:
        std::uint64_t m_LineNumber;
        std::uint64_t m_Column;
        std::string   m_FileName;
    };
} // namespace chw

#endif // INCG_CHW_LOCATION_HPP
