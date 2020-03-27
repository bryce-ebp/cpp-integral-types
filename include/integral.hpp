#pragma once

#include <numeric>
#include <type_traits>
#include <bitset>
#include <cctype>
#include <algorithm>

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

    constexpr std::bitset<sizeof(T) * 8> &get_bitset() const noexcept { return bitset_; }

    [[nodiscard]] std::string bitset_str() const noexcept {
        return bitset_.to_string();
    }

    [[nodiscard]] constexpr unsigned short count_ones() const noexcept {
        return get_bitset().count();
    }

    [[nodiscard]] constexpr unsigned short count_zeros() const noexcept {
        return bitset_size() - count_ones();
    }

    [[nodiscard]] constexpr unsigned short bitset_size() const noexcept {
        return get_bitset().size();
    }

    constexpr T leading_zeros() const noexcept {
        const auto str{ bitset_str() };

        return std::distance(str.begin(), std::adjacent_find(str.begin(), str.end(), [] (const auto &lhs, const auto &rhs) {
            return lhs != rhs;
        })) + 1;
    }

    constexpr T trailing_zeros() const noexcept {
        const auto str{ bitset_str() };

        return std::distance(str.rbegin(), std::adjacent_find(str.rbegin(), str.rend(), [] (const auto &lhs, const auto &rhs) {
            return lhs != rhs;
        })) + 1;
    }

    [[nodiscard]] constexpr bool is_pow_2() const noexcept {
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

    [[nodiscard]] constexpr T next_pow_2() const noexcept {
        auto ret{ value_ };
        --ret;
        ret |= ret >> 1;
        ret |= ret >> 2;
        ret |= ret >> 4;
        ret |= ret >> 8;
        ret |= ret >> 16;
        return ++ret;
    }

private:
    T value_{ };
    static constexpr auto limit_{ std::numeric_limits<T>() };
    std::bitset<sizeof(T) * 8> bitset_{ value_ };

};

using i8 = integral<char>;
using u8 = integral<unsigned char>;

using i16 = integral<short>;
using u16 = integral<unsigned short>;

using i32 = integral<int>;
using u32 = integral<unsigned int>;
