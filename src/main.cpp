#include "ErrorHandling.h"
#include "Player.h"
#include "Potion.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace AboutProgram {
    std::string name { "Roscoe's Potion Emporium" };
    std::string version { "1.0.0" };
    std::string author { "Itosh1key" };

    void print()
    {
        std::cout << name << " v" << version << '\n'
                  << "By " << author << "\n\n";
    }
} // namespace AboutProgram

constexpr std::string_view getPlayerName()
{
    std::cout << "Enter your name: ";
    std::string playerName {};
    std::getline(std::cin >> std::ws, playerName);
    return playerName;
}

void printPlayerNameAndGold(const Player& p)
{
    std::cout << "Hello, " << p.name() << ", "
              << "you have " << p.gold() << " gold.\n";
}

// This function converts the character to a number
int charNumToInt(char c)
{
    return c - '0';
}

Potion::Type whichPotion()
{
    std::cout << "Enter the number of the potion you'd like to buy, or "
              << "'q' to quit: ";
    char input {};

    while (true) {
        std::cin >> input;

        // put us back in 'normal' operation mode
        if (ErrorHandling::clearFailedExtraction()) { 
            ErrorHandling::ignoreLine(); // and remove the bad input
            continue;
        }

        // If there is extraneous input, treat as failure case
        if (ErrorHandling::hasUnextractedInput()) {
            std::cout << "I didn't understand what you said. Try again: ";
            ErrorHandling::ignoreLine(); // ignore any extraneous input
            continue;
        }

        if (input == 'q')
            return Potion::max_types;

        // Convert the char to a number and see if it's a valid potion selection
        int val { charNumToInt(input) };
        if (val >= 0 && val < Potion::max_types)
            return static_cast<Potion::Type>(val);
        
        // It wasn't a valid potion selection
        std::cout << "I didn't understand what you said. Try again: ";
        ErrorHandling::ignoreLine();
    }
}

// This function returns false if the player can't afford a potion, true if purchased
bool buyPotion(Player& p, Potion::Type type)
{
    if (p.gold() < Potion::cost[type])
        return false;

    p.subGold(Potion::cost[type]);
    p.addToInventory(type);

    return true;
}

// Main shop logic
void shop(Player& p)
{
    while (true) {
        std::cout << "\nHere's our selection for today:\n";

        for (const auto& e : Potion::type)
            std::cout << e << ") " << "A " << Potion::name[e]
                      << " potion costs " << Potion::cost[e] << '\n';

        Potion::Type which { whichPotion() };
        if (which == Potion::max_types)
            return;

        bool success { buyPotion(p, which) };
        if(!success)
            std::cout << "You can not afford that.\n";
        else
            std::cout << "You purchased a potion of "<< Potion::name[which]
                      << ".  You have " << p.gold() << " gold left.\n";
    }
}

void printPlayerInventoryAndGold(const Player& p)
{
    std::cout << "\nYour inventory contains:\n";

    for (const auto& e : Potion::type) {
        if (p.inventory(e) > 0)
            std::cout << p.inventory(e) << "x potion of " << Potion::name[e] << '\n';
    }

    std::cout << "You escaped with " << p.gold() << " gold remaining.\n";
}

int main()
{
    AboutProgram::print();

    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::string name { getPlayerName() };

    Player player { name };

    printPlayerNameAndGold(player);

    shop(player);

    printPlayerInventoryAndGold(player);

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";
}