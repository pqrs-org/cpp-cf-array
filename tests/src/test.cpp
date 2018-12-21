#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/cf/array.hpp>

TEST_CASE("make_empty_cf_array") {
  auto array = pqrs::cf::make_empty_cf_array();
  REQUIRE(array);
  REQUIRE(CFArrayGetCount(*array) == 0);
}

TEST_CASE("make_cf_mutable_array, get_cf_array_value") {
  {
    auto array = pqrs::cf::make_cf_mutable_array();
    REQUIRE(array);
    REQUIRE(CFArrayGetCount(*array) == 0);

    auto string1 = CFSTR("string1");
    auto string2 = CFSTR("string2");

    CFArrayAppendValue(*array, string1);
    CFArrayAppendValue(*array, string2);

    REQUIRE(CFArrayGetCount(*array) == 2);

    auto value1 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 0);
    REQUIRE(value1);
    REQUIRE(CFEqual(string1, value1));

    auto value2 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 1);
    REQUIRE(value2);
    REQUIRE(CFEqual(string2, value2));

    auto value3 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 2);
    REQUIRE(!value3);
  }
}
