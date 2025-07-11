#pragma once

#include <vector>
#include <memory>
#include <string>

class Monster
{
protected:
    int force;
    int loot;
    int damage;
    std::string name;

public:
    Monster() : force(0), loot(0), damage(0) {}
    virtual ~Monster() = default;

    virtual int getCombatPower() const;
    virtual int getLoot() const;
    virtual int getDamage() const;
    virtual std::string getName() const;
    virtual void afterCombat() {}
};

class Snail : public Monster
{
public:
    Snail();
};

class Slime : public Monster
{
public:
    Slime();
};

class Balrog : public Monster
{
public:
    Balrog();
    void afterCombat() override;
};

class Pack final : public Monster
{
private:
    std::vector<std::unique_ptr<Monster>> monsters;
    // get recursive length of pack
    int getLength() const;

public:
    Pack();
    ~Pack() override = default;

    int getCombatPower() const override;
    int getLoot() const override;
    int getDamage() const override;
    void afterCombat() override;
    std::string getName() const override;

    void addMonster(std::unique_ptr<Monster> monster);
};
