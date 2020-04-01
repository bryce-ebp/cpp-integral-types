#pragma once

#include <numeric>
#include <type_traits>
#include <cctype>
#define __cpp_lib_bitops
#include <bit>

/* https://doc.rust-lang.org/1.30.0/std/primitive.i8.html
 * https://doc.rust-lang.org/1.30.0/std/primitive.u8.html
 *
 * */


template<typename T>
concept integral_type = std::is_integral_v<T>;

template<integral_type T>
class integral {
public:
    constexpr integral() noexcept = default;
    constexpr integral(const T t) noexcept
        : value_(t) { }

    constexpr operator T() const noexcept { return value_; }

    static constexpr T get_max() noexcept { return limit_.max(); }
    static constexpr T get_min() noexcept { return limit_.min(); }



    [[nodiscard]] constexpr unsigned short count_ones() const noexcept {
        return std::popcount(value_);
    }

    [[nodiscard]] constexpr unsigned short count_zeros() const noexcept {
        return std::bit_length(value_) - count_ones();
    }

    constexpr T leading_zeros() const noexcept {
        return std::countl_zero(value_);
    }

    constexpr T trailing_zeros() const noexcept {
        return std::countr_zero(value_);
    }

    [[nodiscard]] constexpr bool is_pow_two() const noexcept {
        return value_ && !(value_ & (value_ - 1));
    }

    [[nodiscard]] constexpr bool is_ascii() const noexcept {
        return value_ < 256;
    }

    [[nodiscard]] constexpr bool is_ascii_type() const noexcept {
        return get_max() < 256;
    }

    [[nodiscard]] constexpr bool is_ascii_lowercase() const noexcept {
        return std::islower(value_);
    }

    [[nodiscard]] constexpr bool is_ascii_uppercase() const noexcept {
        return std::isupper(value_);
    }

    // Good post related to pow: https://www.rookieslab.com/posts/fast-power-algorithm-exponentiation-by-squaring-cpp-python-implementation
    [[nodiscard]] constexpr long long pow(long long exp) const noexcept {
        auto ret{ 1 };
        auto base{ value_ };

        while (exp > 0) {
            if (exp & 1) {
                // Magic number explanation: https://codeaccepted.wordpress.com/2014/02/15/output-the-answer-modulo-109-7/
                ret = (ret * base) % 1000000007;
            }

            base = (base * base) % 1000000007;
            exp >>= 1;
        }

        return ret;
    }

    [[nodiscard]] constexpr unsigned short next_pow_two() const noexcept {
        return std::ispow2(value_);
    }


private:
    T value_{ };
    static constexpr auto limit_{ std::numeric_limits<T>() };

};

using i8 = integral<char>;
using u8 = integral<unsigned char>;

using i16 = integral<short>;
using u16 = integral<unsigned short>;

using i32 = integral<int>;
using u32 = integral<unsigned int>;
