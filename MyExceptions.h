//
// Created by areg1 on 6/30/2025.
//

#pragma once
#include <stdexcept>

using std::string;

static const string DEFAULT_PLAYER_ERROR_MSG = "Invalid Players File";
static const string DEFAULT_EVENT_ERROR_MSG = "Invalid Events File";
static const string DEFAULT_MONSTER_ERROR_MSG = "Invalid Monster Input";

class InvalidPlayerInput : public std::runtime_error {
public:
    explicit InvalidPlayerInput(const string& message = DEFAULT_PLAYER_ERROR_MSG) : std::runtime_error(message) {}
};

class InvalidEventInput : public std::runtime_error {
public:
    explicit InvalidEventInput(const string& message = DEFAULT_EVENT_ERROR_MSG) : std::runtime_error(message) {}
};

class InvalidMonsterInput : public std::runtime_error {
public:
    explicit InvalidMonsterInput(const string& message = DEFAULT_MONSTER_ERROR_MSG) : std::runtime_error(message) {}
};


