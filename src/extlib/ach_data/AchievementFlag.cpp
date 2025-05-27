#include "AchievementFlag.hpp"
#include "AchievementController.hpp"

AchievementFlag::AchievementFlag(AchievementController* p_controller, std::string p_ach_set, Achievement* p_achievement) {
    controller = p_controller;
    ach_set = p_ach_set;
    achievement = p_achievement;

    if (!controller->hasFlag(ach_set, getId(), controller->getCurrentSlot())){
        int value = 0;
        controller->setFlag(ach_set, getId(), controller->getCurrentSlot(), sizeof(int), &value);
    }
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

