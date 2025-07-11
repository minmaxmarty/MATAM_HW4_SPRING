//
// Created by areg1 on 6/30/2025.
//

#pragma once

#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <iostream>

#include "Players/Character.h"
#include "Events/Event.h"
#include "Players/Job.h"
#include "Events/Monster.h"

class Player;
class Event;

using std::string;

class Factory {
    static const int MAX_NAME_LENGTH = 15;
    static const int MIN_NAME_LENGTH = 3;
    static const int MIN_PLAYER_NUMBER = 2;
    static const int MAX_PLAYER_NUMBER = 6;
    static const int MIN_EVENT_NUMBER = 2;
    static const int MIN_PACK_SIZE = 2;

    const std::map<string, std::function<std::unique_ptr<Job>()>> jobFactory = {
        {"Warrior", []() {return std::make_unique<Warrior>(); }},
        {"Archer", []() {return std::make_unique<Archer>(); }},
        {"Magician", []() {return std::make_unique<Magician>(); }},
    };

    const std::map<string, std::function<std::unique_ptr<Character>()>> characterFactory = {
        {"Responsible", []() {return std::make_unique<Responsible>(); }},
        {"RiskTaking", []() {return std::make_unique<RiskTaking>(); }}
    };

    const std::map<string, std::function<std::unique_ptr<Monster>()>> monsterFactory = {
        {"Snail", []() {return std::make_unique<Snail>(); }},
        {"Slime", []() {return std::make_unique<Slime>(); }},
        {"Balrog", []() {return std::make_unique<Balrog>(); }},
    };

    const std::map<string, std::function<std::unique_ptr<SpecialEvent>()>> specialEventsFactory = {
        {"SolarEclipse", []() {return std::make_unique<SolarEclipse>(); }},
        {"PotionsMerchant", []() {return std::make_unique<PotionsMerchant>(); }}
    };

    Factory() = default;
    ~Factory() = default;

    bool checkPlayerInput(const string& name, const string& job, const string& character) const;
    std::unique_ptr<Pack> packFactory(std::istream &packInput) const;

    static bool hasNonLetter(const string& name);

public:
    Factory(const Factory&) = delete;
    Factory(Factory&) = delete;
    Factory operator=(const Factory&) = delete;
    Factory operator=(Factory&) = delete;

    static Factory& factoryInstance();

    std::vector<std::unique_ptr<Player>> createPlayers(std::istream& playersStream) const;
    std::vector<std::unique_ptr<Event>> createEvents(std::istream& eventStream) const;
};

