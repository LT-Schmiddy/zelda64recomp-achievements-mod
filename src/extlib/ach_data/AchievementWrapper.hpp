#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "lib_recomp.hpp"
#include "achievements.h"

class AchievementController;
class AchievementFlag;

class AchievementWrapper {
public:
    AchievementWrapper(AchievementController* p_controller, std::string p_ach_set, Achievement* p_achievement);
    ~AchievementWrapper();

    std::string getId();
    std::string getDisplayName();
    std::string getDescription();

    void addRequiredFlag(std::shared_ptr<AchievementFlag> flag);
    void updateUnlock(unsigned int slot);

private:

    AchievementController* controller = NULL;
    std::string ach_set;
    Achievement* achievement = NULL;

    std::unordered_map<std::string, std::shared_ptr<AchievementFlag>> required_flags;
};