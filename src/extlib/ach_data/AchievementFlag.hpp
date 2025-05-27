#pragma once

#include <string>
#include <unordered_map>
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

    void addDependentAchievement(std::shared_ptr<AchievementWrapper> ach);

    void loadFlagFromDb(int slot);
    void saveFlagToDb(int slot);

    
private:
    AchievementController* controller = NULL;
    std::string ach_set;
    Achievement* achievement = NULL;
    AchievementFlagDefinition* flag = NULL;

    size_t data_size = 0;
    unsigned char** data = NULL;

    std::unordered_map<std::string,std::shared_ptr<AchievementWrapper>> dependend_achievements;

};