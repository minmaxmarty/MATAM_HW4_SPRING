//
// Created by areg1 on 6/30/2025.
//

#include "Factory.h"

#include "MyExceptions.h"
#include "Player.h"

Factory & Factory::factoryInstance() {
    static Factory instance; // made in a static space, so it exists until the program exits
    return instance;
}

bool Factory::hasNonLetter(const string &name) {
    for (const char c : name) {
        if (!isalpha(c)) {
            return true;
        }
    }
    return false;
}

bool Factory::checkPlayerInput(const string &name, const string &job, const string &character) const {
    if (name.length() > MAX_NAME_LENGTH || name.length() < MIN_NAME_LENGTH
        || hasNonLetter(name) || jobFactory.find(job) == jobFactory.end() ||
        characterFactory.find(character) == characterFactory.end()) {
        return false;
    }
    return true;
}

std::vector<std::unique_ptr<Player>> Factory::createPlayers(std::istream &playersStream) const {
    string name, job, character;
    std::vector<std::unique_ptr<Player>> players;
    while (playersStream >> name >> job >> character) {
        if (!checkPlayerInput(name, job, character)) {
            throw InvalidPlayerInput();
        }
        players.push_back(std::make_unique<Player>(
            name,
            jobFactory.at(job)(),
            characterFactory.at(character)())); // push new player into the vector
    }
    int numberOfPlayers = players.size();
    if (numberOfPlayers < MIN_PLAYER_NUMBER || numberOfPlayers > MAX_PLAYER_NUMBER) {
        throw InvalidPlayerInput();
    }
    return players;

}

std::vector<std::unique_ptr<Event>> Factory::createEvents(std::istream &eventStream) const {
    string eventName;
    std::vector<std::unique_ptr<Event>> events;
    while (eventStream >> eventName) {
        if (monsterFactory.find(eventName) != monsterFactory.end()) {
            events.push_back(std::make_unique<Encounter>(monsterFactory.at(eventName)()));
        }
        else if (eventName == "Pack") {
            events.push_back(std::make_unique<Encounter>(packFactory(eventStream)));
        }
        else if (specialEventsFactory.find(eventName) != specialEventsFactory.end()) {
            events.push_back(specialEventsFactory.at(eventName)());
        }
        else {
            throw InvalidEventInput();
        }
    }
    if (events.size() < MIN_EVENT_NUMBER) {
        throw InvalidEventInput();
    }
    return events;
}

std::unique_ptr<Pack> Factory::packFactory(std::istream &packInput) const {
    int packSize;
    if (packInput >> packSize && packSize >= MIN_PACK_SIZE) {
        int i;
        std::vector<std::unique_ptr<Monster>> packMonsters;
        for (i = 0; i < packSize; ++i) {
            string curMonster;
            packInput >> curMonster;
            if (monsterFactory.find(curMonster) != monsterFactory.end()) {
                packMonsters.push_back(monsterFactory.at(curMonster)());
            }
            else if (curMonster == "Pack") {
                packMonsters.push_back(packFactory(packInput));
            }
            else {
                break;
            }
        }
        if (i == packSize) {
            return std::make_unique<Pack>(packMonsters);
        }
    }
    throw InvalidEventInput();
}
