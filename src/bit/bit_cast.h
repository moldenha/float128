#ifndef NT_BIT_CAST_H__
#define NT_BIT_CAST_H__

#include "../utils/cp20_macro.h"
#include <bit>
#include <cstring>

namespace nt{

#ifdef NT_CPP20_AVAILABLE_
template<typename To, typename From>
inline constexpr To bit_cast(const From& src) noexcept {
    return std::bit_cast<To>(src);
}
#else
template<class To, class From_>
inline std::enable_if_t<
    sizeof(To) == sizeof(From_) &&
    std::is_trivially_copyable_v<From_> &&
    std::is_trivially_copyable_v<To>,
    To>
// constexpr support needs compiler magic
bit_cast(const From_& src) noexcept
{
    using From = std::decay_t<From_>;
    // the union is trivially constructible
    // Therefore From_ and To don't need to be
    union u__{u__(){}; char bits[sizeof(From)]; std::decay_t<To> dst;} u;
    std::memcpy(&u.dst, &src, sizeof(From));
    return u.dst;
}

#endif

}

#endif
