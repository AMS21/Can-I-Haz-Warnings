#include "Location.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Location::Location")
{
    chw::Location loc("file_name", 42, 21);

    CHECK(loc.GetFileName() == "file_name");
    CHECK(loc.GetLineNumber() == 42);
    CHECK(loc.GetColumn() == 21);
}
