#pragma once

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
