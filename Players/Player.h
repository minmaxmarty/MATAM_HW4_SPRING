#pragma once

#include <string>
#include <memory>

class Job;
class Character;

using std::string;

class Player {
    static const unsigned int DEFAULT_MAX_HEALTH = 100;
    static const unsigned int DEFAULT_LEVEL = 1;
    static const unsigned int DEFAULT_FORCE = 5;
    static const unsigned int DEFAULT_COINS = 10;

    friend class Job;
    friend class Character;
    friend class Event;

    string m_name;
    std::unique_ptr<Job> m_job;
    std::unique_ptr<Character> m_character;
    unsigned int m_maxHealth;
    unsigned int m_healthPoints;
    int m_level;
    unsigned int m_force;
    unsigned int m_coins;
    bool m_isFainted;


public:
    static const unsigned int MAX_LEVEL = 10;

    Player(const string& name, std::unique_ptr<Job> job, std::unique_ptr<Character> character);

    Job& getJob() const;

    Character& getCharacter() const;

    bool operator>(const Player& leftPlayer) const;

    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    unsigned int getCoins() const;

    int getMaxHealthPoints() const;

    bool isPlayerFainted() const;

    int getCombatPower() const;
};
