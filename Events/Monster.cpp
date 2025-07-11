//
// Created by areg1 on 6/30/2025.
//

#include "Monster.h"

const string Snail::SNAIL = "Snail";
const string Slime::SLIME = "Slime";
const string Balrog::BALROG = "Balrog";

string Monster::createDescriptionString() const {
    const string& power = std::to_string(m_combatPower);
    const string& loot = std::to_string(m_loot);
    const string& damage = std::to_string(m_damage);
    string result = " (power " + power + ", " +
                    "loot " + loot + ", " +
                    "damage " + damage + ")";
    return result;
}

Pack::Pack(std::vector<std::unique_ptr<Monster>> &monsters) : Monster("Pack"),
                                                              m_packMonsters(std::move(monsters)), m_packSize(0) {
    for (auto& monster : m_packMonsters) {
        m_combatPower += monster->getCombatPower();
        m_loot += monster->getLoot();
        m_damage += monster->getDamage();
        if (auto* pack = dynamic_cast<Pack*>(monster.get())) {
            m_packSize += pack->m_packSize;
        } else {
            m_packSize += 1;
        }
    }

    m_description = m_name + Pack::createDescriptionString();
}

int Pack::getPackSize() const {
    return m_packSize;
}

string Pack::createDescriptionString() const {
    return " of " + std::to_string(m_packSize) + " members" + Monster::createDescriptionString();
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

string Monster::getDescription() const {
    return m_description;
}

void Balrog::applyPostFightImplications() {
    m_combatPower += BALROG_COMBAT_POWER_BOOST;
    m_description = Monster::createDescriptionString(); // update description
}
