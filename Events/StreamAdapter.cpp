#include "StreamAdapter.h"
#include <iostream>
#include <string>
#include <../Utilities.h>
#include <vector>

using std::string;
using std::isspace;
using std::vector;
using std::getline;

StreamAdapter::StreamAdapter() {
    this->playerFactory = std::make_unique<PlayerFactory>();
    this->monsterFactory = std::make_unique<MonsterFactory>();
    this->eventFactory = std::make_unique<EventFactory>();
}

vector<unique_ptr<Player> > StreamAdapter::getPlayersViaStream(std::istream &playerStream) const {
    try {
        vector<unique_ptr<Player> > players;
        string name, job, character;
        while (playerStream >> name) {
            //check name size
            int nameSize = name.size();
            if (nameSize < 3) {
                throw std::invalid_argument("Player name is too short");
            }
            if (nameSize > 15) {
                throw std::invalid_argument("Player name is too long");
            }
            // check characters of name
            for ( char c : name) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("Player has an invalid character");
                }
            }
            // get job and character
            playerStream >> job >> character;
            auto newPlayer = this->playerFactory->create(name, job, character);
            players.push_back(std::move(newPlayer));
            //reset name,job,character
            name = job = character = "";
        }
        // enforce max and min players size
        if (players.size() < 2 || players.size() > 6) {
            throw std::invalid_argument("Invalid player count");
        }
        return players;
    } catch (...) {
        throw std::invalid_argument("Invalid Players File");
    }
}

vector<unique_ptr<Event> > StreamAdapter::getEventsViaStream(std::istream &eventStream) const {
    try {
        vector<unique_ptr<Event> > events;
        string currEventString;
        //iterate over playerStream line by line
        while (!eventStream.eof()) {
            eventStream >> currEventString;

            if (currEventString == "Pack") {
                //Pack handle
                unique_ptr<Encounter> packEvent = this->buildPackEvent(eventStream);
                events.push_back(std::move(packEvent));
            } else {
                // normal handle
                events.push_back(std::move(this->eventFactory->create(currEventString)));
            }
        }
        //must be at least 2 events
        if (events.size() < 2) {
            throw std::invalid_argument("not enough events");
        }
        return events;
    } catch (...) {
        throw std::invalid_argument("Invalid Events File");
    }
}

unique_ptr<Encounter> StreamAdapter::buildPackEvent(std::istream &eventStream) const {
    try {
        unique_ptr<Encounter> packEvent = std::make_unique<Encounter>();
        packEvent->setMonster(this->buildPackRecursive(eventStream));
        return packEvent;
    } catch (std::exception &e) {
        throw e;
    }
}

unique_ptr<Pack> StreamAdapter::buildPackRecursive(std::istream &eventStream) const {

    //throw error if called on empty stream
    if (eventStream.eof()) {
        throw std::invalid_argument("Event stream is empty");
    }
    unique_ptr<Pack> packHead;
    try {
        // first string will be size of pack
        string rawPackSize;
        eventStream >> rawPackSize;
        //convert to int
        //check that rawPacKSize is explicitly int
        if (rawPackSize.find('.')!=string::npos) {
            throw std::invalid_argument("Invalid Pack Size");
        }
        int size = std::stoi(rawPackSize);

        if (size < 2) {
            throw std::invalid_argument("Invalid Pack Size");
        }

        //init pack head
        packHead = MonsterFactory::getEmptyPack();

        string rawInput;
        for (int i = 0; i < size; i++) {
            if (eventStream.eof()) {
                throw std::out_of_range("Monster size is longer than amount of monsters");
            }
            // get next string
            eventStream >> rawInput;
            if (rawInput == "Pack") {
                // add pack recursively
                packHead->addMonster(this->buildPackRecursive(eventStream));
            } else {
                // add regular monster
                packHead->addMonster(this->monsterFactory->create(rawInput));
            }
        }
    } catch (std::exception &e) {
        throw e;
    }
    return packHead;
}
