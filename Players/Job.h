#pragma once
#include <Monster.h>
#include <string>

using std::string;

//forward declaration
class Player;

class Job
{
protected:
    bool magical;
    bool ranged;
    string jobDescription;

public:
    // virtual destructor
    virtual ~Job() = default;
    // getters
    bool isMagical() const;

    bool isRanged() const;

    // handle combat method
    virtual int getCombatPower(const Player &player) const;

    // default max hp
    virtual int getStartingHp() const;

    // default coins
    virtual int getStartingCoins() const;

    // get job description
    string getDescription() const;

    //custom combat logic - default do nothing
    virtual void doCombat(const Player &player, const Monster &monster) const {};
};

// types of jobs

class Warrior : public Job
{
public:
    // default ctor
    Warrior();

    // get combat power
    int getCombatPower(const Player &player) const override;

    // warrior has custom initial hp
    int getStartingHp() const override;
};

class Archer : public Job
{
public:
    // default ctor
    Archer();

    // archer has custom initial coins
    int getStartingCoins() const override;
};

class Magician : public Job
{
public:
    // default ctor
    Magician();
};