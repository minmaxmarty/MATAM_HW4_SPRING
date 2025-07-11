#pragma once
#include <memory>
#include "PlayerFactory.h"
#include "MonsterFactory.h"
#include "EventFactory.h"

using std::unique_ptr;
using std::vector;

class StreamAdapter {
    private:
    unique_ptr<PlayerFactory> playerFactory;
    unique_ptr<MonsterFactory> monsterFactory;
    unique_ptr<EventFactory> eventFactory;

    unique_ptr<Player> getPlayerFromLine(const string& line) const;

    unique_ptr<Encounter> buildPackEvent(std::istream &eventStream) const;
    unique_ptr<Pack> buildPackRecursive(std::istream &eventStream) const;

    public:
    StreamAdapter();
    ~StreamAdapter() = default;

    vector<unique_ptr<Player>> getPlayersViaStream(std::istream& playerStream) const;
    vector<unique_ptr<Event>> getEventsViaStream(std::istream& eventStream) const;
};
