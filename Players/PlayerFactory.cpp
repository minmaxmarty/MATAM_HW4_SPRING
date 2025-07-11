#include "PlayerFactory.h"
#include "Player.h"
#include <memory>
#include <stdexcept>

PlayerFactory::PlayerFactory()= default;

unique_ptr<Player> PlayerFactory::create(const string &name, const string &jobName, const string &characterName) const
{

    unique_ptr<Job> newJob = this->jobs.create(jobName);
    unique_ptr<Character> newCharacter = this->characters.create(characterName);

    if (!newJob)
    {
        throw std::runtime_error("Job Not Found");
    }
    if (!newCharacter)
    {
        throw std::runtime_error("Character Not Found");
    }
    // both exist
    return std::make_unique<Player>(name, newJob, newCharacter);
};
