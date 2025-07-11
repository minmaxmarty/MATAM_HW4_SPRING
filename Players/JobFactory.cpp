#include "JobFactory.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

JobFactory::JobFactory() {

    // register Jobs

    this->registerItem("Warrior", []() -> std::unique_ptr<Job> {
        return std::make_unique<Warrior>();
    });

    this->registerItem("Archer", []() -> std::unique_ptr<Job> {
        return std::make_unique<Archer>();
    });

    this->registerItem("Magician", []() -> std::unique_ptr<Job> {
        return std::make_unique<Magician>();
    });
}