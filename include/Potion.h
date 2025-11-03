#ifndef POTION_H
#define POTION_H

#include <array>
#include <string_view>

namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        max_types,
    };

    using namespace std::string_view_literals; // for sv literals

    // An array of our enumerators
    constexpr std::array type { healing, mana, speed, invisibility };
    constexpr std::array cost { 20, 30, 12, 50 };
    constexpr std::array name {
        "healing"sv, "mana"sv, "speed"sv, "invisibility"sv
    };

    // Ensure that the length of the arrays isn't mismatched
    static_assert(std::size(type) == max_types,
        "Potion::types: array length mismatch");
    static_assert(std::size(cost) == max_types,
        "Potion::costs: array length mismatch");
    static_assert(std::size(name) == max_types,
        "Potion::names: array length mismatch");
} // namespace Potion

#endif