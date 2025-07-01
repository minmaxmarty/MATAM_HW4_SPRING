//
// Created by areg1 on 7/1/2025.
//

#include "Event.h"

#include "Character.h"
#include "Job.h"
#include "Monster.h"
#include "Utilities.h"

const string SolarEclipse::SOLAR_ECLIPSE = "Solar Eclipse";
const string PotionsMerchant::POTIONS_MERCHANT = "Potions Merchant";

void Event::faintPlayer(Player &player) {
    player.m_isFainted = true;
}

string Event::getDescription() const {
    return m_description;
}

string Encounter::applyEvent(Player &player) const {
    const int playerCombatPower = player.getCombatPower();
    const unsigned int monsterCombatPower = m_monster->getCombatPower();
    bool didWin = false;
    if (playerCombatPower > monsterCombatPower) {
        player.getJob().encounterWinImplications(player, *m_monster);
        didWin = true;
    }
    else {
        player.getJob().encounterLoseImplications(player, *m_monster);
    }
    m_monster->applyPostFightImplications();
    if (player.getHealthPoints() == 0) {
        faintPlayer(player);
    }
    if (didWin) {
        return getEncounterWonMessage(player, m_monster->getLoot());
    }
    return getEncounterLostMessage(player, m_monster->getDamage());
}

string SolarEclipse::applyEvent(Player &player) const {
    const int forceGain = player.getJob().solarEclipseImplications(player);
    return getSolarEclipseMessage(player, forceGain);
}

string PotionsMerchant::applyEvent(Player &player) const {
    const int amount = player.getCharacter().howManyPotions(player);
    return getPotionsPurchaseMessage(player, amount);
}

Encounter::Encounter(std::unique_ptr<Monster> monster) : m_monster(std::move(monster)) {
    const string& name = monster->getName();
    if (auto pack = dynamic_cast<Pack*>(monster.get())) {
        const string& packSize = std::to_string(pack->getPackSize());
        m_description = "Pack of " + packSize + " members" + createDescriptionString(monster);
    }
    m_description = name + createDescriptionString(monster);
}

string Encounter::createDescriptionString(const std::unique_ptr<Monster> &monster) {
    const string& power = std::to_string(monster->getCombatPower());
    const string& loot = std::to_string(monster->getLoot());
    const string& damage = std::to_string(monster->getDamage());
    string result = " (power " + power + ", " +
                    "loot " + loot + ", " +
                    "damage " + damage + ")";
    return result;
}
