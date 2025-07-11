#include "Player.h"
#include <utility>

// Player default constructor implementation
Player::Player() : level(0), force(0), maxHp(0), currHp(0), coins(0), potions(0), job(nullptr),
                   character(nullptr) {
};

// Player param constructor implementation
Player::Player(string name, std::unique_ptr<Job>& job, std::unique_ptr<Character>& character)
    : name(std::move(name)), level(1), force(5), maxHp(job->getStartingHp()),
      currHp(maxHp), coins(job->getStartingCoins()), potions(0),
      job(std::move(job)), character(std::move(character)) {}


// get player name implementation
string Player::getName() const
{
    return this->name;
}

// get player level implementation
int Player::getLevel() const
{
    return this->level;
}

// get player force implementation
int Player::getForce() const
{
    return this->force;
}

// get player health points implementation
int Player::getHealthPoints() const
{
    return this->currHp;
}

// get player max health implementation
int Player::getMaxHealth() const
{
    return this->maxHp;
}

// get potential health implementation
int Player::getPotentialHealth() const
{
    // if fainted, potions won't help
    if (this->currHp <= 0)
    {
        return 0;
    }

    int rawPotentialHp = this->currHp + 10 * this->potions;

    if (rawPotentialHp < this->maxHp)
    {
        return rawPotentialHp;
    }

    // prevent overheal
    return this->maxHp;
}

// get player description implementation
string Player::getDescription() const
{
    if (job && character)
    {
        string description = name;

        description += ", " + job->getDescription();
        description += " with " + character->getDescription() + " character";
        description += " (level " + std::to_string(level) + ", force " + std::to_string(force) + ")";
        return description;
    }
    return "";
}

// get coins of the player implementation
int Player::getCoins() const
{
    return this->coins;
}

// add coins implementation
void Player::addCoins(int income)
{
    this->coins += income;
}

// add levels implementation
void Player::addLevels(int levels)
{
    this->level += levels;
}

// get combat power implementation
int Player::getCombatPower() const
{
    return this->job->getCombatPower(*this);
}

// get if player is magical
bool Player::isMagical() const
{
    return this->job->isMagical();
}

// get if player is ranged
bool Player::isRanged() const
{
    return this->job->isRanged();
}

// get max desired potions implementation
int Player::getMaxDesiredPotions(int price) const
{
    return this->character->potionBuyAmount(*this, price);
}

// buy potion implementation
int Player::buyPotions(int amount, int price)
{
    int purchased = 0;
    while (this->coins >= price && purchased < amount)
    {
        this->potions++;
        purchased++;
        this->coins -= price;
    }
    return purchased;
}

// use potion implementation
void Player::usePotions(int amount)
{
    int used = 0;
    while (this->potions > 0 && used < amount)
    {
        // lower potion count
        --this->potions;

        // prevent overhead
        if (this->maxHp - this->currHp < 10)
        {
            this->currHp = this->maxHp;
        }
        else
        {
            this->currHp += 10;
        }
        //increment used
        used++;
    }
}

// take damage implementation
int Player::takeDamage(int damage)
{
    // fainted logic
    if (damage >= this->currHp) {
        this->currHp = 0;
    } else {
        this->currHp -= damage;
    }
    return damage;
}

// add force implementation
int Player::addForce(int forceChange)
{
    int newForce = this->force + forceChange;
    if (newForce <= 0) {
        // all current force is changed
        int effect = -1 * this->force;
        this->force = 0;
        return effect;
    } else {
        this->force = newForce;
    }
    return forceChange;
}

//do combat implementation
void Player::doCombat(const Monster &monster) const {
    this->job->doCombat(*this, monster);
}


bool operator>(const Player &lhs, const Player &rhs) {
    // Higher level - priority 1
    if (lhs.getLevel() != rhs.getLevel()) return lhs.getLevel() > rhs.getLevel();
    // Higher Coins - priority 2
    if (lhs.getCoins() != rhs.getCoins()) return lhs.getCoins() > rhs.getCoins();
    // Lexicographical order - priority 3
    return lhs.getName() < rhs.getName();
}

