#pragma once

#include <string>
#include <vector>
#include <memory>
#include "lib_recomp.hpp"
#include "achievements.h"

class AchievementController;
class AchievementWrapper;

class AchievementFlag {
public:
    AchievementFlag(AchievementController* p_controller, std::string p_ach_set, Achievement* p_achievement);
    ~AchievementFlag();
    std::string getId();
    AchievementFlagType getType();
private:
    AchievementController* controller = NULL;
    std::string ach_set;
    Achievement* achievement = NULL;
    AchievementFlagDefinition* flag = NULL;
    std::vector<std::shared_ptr<AchievementWrapper>> used_by_achievements;

};