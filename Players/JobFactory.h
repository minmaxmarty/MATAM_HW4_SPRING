#pragma once

#include "../Events/AbstractFactory.h"
#include "Job.h"

class JobFactory final : public AbstractFactory<Job> {
public:
    JobFactory();
};
