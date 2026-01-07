#ifndef NT_TYPES_FLOAT128_ENSURE_H__
#define NT_TYPES_FLOAT128_ENSURE_H__

// this holds the float128_t class
#include "src/float128_impl.h"
// #ifndef NT_FLOAT128_HEADER_ONLY__
// #define NT_FLOAT128_HEADER_ONLY__
// #endif
// this holds the ability to go from strings and do something like:
// constexpr float128_t f = 1.235867284617643_f128;
#include "src/from_string.hpp"
// this holds the ability to go to a string:
// std::string str = nt::float128_func::to_string(f);
#include "src/to_string.hpp"
// this holds the ability to print a float128_t:
// std::cout << f << std::endl;
#include "src/print.hpp"
// this holds numeric limits, make_unsigned, is_floating_point
#include "src/type_traits.h"

// math
#include "src/math.h"
#include "src/kmath.h"

#endif
