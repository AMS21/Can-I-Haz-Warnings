#include <catch2/catch_test_macros.hpp>

#include "Parser/CppCheck.hpp"
#include "WarningDatabase.hpp"

static constexpr const char* OneError{R"(Checking samples/OutOfBounds/IndexOutOfBounds.c ...
samples/OutOfBounds/IndexOutOfBounds.c:7:10: error: Array 'a[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
        a[i] = 0;
         ^)"};

TEST_CASE("Parser CppCheck")
{
    chw::WarningDatabase database;

    SECTION("Empty")
    {
        CHECK(chw::ParseCppCheckOutput("", database));

        CHECK(database.m_Warnings.empty());
    }

    SECTION("One Error")
    {
        CHECK(chw::ParseCppCheckOutput(OneError, database));

        REQUIRE(database.m_Warnings.size() == 1);

        chw::Warning& warning = database.m_Warnings.at(0);

        CHECK(warning.GetLocation().GetFileName() == "samples/OutOfBounds/IndexOutOfBounds.c");
        CHECK(warning.GetLocation().GetLineNumber() == 7);
        CHECK(warning.GetLocation().GetColumn() == 10);
        CHECK(warning.GetLevel() == chw::Level::Error);
        CHECK(warning.GetId() == "arrayIndexOutOfBounds");
        CHECK(warning.GetMessage() == "Array 'a[2]' accessed at index 2, which is out of bounds.");

        database.m_Warnings.clear();
    }
}
