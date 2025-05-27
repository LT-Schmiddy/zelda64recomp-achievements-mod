#pragma once

#include <string>
#include <vector>
#include <memory>
#include "lib_recomp.hpp"
#include "achievements.h"

class AchievementWrapper;

class AchievementFlag {
public:
    AchievementFlagDefinition* flag = NULL;

    std::vector<std::shared_ptr<AchievementWrapper>> achievements;

    AchievementFlag();
    AchievementFlagType getType();
};