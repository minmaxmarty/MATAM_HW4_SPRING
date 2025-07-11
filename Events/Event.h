#pragma once

#include "Player.h"
#include "Monster.h"

#include <string>

using std::unique_ptr;

class Event
{
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
     */
    virtual std::string getDescription() const = 0;

    // apply event method
    virtual std::string apply(Player &player) const = 0;

    virtual ~Event() = default;
};

class Encounter : public Event
{
private:
    unique_ptr<Monster> monster;

public:
    // ctor
    Encounter();

    // ctor with param
    explicit Encounter(unique_ptr<Monster> monster);

    // apply override
    std::string apply(Player &player) const override;

    //get description
    std::string getDescription() const override;

    void setMonster(unique_ptr<Monster> newMonster);

    void afterCombat() const;
};

class SpecialEvent : public Event
{
protected:
    std::string name;

public:
    ~SpecialEvent() override = default;

    //get description
    std::string getDescription() const override;
};

class PotionMerchant final : public SpecialEvent
{
public:
    PotionMerchant();

    // apply override
    std::string apply(Player &player) const override;
};

class SolarEclipse final : public SpecialEvent
{
public:
    SolarEclipse();

    // apply override
    std::string apply(Player &player) const override;
};
