#pragma once

#include "Location.hpp"
#include <string>

namespace chw
{
    class Warning
    {
    public:
        Warning(const Location& location, const std::string& severity, const std::string& id,
                const std::string& message);

        [[nodiscard]] const Location& GetLocation() const noexcept;

        [[nodiscard]] const std::string& GetSeverity() const noexcept;

        [[nodiscard]] const std::string& GetId() const noexcept;

        [[nodiscard]] const std::string& GetMessage() const noexcept;

    private:
        Location    m_Location;
        std::string m_Severity;
        std::string m_Id;
        std::string m_Message;
    };
} // namespace chw
