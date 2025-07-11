//
// Created by areg1 on 6/29/2025.
//

#pragma once

#include <string>

class Player;
class Character;
class Monster;
using std::string;

enum class CombatType {
    Melee,
    Ranged
};

enum class JobType {
    Physical,
    Magical
};

class Job {
    friend class Character;
    static const int SOLAR_ECLIPSE_FORCE_LOSS = 1;

    string m_jobTitle;
    JobType m_jobType;
    CombatType m_combatType; // Melee is default

protected:
    static void levelUp(Player &player);
    static void gainCoins(Player& player, int amount);
    static void setMaxHealth(Player& player, int amount);
    static void gainForce(Player& player, int amount);
    static void loseForce(Player& player, int amount);
    static void gainHealth(Player& player, int amount);
    static void loseHealth(Player& player, int amount);

public:
    explicit Job(const string& title, const JobType& jobType,const CombatType& combatType) : m_jobTitle(title), m_jobType(jobType),m_combatType(combatType) {}
    virtual ~Job() = default;

    const string &getJobTitle() const;
    virtual void specialStartGameAttributes(Player& player) const {} // stub override, class player sets because default
    virtual int computeCombatPower(const Player& player) const;
    virtual int solarEclipseImplications(Player &player) const;
    virtual void encounterWinImplications(Player& player, const Monster &monster) const;
    virtual void encounterLoseImplications(Player& player, const Monster &monster) const;
};

class Warrior : public Job {
    static const int WARRIOR_MAX_HEALTH = 150;
    static const int WARRIOR_MULTIPLIER = 2;
    static const int WARRIOR_HEALTH_LOSE = 10;
public:
    // ----- Constructor ----- //
    Warrior() : Job("Warrior", JobType::Physical, CombatType::Melee) {}
    // ----- Methods ----- //
    void specialStartGameAttributes(Player& player) const override;
    int computeCombatPower(const Player& player) const override;
    void encounterWinImplications(Player& player, const Monster &monster) const override;

};

class Archer : public Job {
    static const int EXTRA_ARCHER_COINS = 10;
public:
    // ----- Constructor ----- //
    Archer() : Job("Archer", JobType::Physical, CombatType::Ranged) {}
    // ----- Methods ----- //
    void specialStartGameAttributes(Player& player) const override;
};

class Magician : public Job {
    static const int MAGICIAN_FORCE_INCREASE = 1;
public:
    // ----- Constructor ----- //
    Magician() : Job("Magician", JobType::Magical, CombatType::Ranged) {}
    // ----- Methods ----- //
    int solarEclipseImplications(Player &player) const override;
};

