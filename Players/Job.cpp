#include "Job.h"
#include "Player.h"

#define DEFAULT_HP 100
#define WARRIOR_HP 150
#define DEFAULT_COINS 10
#define ARCHER_COINS 20

// Job implementations
// getters

bool Job::isMagical() const
{
    return this->magical;
}

bool Job::isRanged() const
{
    return this->ranged;
}

// default get combat power implementation
int Job::getCombatPower(const Player &player) const
{
    return player.getForce() + player.getLevel();
}

// default get starting hp implementation
int Job::getStartingHp() const
{
    return DEFAULT_HP;
}

// default get starting coins implementation
int Job::getStartingCoins() const
{
    return DEFAULT_COINS;
}

// default get description implementation
string Job::getDescription() const
{
    return this->jobDescription;
}

//  Warrior Job
Warrior::Warrior()
{
    this->magical = false;
    this->ranged = false;
    this->jobDescription = "Warrior";
}
// Warrior get starting hp override
int Warrior::getStartingHp() const
{
    return WARRIOR_HP;
}
// Warrior get combat power override
int Warrior::getCombatPower(const Player &player) const
{
    return player.getForce() * 2 + player.getLevel();
}

// Archer Job
Archer::Archer()
{
    this->magical = false;
    this->ranged = true;
    this->jobDescription = "Archer";
}

// archer starting coins override
int Archer::getStartingCoins() const
{
    return ARCHER_COINS;
}

// Mage Job
Magician::Magician()
{
    this->magical = true;
    this->ranged = true;
    this->jobDescription = "Magician";
}

