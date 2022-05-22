#include <boost/ut.hpp>
#include <pqrs/cf/array.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "make_empty_cf_array"_test = [] {
    auto array = pqrs::cf::make_empty_cf_array();
    expect(array);
    expect(CFArrayGetCount(*array) == 0);
  };

  "make_cf_mutable_array, get_cf_array_value"_test = [] {
    {
      auto array = pqrs::cf::make_cf_mutable_array();
      expect(array);
      expect(CFGetRetainCount(*array) == 1);
      expect(CFArrayGetCount(*array) == 0);

      auto string1 = CFSTR("string1");
      auto string2 = CFSTR("string2");

      CFArrayAppendValue(*array, string1);
      CFArrayAppendValue(*array, string2);

      expect(CFArrayGetCount(*array) == 2);

      auto value1 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 0);
      expect(value1);
      expect(CFEqual(string1, value1));

      auto value2 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 1);
      expect(value2);
      expect(CFEqual(string2, value2));

      auto value3 = pqrs::cf::get_cf_array_value<CFStringRef>(*array, 2);
      expect(!value3);
    }
  };
}
