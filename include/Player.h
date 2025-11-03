#ifndef PLAYER_H
#define PLAYER_H

#include "Potion.h"
#include "Random.h"
#include <string>
#include <string_view>

class Player {
public:
    explicit Player(std::string_view name)
        : m_name { name }
        , m_gold { Random::get(m_minStartingGold, m_maxStartingGold) }
    {
    }

    bool buyPotion(Potion::Type type) const;

    // Access functions
    std::string_view name() const { return m_name; }
    int gold() const { return m_gold; }
    int inventory(Potion::Type p) const { return m_inventory[p]; }

    void setName(std::string_view name) { m_name = name; }
    void subGold(int x) { m_gold -= x; }
    void addToInventory(Potion::Type p) { m_inventory[p] += 1; }

private:
    static constexpr int m_minStartingGold { 80 };
    static constexpr int m_maxStartingGold { 120 };

    std::string m_name {};
    int m_gold {};
    std::array<int, Potion::max_types> m_inventory {};
};

#endif