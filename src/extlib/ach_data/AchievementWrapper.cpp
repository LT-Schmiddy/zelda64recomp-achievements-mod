#include "AchievementWrapper.hpp"

#include "AchievementController.hpp"


AchievementWrapper::AchievementWrapper(AchievementController* p_controller, std::string p_ach_set, Achievement* p_achievement) {
    controller = p_controller;
    ach_set = p_ach_set;
    achievement = p_achievement;
}

AchievementWrapper::~AchievementWrapper(){}

std::string AchievementWrapper::getId(){
    return ptr_to_string(controller->getRdram(), (int32_t)achievement->id);
}
std::string AchievementWrapper::getDisplayName(){
    return ptr_to_string(controller->getRdram(), (int32_t)achievement->display_name);
}
std::string AchievementWrapper::getDescription(){
    return ptr_to_string(controller->getRdram(), (int32_t)achievement->description);
}