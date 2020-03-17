#pragma once

#include <numeric>
#include <type_traits>

/* https://doc.rust-lang.org/1.30.0/std/primitive.i8.html
 * https://doc.rust-lang.org/1.30.0/std/primitive.u8.html
 *
 * */

template<typename T>
concept integral_type = std::is_integral_v<T>;

template<integral_type T>
class integral {
public:
    constexpr integral() = default;
    constexpr integral(const T t) noexcept
        : value_(t) { }

    static constexpr T get_max() noexcept { return std::numeric_limits<T>().max(); }
    static constexpr T get_min() noexcept { return std::numeric_limits<T>().min(); }

    constexpr operator T() const noexcept { return value_; }

private:
    T value_{ };
};

using i8 = integral<char>;
using u8 = integral<unsigned char>;

using i16 = integral<short>;
using u16 = integral<unsigned short>;

using i32 = integral<int>;
using u32 = integral<unsigned int>;
