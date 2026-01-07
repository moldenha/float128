#ifndef NT_MATH_KMATH_FLOAT128_NAN_HPP__
#define NT_MATH_KMATH_FLOAT128_NAN_HPP__

#include "../float128_impl.h"
#include "../utils/always_inline_macro.h"

// constexpr math functions
namespace nt::math::kmath{

inline constexpr bool isnan(float128_t arg) noexcept {
    return arg.get_bits().is_nan();
}



}

#endif
