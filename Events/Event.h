
#pragma once

#include <vector>

#include "../Players/Player.h"

class Monster;

class Event {
protected:
    string m_description;
    static void faintPlayer(Player& player);

public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    Event() = default;
    explicit Event(const string& description) : m_description(description) {}
    virtual ~Event() = default;
    virtual string getDescription() const;
    virtual string applyEvent(Player& player) const = 0;

};

class SpecialEvent : public Event {

public:
    explicit SpecialEvent(const string& description) : Event(description) {}
};

class SolarEclipse : public SpecialEvent {

public:
    static const string SOLAR_ECLIPSE;

    SolarEclipse() : SpecialEvent(SOLAR_ECLIPSE) {}
    string applyEvent(Player& player) const override;

};

class PotionsMerchant : public SpecialEvent {

public:
    static const string POTIONS_MERCHANT;

    PotionsMerchant() : SpecialEvent(POTIONS_MERCHANT) {}
    string applyEvent(Player& player) const override;

};

class Encounter : public Event {
    std::unique_ptr<Monster> m_monster;

    static string createDescriptionString(const std::unique_ptr<Monster> &monster) ;

public:
    explicit Encounter(std::unique_ptr<Monster> monster);
    string applyEvent(Player& player) const override;
};


