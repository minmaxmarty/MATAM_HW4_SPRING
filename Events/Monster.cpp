#include "Monster.h"

// Monster constructors
Snail::Snail()
{
    this->force = 5;
    this->loot = 2;
    this->damage = 10;
    this->name = "Snail";
}

Slime::Slime()
{
    this->force = 12;
    this->loot = 5;
    this->damage = 25;
    this->name = "Slime";
}

Balrog::Balrog()
{
    this->force = 15;
    this->loot = 100;
    this->damage = 9001;
    this->name = "Balrog";
}

//default methods
int Monster::getCombatPower() const {
    return this->force;
}

int Monster::getLoot() const {
    return this->loot;
}

int Monster::getDamage() const {
    return this->damage;
}

void Balrog::afterCombat()
{
    this->force += 2;
}

// Pack implementation
Pack::Pack() = default;

void Pack::addMonster(std::unique_ptr<Monster> monster)
{
    monsters.push_back(std::move(monster));
}

int Pack::getCombatPower() const
{
    int totalPower = 0;
    for (const auto &monster : monsters)
    {
        totalPower += monster->getCombatPower();
    }
    return totalPower;
}

int Pack::getLoot() const
{
    int totalLoot = 0;
    for (const auto &monster : monsters)
    {
        totalLoot += monster->getLoot();
    }
    return totalLoot;
}

int Pack::getDamage() const
{
    int totalDamage = 0;
    for (const auto &monster : monsters)
    {
        totalDamage += monster->getDamage();
    }
    return totalDamage;
}

std::string Monster::getName() const {
    return this->name;
}

std::string Pack::getName() const {
    std::string name;
    name += "Pack of ";
    name += std::to_string(this->getLength());
    name += " members";
    return name;
}


void Pack::afterCombat()
{
    for (const auto &monster : monsters)
    {
        monster->afterCombat();
    }
}

//get length implementation
int Pack::getLength() const {
    int count = 0;
    for (const auto &monster : monsters) {
        // dynamic cast checks if monster is pack
        if (auto pack = dynamic_cast<Pack *>(monster.get())) {
            count += pack->getLength();
        } else {
            // other monsters add 1
            count++;
        }
    }
    return count;
}

