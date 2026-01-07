#ifndef NT_MATH_KMATH_FLOAT128_ABS_HPP__
#define NT_MATH_KMATH_FLOAT128_ABS_HPP__

#include "../float128_impl.h"
#include "../utils/always_inline_macro.h"

// constexpr math functions
namespace nt::math::kmath{

NT_ALWAYS_INLINE constexpr float128_t abs(float128_t arg) noexcept {
    return float128_t(arg.get_bits().positive_sign_bit());
}



}

#endif
