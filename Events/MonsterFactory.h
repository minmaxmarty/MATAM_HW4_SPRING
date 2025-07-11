#pragma once

#include "AbstractFactory.h"
#include "Monster.h"

class MonsterFactory final : public AbstractFactory<Monster> {

public:
    MonsterFactory();

    static std::unique_ptr<Pack> getEmptyPack() ;
};
