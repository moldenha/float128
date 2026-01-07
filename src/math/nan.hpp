#ifndef NT_MATH_FLOAT128_NAN_HPP__
#define NT_MATH_FLOAT128_NAN_HPP__

#include "../float128_impl.h"
#include "../utils/always_inline_macro.h"
#include "../kmath/nan.hpp"

// constexpr math functions
namespace nt::math{

inline bool constexpr isnan(const float128_t& x) noexcept {
    return kmath::isnan(x);
}

}

#endif
