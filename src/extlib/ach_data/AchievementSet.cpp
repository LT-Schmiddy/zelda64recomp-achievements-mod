#include "AchievementSet.hpp"

#include "AchievementFlag.hpp"
#include "AchievementWrapper.hpp"
#include "AchievementController.hpp"

AchievementSet::AchievementSet(AchievementController* p_controller, std::string p_ach_set) {
    controller = p_controller;
    ach_set = p_ach_set;
}

AchievementSet::~AchievementSet(){}