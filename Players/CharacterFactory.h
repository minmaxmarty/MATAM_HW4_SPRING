#pragma once

#include "../Events/AbstractFactory.h"
#include "Character.h"

class CharacterFactory final : public AbstractFactory<Character> {
public:
    CharacterFactory();
};