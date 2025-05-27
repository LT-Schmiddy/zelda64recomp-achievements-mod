#include "AchievementFlag.hpp"
#include "AchievementController.hpp"
#include "AchievementWrapper.hpp"

AchievementFlag::AchievementFlag(AchievementController* p_controller, std::string p_ach_set, Achievement* p_achievement) {
    controller = p_controller;
    ach_set = p_ach_set;
    achievement = p_achievement;
}


AchievementFlag::~AchievementFlag() {}

std::string AchievementFlag::getId() {
    uint8_t* rdram = controller->getRdram();
    if (achievement != NULL) {
        return ptr_to_string(controller->getRdram(), (int32_t)achievement->id);
    }

    else if (flag != NULL) {
        return ptr_to_string(controller->getRdram(), (int32_t)flag->id);
    }
    throw std::runtime_error("AchievementFlag::achievement and AchievementFlag::flag cannot both be null!");
}

AchievementFlagType AchievementFlag::getType() {
    if (flag == NULL) {
        return ACHIEVEMENT_FLAG_BOOLEAN;
    }
    return flag->type;
}

void AchievementFlag::addDependentAchievement(std::shared_ptr<AchievementWrapper> ach) {
    auto pair = std::pair<std::string, std::shared_ptr<AchievementWrapper>>(ach->getId(), ach);

    dependend_achievements.insert(pair);
    printf("Achievement %s now depends on flag %s\n", ach->getId().c_str(), this->getId().c_str());
}

