#include "Event.h"
#include "Utilities.h"
#include "Player.h"

#define POTION_PRICE 5
using std::string;
// constructors
Encounter::Encounter() : monster(nullptr) {}

Encounter::Encounter(unique_ptr<Monster> monster)
{
    this->monster = std::move(monster);
};

PotionMerchant::PotionMerchant()
{
    this->name = "PotionsMerchant";
};

SolarEclipse::SolarEclipse()
{
    this->name = "SolarEclipse";
};

//event logics

// combat logic
string Encounter::apply(Player &player) const
{
    int monsterCombatPower = this->monster->getCombatPower();
    string message;
    // player wins encounter
    if (player.getCombatPower() > monsterCombatPower)
    {
        // if melee take damage
        if (!player.isRanged())
        {
            player.takeDamage(10);
        }
        // take loot
        int loot = monster->getLoot();
        player.addCoins(loot);

        // player level up
        player.addLevels(1);

        //call after combat of monsters

        // get won message
        message = getEncounterWonMessage(player, loot);
    }
    // combat loss
    else
    {
        // lose hp
        int taken = player.takeDamage(monster->getDamage());

        //get loss message
        message = getEncounterLostMessage(player, taken);
    }
    this->afterCombat();
    return message;
};

// Potion merchant implementation
string PotionMerchant::apply(Player &player) const
{
    int desiredPotions = player.getMaxDesiredPotions(POTION_PRICE);
    int bought = player.buyPotions(desiredPotions, POTION_PRICE);
    //use potions
    player.usePotions(bought);
    return getPotionsPurchaseMessage(player, bought);
};

// Solar eclipse implementation
string SolarEclipse::apply(Player &player) const
{
    int change = 0;
    if (player.isMagical())
    {
        // buff
        change = 1;
    }
    else
    {
        // debuff
        change = -1;
    }
    const int effect = player.addForce(change);
    return getSolarEclipseMessage(player, effect);
}

void Encounter::setMonster(unique_ptr<Monster> newMonster) {
    this->monster = std::move(newMonster);
}

//get description special event implementation
string SpecialEvent::getDescription() const {
    return this->name;
}

//get description encounter implementation
string Encounter::getDescription() const {
    if (this->monster) {
        string desc;
        desc += this->monster->getName();
        desc += " (power ";
        desc += std::to_string(this->monster->getCombatPower());
        desc += ", loot ";
        desc += std::to_string(this->monster->getLoot());
        desc += ", damage ";
        desc += std::to_string(this->monster->getDamage());
        desc += ")";
        return desc;
    }
    return "";
}

void Encounter::afterCombat() const {
    this->monster->afterCombat();
}

