//
// Created by areg1 on 6/29/2025.
//

#pragma once

#include <string>

class Job;
class Player;
using std::string;

class Character {
    string m_type;

protected:
    static void gainHealth(Player& player, int amount);
    static void gainCoins(Player& player, int amount);


public:
    static const int POTION_PRICE = 5;
    static const int POTION_HEALTH_BOOST = 10;

    explicit Character(const string& type) : m_type(type) {}
    virtual ~Character() = default;

    const string &getCharacterType() const;
    virtual int howManyPotions(Player &player) = 0;
    static void updatePlayerAfterEvent(Player& player, int amountToBuy);
};

class Responsible : public Character {

public:
    Responsible() : Character("Responsible") {}
    int howManyPotions(Player &player) override;
};

class RiskTaking : public Character {
    static const int BUYING_HEALTH_THRESHOLD = 50;

public:
    RiskTaking() : Character("RiskTaking") {}
    int howManyPotions(Player &player) override;
};


