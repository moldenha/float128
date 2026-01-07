// the only macro that really matters for if certain functions can be constexpr
// is if std::bit_cast can be constexpr 
#include <bit>

#if defined(__cpp_lib_bit_cast)
    #define NT_CPP20_AVAILABLE_
    #define NT_CPP20_CONSTEXPR constexpr
#else
    #define NT_CPP20_CONSTEXPR
#endif
    
    
