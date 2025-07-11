#include "CharacterFactory.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

CharacterFactory::CharacterFactory() {

    // register Characters

    this->registerItem("Responsible", []() -> std::unique_ptr<Character> {
        return std::make_unique<Responsible>();
    });

    this->registerItem("RiskTaking", []() -> std::unique_ptr<Character> {
        return std::make_unique<RiskTaking>();
    });

}