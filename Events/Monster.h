//
// Created by areg1 on 6/30/2025.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

using std::string;

class Monster {

protected:
    string m_name;
    unsigned int m_combatPower = 0;
    int m_loot = 0;
    int m_damage = 0;
    string m_description;

public:
    explicit Monster(const string& name) : m_name(name) {}
    Monster(const string &name, unsigned int combatPower, int loot, int damage) : m_name(name),
        m_combatPower(combatPower), m_loot(loot), m_damage(damage), m_description(m_name + Monster::createDescriptionString()) {}
    virtual ~Monster() = default;
    virtual string createDescriptionString() const;
    virtual void applyPostFightImplications() {};
    const string& getName() const;
    unsigned int getCombatPower() const;
    int getLoot() const;
    int getDamage() const;
    string getDescription() const;

};

class Snail : public Monster {
    static const int SNAIL_COMBAT_POWER = 5;
    static const unsigned int SNAIL_LOOT = 2;
    static const int SNAIL_DAMAGE = 10;

public:
    static const string SNAIL;

    Snail() : Monster(SNAIL, SNAIL_COMBAT_POWER, SNAIL_LOOT, SNAIL_DAMAGE) {}
};

class Slime : public Monster {
    static const int SLIME_COMBAT_POWER = 12;
    static const unsigned int SLIME_LOOT = 5;
    static const int SLIME_DAMAGE = 25;

public:
    static const string SLIME;

    Slime() : Monster(SLIME, SLIME_COMBAT_POWER, SLIME_LOOT, SLIME_DAMAGE) {}
};

class Balrog : public Monster {
    static const int BALROG_COMBAT_POWER = 15;
    static const unsigned int BALROG_LOOT = 100;
    static const int BALROG_DAMAGE = 9001;
    static const int BALROG_COMBAT_POWER_BOOST = 2;

public:
    static const string BALROG;

    Balrog() : Monster(BALROG, BALROG_COMBAT_POWER, BALROG_LOOT, BALROG_DAMAGE) {}

    void applyPostFightImplications() override;

};

class Pack : public Monster {
    std::vector<std::unique_ptr<Monster>> m_packMonsters;
    int m_packSize;

public:
    explicit Pack(std::vector<std::unique_ptr<Monster>>& monsters);
    string createDescriptionString() const override;
    int getPackSize() const;
};