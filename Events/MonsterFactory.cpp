#include "MonsterFactory.h"
#include <string>
#include <memory>
#include <stdexcept>
#include <stack>

using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

MonsterFactory::MonsterFactory() {
    registerItem("Snail", []() -> unique_ptr<Monster> { return make_unique<Snail>(); });
    registerItem("Slime", []() -> unique_ptr<Monster> { return make_unique<Slime>(); });
    registerItem("Balrog", []() -> unique_ptr<Monster> { return make_unique<Balrog>(); });
    registerItem("Pack", []() -> unique_ptr<Monster> { return make_unique<Pack>(); });
}

std::unique_ptr<Pack> MonsterFactory::getEmptyPack() {
    return make_unique<Pack>();
}
