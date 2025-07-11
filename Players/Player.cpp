//
// Created by areg1 on 6/29/2025.
//

#include "Player.h"

#include <ios>

#include "Character.h"
#include "Job.h"

Player::Player(const string &name, std::unique_ptr<Job> job, std::unique_ptr<Character> character) :
                m_name(name),
                m_job(std::move(job)), m_character(std::move(character)), m_maxHealth(DEFAULT_MAX_HEALTH),
                m_healthPoints(DEFAULT_MAX_HEALTH), m_level(DEFAULT_LEVEL), m_force(DEFAULT_FORCE),
                m_coins(DEFAULT_COINS), m_isFainted(false) {
    m_job->specialStartGameAttributes(*this);
}

bool Player::operator>(const Player& other) const {
    if (m_level != other.m_level)
        return m_level > other.m_level;

    if (m_coins != other.m_coins)
        return m_coins > other.m_coins;

    return  m_name < other.m_name;
}


string Player::getDescription() const {
    const string& jobTitle = m_job->getJobTitle();
    const string& characterType = m_character->getCharacterType();
    const string& levelString = std::to_string(getLevel());
    const string& forceString = std::to_string(getForce());
    string result = m_name + ", " + jobTitle + " with " + characterType + " character (level "
               + levelString + ", force " + forceString + ")";
    return result;
}

string Player::getName() const {
    return m_name;
}

int Player::getLevel() const {
    return m_level;
}

int Player::getForce() const {
    return m_force;
}

int Player::getHealthPoints() const {
    return m_healthPoints;
}

unsigned int Player::getCoins() const {
    return m_coins;
}

int Player::getMaxHealthPoints() const {
    return m_maxHealth;
}

bool Player::isPlayerFainted() const {
    return m_isFainted;
}

int Player::getCombatPower() const {
    return m_job->computeCombatPower(*this);
}

Job & Player::getJob() const {
    return *(m_job);
}

Character & Player::getCharacter() const {
    return *(m_character);
}
