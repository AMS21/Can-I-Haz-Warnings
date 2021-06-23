#ifndef INCG_CHW_WARNING_HPP
#define INCG_CHW_WARNING_HPP

#include "Location.hpp"
#include <string>

namespace chw
{
    enum class Level
    {
        Info,
        Warning,
        Error,
    };

    class Warning
    {
    public:
        Warning(Location location, Level level, const std::string& id, const std::string& message);

        const Location& GetLocation() const noexcept;

        Level GetLevel() const noexcept;

        const std::string& GetId() const noexcept;

        const std::string& GetMessage() const noexcept;

    private:
        Location    m_Location;
        Level       m_Level;
        std::string m_Id;
        std::string m_Message;
    };
} // namespace chw

#endif // INCG_CHW_WARNING_HPP
