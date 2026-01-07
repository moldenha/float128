#ifndef NT_MATH_KMATH_FLOAT128_INF_HPP__
#define NT_MATH_KMATH_FLOAT128_INF_HPP__

#include "../float128_impl.h"
#include "../utils/always_inline_macro.h"

// constexpr math functions
namespace nt::math::kmath{

inline constexpr float128_t generate_f128_inf() noexcept {
    return float128_t::make_inf();
}

inline constexpr float128_t generate_neg_f128_inf() noexcept {
    return float128_t::make_inf(true);
}

inline constexpr bool isinf(float128_t arg) noexcept {
    return arg.get_bits().is_inf();
}



}

#endif
