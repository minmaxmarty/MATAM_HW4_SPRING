#pragma once

#include <string>

using std::string;

//forward declaration
class Player;

class Character
{
protected:
    string characterDescription;

public:
    // virtual destructor
    virtual ~Character() = default;
    // how many potions does the player want to buy
    virtual int potionBuyAmount(const Player &player, int price) const = 0;

    // get character description
    string getDescription() const;
};

// types of character

class Responsible : public Character
{
public:
    Responsible();
    // can buy potion method
    int potionBuyAmount(const Player &player, int price) const override;
};

class RiskTaking : public Character
{
public:
    RiskTaking();
    // can buy potion method
    int potionBuyAmount(const Player &player, int price) const override;
};