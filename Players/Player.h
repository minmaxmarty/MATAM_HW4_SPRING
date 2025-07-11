#pragma once

#include <string>
#include <memory>
#include "Job.h"
#include "Character.h"

using std::unique_ptr;
using std::string;

class Player
{
private:
    string name;
    int level;
    int force;
    int maxHp;
    int currHp;
    int coins;
    int potions;

    unique_ptr<Job> job;
    unique_ptr<Character> character;

public:
    // constructors
    // default ctor
    Player();

    // ctor with params
    Player(string name, unique_ptr<Job>& job, unique_ptr<Character> &character);

    /**
     * Gets the description of the player
     *
     * @return - description of the player
     */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
     */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
     */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
     */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
     */
    int getHealthPoints() const;

    /**
     * Gets the maximum health points of the player
     *
     * @return - max health points of the player
     */
    int getMaxHealth() const;

    /**
     * Gets the potential health due to potions and other buffs
     *
     * @return - potential health points of the player
     */
    int getPotentialHealth() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
     */
    int getCoins() const;

    /*
     * add coins to player
     */
    void addCoins(int income);

    /*
     * add coins to player
     */
    void addLevels(int levels);

    /**
     * gets the calculated combat power of player
     *
     * @return - combat power of player
     */
    int getCombatPower() const;

    /**
     * Gets if the player is magical
     *
     * @return - if the player is magical
     */
    bool isMagical() const;

    /**
     * Gets if the player is ranged
     *
     * @return - if the player is ranged
     */
    bool isRanged() const;

    /**
     * gets the maximum amout of potions player watns
     *
     * @return - amount of potions player wants to buy
     */
    int getMaxDesiredPotions(int price) const;

    /**
     * makes the player buy amount of potions
     * @return - amount of potions actually bought
     */
    int buyPotions(int amount, int price);

    /**
     * makes the player use a potion to replenish hp
     */
    void usePotions(int amount);

    /**
     * makes the player take damage
     * @return - actual damage taken
     */
    int takeDamage(int damage);

    /**
     * buffs/debuffs players force
     * @return - actual change applied
     */
    int addForce(int force);

    //custom logic for do combat
    void doCombat(const Monster &monster) const;


    friend bool operator>(const Player& lhs, const Player& rhs);
};

// symmetrical operator>
bool operator>(const Player& lhs, const Player& rhs);