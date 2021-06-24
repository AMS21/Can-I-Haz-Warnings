#include "Warning.hpp"

namespace chw
{
    Warning::Warning(const Location& location, const std::string& severity, const std::string& id,
                     const std::string& message)
        : m_Location(location)
        , m_Severity(severity)
        , m_Id(id)
        , m_Message(message)
    {}

    const Location& Warning::GetLocation() const noexcept
    {
        return m_Location;
    }

    const std::string& Warning::GetSeverity() const noexcept
    {
        return m_Severity;
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