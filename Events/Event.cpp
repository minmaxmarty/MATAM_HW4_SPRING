//
// Created by areg1 on 7/1/2025.
//

#include "Event.h"

#include "Character.h"
#include "Job.h"
#include "Monster.h"
#include "Utilities.h"

const string SolarEclipse::SOLAR_ECLIPSE = "SolarEclipse";
const string PotionsMerchant::POTIONS_MERCHANT = "PotionsMerchant";

void Event::faintPlayer(Player &player) {
    player.m_isFainted = true;
}

string Event::getDescription() const {
    return m_description;
}

string Encounter::applyEvent(Player &player) {
    const unsigned int playerCombatPower = player.getCombatPower();
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
    m_description = m_monster->getName() + m_monster->createDescriptionString();
    if (player.getHealthPoints() == 0) {
        faintPlayer(player);
    }
    if (didWin) {
        return getEncounterWonMessage(player, m_monster->getLoot());
    }
    return getEncounterLostMessage(player, m_monster->getDamage());
}

string SolarEclipse::applyEvent(Player &player) {
    const int forceGain = player.getJob().solarEclipseImplications(player);
    return getSolarEclipseMessage(player, forceGain);
}

string PotionsMerchant::applyEvent(Player &player) {
    const int amount = player.getCharacter().howManyPotions(player);
    return getPotionsPurchaseMessage(player, amount);
}

Encounter::Encounter(std::unique_ptr<Monster> monster) : m_monster(std::move(monster)) {
    m_description = m_monster->getDescription();
}
