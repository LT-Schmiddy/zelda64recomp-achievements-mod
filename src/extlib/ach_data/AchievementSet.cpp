#include <string.h>

#include "AchievementSet.hpp"

#include "AchievementFlag.hpp"
#include "AchievementWrapper.hpp"
#include "AchievementController.hpp"

AchievementSet::AchievementSet(AchievementController* p_controller, std::string p_ach_set) {
    controller = p_controller;
    ach_set = p_ach_set;
}

AchievementSet::~AchievementSet(){}

void AchievementSet::declareAchievement(Achievement* achievement) {
    printf("Adding achievement to set...\n");

    std::shared_ptr<AchievementFlag> flag = std::make_shared<AchievementFlag>(controller, ach_set, achievement);

    auto pair = std::pair<std::string, std::shared_ptr<AchievementFlag>>(flag->getId(), flag);

    flags.insert(pair);
}