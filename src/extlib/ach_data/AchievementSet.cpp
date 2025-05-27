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
    printf("Adding achievement to set %s...\n", ach_set.c_str());

    // Create the default flag for the achievement:
    std::shared_ptr<AchievementFlag> new_flag = std::make_shared<AchievementFlag>(controller, ach_set, achievement);
    auto flag_pair = std::pair<std::string, std::shared_ptr<AchievementFlag>>(new_flag->getId(), new_flag);
    flags.insert(flag_pair);

    // Create the achievement wrapper:
    std::shared_ptr<AchievementWrapper> new_ach = std::make_shared<AchievementWrapper>(controller, ach_set, achievement);
    auto ach_pair = std::pair<std::string, std::shared_ptr<AchievementWrapper>>(new_ach->getId(), new_ach);
    achievments.insert(ach_pair);

    // Link 'em together:
    new_flag->addDependentAchievement(new_ach);
    new_ach->addRequiredFlag(new_flag); // TODO: handle additional flags... once those are implemented.
}