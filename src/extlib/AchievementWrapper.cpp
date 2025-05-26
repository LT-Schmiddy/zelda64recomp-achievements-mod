#include "AchievementWrapper.hpp"


AchievementWrapper::AchievementWrapper(uint8_t* p_recomp_rdram, Achievement* p_achievement) {
    recomp_rdram = p_recomp_rdram;
    achievement = p_achievement;
}

AchievementWrapper::~AchievementWrapper(){}

std::string AchievementWrapper::getId(){
    return ptr_to_string(recomp_rdram, (int32_t)achievement->id);
}
std::string AchievementWrapper::getDisplayName(){
    return ptr_to_string(recomp_rdram, (int32_t)achievement->display_name);
}
std::string AchievementWrapper::getDescription(){
    return ptr_to_string(recomp_rdram, (int32_t)achievement->description);
}