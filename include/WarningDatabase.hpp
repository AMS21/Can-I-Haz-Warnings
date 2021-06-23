#ifndef INCG_WARNING_DATABASE_HPP
#define INCG_WARNING_DATABASE_HPP

#include "Warning.hpp"
#include <vector>

namespace chw
{
    class WarningDatabase
    {
    public:
        WarningDatabase() = default;

        bool AddWarning(const Warning& warning);

    public:
        std::vector<Warning> m_Warnings;
    };
} // namespace chw

#endif // INCG_WARNING_DATABASE_HPP
