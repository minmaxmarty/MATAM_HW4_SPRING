#include "EventFactory.h"
#include "Monster.h"
#include <string>
#include <stdexcept>

using std::string;

EventFactory::EventFactory()
{
    // add events
    registerItem("Snail", []() -> std::unique_ptr<Event> {
        return std::make_unique<Encounter>(std::make_unique<Snail>());
    });
    registerItem("Slime", []() -> std::unique_ptr<Event> {
        return std::make_unique<Encounter>(std::make_unique<Slime>());
    });
    registerItem("Balrog", []() -> std::unique_ptr<Event> {
        return std::make_unique<Encounter>(std::make_unique<Balrog>());
    });
    registerItem("Pack", []() -> std::unique_ptr<Event> {
        return std::make_unique<Encounter>(std::make_unique<Pack>());
    });
    registerItem("PotionsMerchant", []() -> std::unique_ptr<Event> {
        return std::make_unique<PotionMerchant>();
    });
    registerItem("SolarEclipse", []() -> std::unique_ptr<Event> {
        return std::make_unique<SolarEclipse>();
    });
}

std::unique_ptr<Event> EventFactory::createWithMonster(const string &eventName, std::unique_ptr<Monster> monster) const
{
    auto newEvent = this->itemCreators.find(eventName);
    if (newEvent != itemCreators.end()) {
        // get event unique ptr
        std::unique_ptr<Event> event = newEvent->second();
        if (monster){
            //check if event is Encounter using dynamic_cast
            auto encounter = dynamic_cast<Encounter*>(event.get());

            if (!encounter) {
                throw std::runtime_error("Only Encounter can receive a Monster");
            }

            encounter->setMonster(std::move(monster));
        }
        return event;
    }
    throw std::runtime_error("Event type not found: " + eventName);
}
