#include <iostream>
#include <pqrs/cf/array.hpp>
#include <pqrs/cf/string.hpp>

int main(void) {
  if (auto array_ptr = pqrs::cf::make_cf_mutable_array(0)) {
    CFArrayAppendValue(*array_ptr, CFSTR("hello"));
    CFArrayAppendValue(*array_ptr, CFSTR("world"));

    if (auto cf_string = pqrs::cf::get_cf_array_value<CFStringRef>(*array_ptr, 0)) {
      if (auto string = pqrs::cf::make_string(cf_string)) {
        std::cout << "string: " << *string << std::endl;
      }
    }

    if (auto cf_string = pqrs::cf::get_cf_array_value<CFStringRef>(*array_ptr, 1)) {
      if (auto string = pqrs::cf::make_string(cf_string)) {
        std::cout << "string: " << *string << std::endl;
      }
    }
  }

  return 0;
}
