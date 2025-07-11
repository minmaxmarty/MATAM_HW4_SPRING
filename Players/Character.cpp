#include "Character.h"
#include <string>
#include "Player.h"
#include <cmath>

using std::string;

// Character

// default get description implementation
string Character::getDescription() const
{
    return this->characterDescription;
}

// Responsible Character
Responsible::Responsible()
{
    this->characterDescription = "Responsible";
}

// Responsible potion buy amount
int Responsible::potionBuyAmount(const Player &player, int price) const
{
    int missingHealth = player.getMaxHealth() - player.getPotentialHealth();
    int hpLimitedAmount = ceil(missingHealth / 10);

    int coinLimitedAmount = floor(player.getCoins() / price);

    // min is first limitation
    return std::min(hpLimitedAmount, coinLimitedAmount);
}
// Risktaking Character
RiskTaking::RiskTaking()
{
    this->characterDescription = "RiskTaking";
}

// RiskTaking potion buy amount
int RiskTaking::potionBuyAmount(const Player &player, int price) const
{
    if (player.getHealthPoints() < 50)
    {
        return 1;
    }
    return 0;
}
