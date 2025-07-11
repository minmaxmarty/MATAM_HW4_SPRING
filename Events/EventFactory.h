#pragma once

#include "Event.h"
#include "AbstractFactory.h"
#include <string>

using std::string;

class EventFactory final : public AbstractFactory<Event>
{
    public:
    EventFactory();

    //create with optional monster
    std::unique_ptr<Event> createWithMonster(const string &eventName, std::unique_ptr<Monster> monster = nullptr) const;
};
