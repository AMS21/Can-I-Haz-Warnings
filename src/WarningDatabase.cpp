#include "WarningDatabase.hpp"

namespace chw
{
    bool WarningDatabase::AddWarning(const Warning& warning)
    {
        m_Warnings.emplace_back(warning);

        return true;
    }
} // namespace chw
