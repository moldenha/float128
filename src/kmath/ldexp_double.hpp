#ifndef NT_MATH_KMATH_FLOAT128_LDEXP_DOUBLE_HPP__
#define NT_MATH_KMATH_FLOAT128_LDEXP_DOUBLE_HPP__
#include <cmath>

// constexpr math functions
namespace nt::math::kmath{

inline constexpr double ldexpd(double arg, int exp) noexcept {
    constexpr double two = 2;
    while(exp > 0)
    {
        arg *= two;
        --exp;
    }
    while(exp < 0)
    {
        arg /= two;
        ++exp;
    }

    return arg;
}


}

#endif
