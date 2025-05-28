
#include "plog/Log.h"

#include "AchievementWrapper.hpp"

#include "AchievementFlag.hpp"
#include "AchievementController.hpp"


AchievementWrapper::AchievementWrapper(AchievementController* p_controller, std::string p_ach_set, PTR(Achievement) p_achievement) {
    controller = p_controller;
    ach_set = p_ach_set;
    recomp_address = p_achievement;
}

AchievementWrapper::~AchievementWrapper(){}

std::string AchievementWrapper::getId(){
    return ptr_to_string(controller->getRdram(), (int32_t)getNativePtr()->id);
}
std::string AchievementWrapper::getDisplayName(){
    return ptr_to_string(controller->getRdram(), (int32_t)getNativePtr()->display_name);
}
std::string AchievementWrapper::getDescription(){
    return ptr_to_string(controller->getRdram(), (int32_t)getNativePtr()->description);
}

void AchievementWrapper::addRequiredFlag(std::shared_ptr<AchievementFlag> flag) {
    auto flag_pair = std::pair<std::string, std::shared_ptr<AchievementFlag>>(flag->getId(), flag);
    required_flags.insert(flag_pair);
}

void AchievementWrapper::updateUnlock(unsigned int slot) {
    PLOGI.printf("Updating achievement %s on slot %i", getId().c_str(), slot);
    if (recomp_address == 0) {
        bool unlocked = standardIsUnlocked(slot);
    }
}

bool AchievementWrapper::standardIsUnlocked(unsigned int slot) {
    unsigned int retVal = 1;

    // We'll just assess the truthiness of all flags.
    for (auto iter: required_flags) {
        AchievementFlagType flag_type = iter.second->getType();

        if (flag_type == ACHIEVEMENT_FLAG_UNSIGNED_INT) {
            unsigned int value;
            iter.second->getValue(slot, &value);

            retVal = retVal && value;
        }

        if (flag_type == ACHIEVEMENT_FLAG_SIGNED_INT) {
            int value;
            iter.second->getValue(slot, &value);

            retVal = retVal && value;
        }

        if (flag_type == ACHIEVEMENT_FLAG_FLOAT) {
            float value;
            iter.second->getValue(slot, &value);

            retVal = retVal && value;
        }
    }

    return retVal;
}

Achievement* AchievementWrapper::getNativePtr() {
    uint8_t* rdram = controller->getRdram();
    return TO_PTR(Achievement, recomp_address);
}