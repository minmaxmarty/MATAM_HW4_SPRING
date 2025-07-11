#pragma once

#include "Player.h"
#include <memory>
#include <map>
#include "JobFactory.h"
#include "CharacterFactory.h"

using std::map;
using std::unique_ptr;

class PlayerFactory
{
private:
    JobFactory jobs;
    CharacterFactory characters;

public:
    // ctor
    PlayerFactory();

    ~PlayerFactory() = default;

    // create player
    unique_ptr<Player> create(const string &name,const string &jobName,const string &charName) const;
};