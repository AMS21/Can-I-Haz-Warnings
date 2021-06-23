#include "Warning.hpp"

namespace chw
{
    Warning::Warning(Location location, Level level, const std::string& id,
                     const std::string& message)
        : m_Location(location)
        , m_Level(level)
        , m_Id(id)
        , m_Message(message)
    {}

    const Location& Warning::GetLocation() const noexcept
    {
        return m_Location;
    }

    Level Warning::GetLevel() const noexcept
    {
        return m_Level;
    }

    const std::string& Warning::GetId() const noexcept
    {
        return m_Id;
    }

    const std::string& Warning::GetMessage() const noexcept
    {
        return m_Message;
    }
} // namespace chw