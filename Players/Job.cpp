//
// Created by areg1 on 6/29/2025.
//

#include "Player.h"
#include "Job.h"

#include "Monster.h"

void Job::encounterWinImplications(Player &player, const Monster &monster) const {
    levelUp(player);
    gainCoins(player, monster.getLoot());
}

void Job::encounterLoseImplications(Player &player, const Monster &monster) const {
    loseHealth(player, monster.getDamage());
}

void Job::gainHealth(Player &player, const int amount) {
    const int curHealth = player.m_healthPoints;
    if (curHealth + amount > player.getMaxHealthPoints()) {
        player.m_healthPoints = player.getMaxHealthPoints();
    }
    else {
        player.m_healthPoints += amount;
    }
}

void Job::loseHealth(Player &player, const int amount) {
    const int curHealth = player.m_healthPoints;
    if (curHealth - amount < 0) {
        player.m_healthPoints = 0;
    }
    else {
        player.m_healthPoints -= amount;
    }
}

void Warrior::encounterWinImplications(Player &player, const Monster &monster) const {
    Job::encounterWinImplications(player, monster);
    loseHealth(player, WARRIOR_HEALTH_LOSE);
}

void Job::levelUp(Player &player) {
    player.m_level++;
}

void Job::gainCoins(Player &player, int amount) {
    player.m_coins = amount;
}

void Job::setMaxHealth(Player &player, int amount) {
    player.m_maxHealth = amount;
}

void Job::gainForce(Player &player, const int amount) {
    player.m_force += amount;
}

void Job::loseForce(Player &player, const int amount) {
    gainForce(player, -amount);
}

const string &Job::getJobTitle() const {
    return m_jobTitle;
}

int Job::computeCombatPower(const Player &player) const {
    return player.m_force + player.m_level;
}

int Job::solarEclipseImplications(Player &player) const {
    loseForce(player, SOLAR_ECLIPSE_FORCE_LOSS);
    return -SOLAR_ECLIPSE_FORCE_LOSS;
}

void Warrior::specialStartGameAttributes(Player &player) const {
    setMaxHealth(player, WARRIOR_MAX_HEALTH);
}

int Warrior::computeCombatPower(const Player &player) const {
    return player.getForce() * WARRIOR_MULTIPLIER + player.getLevel();
}

void Archer::specialStartGameAttributes(Player &player) const {
    gainCoins(player, EXTRA_ARCHER_COINS);
}

int Magician::solarEclipseImplications(Player &player) const {
    gainForce(player, MAGICIAN_FORCE_INCREASE);
    return MAGICIAN_FORCE_INCREASE;
}
