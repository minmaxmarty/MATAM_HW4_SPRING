//
// Created by areg1 on 6/30/2025.
//

#include "Monster.h"

const string Snail::SNAIL = "Snail";
const string Slime::SLIME = "Slime";
const string Balrog::BALROG = "Balrog";

Pack::Pack(std::vector<std::unique_ptr<Monster>> &monsters) : Monster("Pack"),
    m_packMonsters(std::move(monsters)), m_packSize(m_packMonsters.size()) {
    for (const auto monster : m_packMonsters) {
        m_combatPower += monster->getCombatPower();
        m_loot += monster->getLoot();
        m_damage += monster->getDamage();
    }
}

int Pack::getPackSize() const {
    return m_packSize;
}

const string & Monster::getName() const {
    return m_name;
}

unsigned int Monster::getCombatPower() const {
    return m_combatPower;
}

int Monster::getLoot() const {
    return m_loot;
}

int Monster::getDamage() const {
    return m_damage;
}

void Balrog::applyPostFightImplications() {
    m_combatPower += BALROG_COMBAT_POWER_BOOST;
}
