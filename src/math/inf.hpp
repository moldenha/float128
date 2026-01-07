#ifndef NT_MATH_FLOAT128_INF_HPP__
#define NT_MATH_FLOAT128_INF_HPP__

#include "../float128_impl.h"
#include "../utils/always_inline_macro.h"
#include "../kmath/abs.hpp"

// constexpr math functions
namespace nt::math{

inline bool constexpr isinf(const float128_t& x) noexcept {
    return x.get_bits().is_inf();
}

}

#endif
