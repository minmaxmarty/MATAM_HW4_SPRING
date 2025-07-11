//
// Created by areg1 on 6/29/2025.
//

#include "Character.h"

#include "Job.h"
#include "Player.h"


void Character::gainHealth(Player &player, int amount) {
    Job::gainHealth(player, amount);
}

void Character::gainCoins(Player &player, int amount) {
    Job::gainCoins(player, amount);
}

const string &Character::getCharacterType() const {
    return m_type;
}

int Responsible::howManyPotions(Player &player) {
    int curCoins = player.getCoins();
    int curHealth = player.getHealthPoints();
    const int curMaxHealth = player.getMaxHealthPoints();
    int amountToBuy = 0;
    while (curMaxHealth - curHealth > 0 && curCoins >= POTION_PRICE) {
        amountToBuy++;
        curHealth += POTION_HEALTH_BOOST;
        curCoins -= POTION_PRICE;

    }

    updatePlayerAfterEvent(player, amountToBuy);
    return amountToBuy;
}

int RiskTaking::howManyPotions(Player &player) {
    const int curHealth = player.getHealthPoints();
    int amountToBuy = 0;
    if (curHealth < BUYING_HEALTH_THRESHOLD) {
        amountToBuy++;
    }

    updatePlayerAfterEvent(player, amountToBuy);
    return amountToBuy;
}

void Character::updatePlayerAfterEvent(Player &player, const int amountToBuy) {
    const int price = amountToBuy * POTION_PRICE;
    const int healthBoost = amountToBuy * POTION_HEALTH_BOOST;
    gainHealth(player, healthBoost);
    gainCoins(player, price);
}
