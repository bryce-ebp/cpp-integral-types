#include <iostream>
#include <chrono>

#include "integral.hpp"


int main() {
    constexpr i32 var { 8 };
    constexpr u16 var2 {240 };
    constexpr i32 var3{ var + var2 };

    const auto prev_time = std::chrono::steady_clock::now();

    std::cout << "var: " << var << '\n'
            << "var get_max: " << var.get_max() << '\n'
            << "var get_min: " << var.get_min() << '\n'
            << "var is_pow_2: " << var.is_pow_two() << "\n\n\n"


            << "var2: " << var2 << '\n'
            << "var2: get_max: " << var2.get_max() << '\n'
            << "var2: get_min: " << var2.get_min() << '\n'
            << "var2: trailing_zeros: " << var2.trailing_zeros() << '\n'
            << "var2 is_pow2: " << var2.is_pow_two() << "\n\n\n"


            << "var3: " << var3 << '\n'
            << "var3 get_max: " << var3.get_max() << '\n'
            << "var3 get_min: " << var3.get_min() << '\n'
            << "execution: " << std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - prev_time).count();

    return 0;
}
