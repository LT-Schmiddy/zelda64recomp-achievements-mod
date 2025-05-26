#include <filesystem>
#include <iostream>
#include <string>
#include <bit>
#include <map>
#include <string.h>
#include "achievements.h"

#include "sqlite3.h"
#include "lib_recomp.hpp"

#include "AchievementWrapper.hpp"

 
extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
    
}

std::map<std::string, AchievementWrapper> achievement_wrappers;

uint8_t* recomp_rdram = NULL;

RECOMP_DLL_FUNC(AchievementLib_Init) {
    recomp_rdram = rdram;
}

RECOMP_DLL_FUNC(AchievementLib_Declare) {
    Achievement* achievement = RECOMP_ARG(Achievement*, 0);

    printf("Achievement ID: %s\n", ptr_to_string(rdram, (PTR(const char*))achievement->id).c_str());
    AchievementWrapper wrapper(rdram, achievement);
    achievement_wrappers.insert(std::pair<std::string,AchievementWrapper>(wrapper.getId(), wrapper));

    printf("Total Achievements = %zu\n", achievement_wrappers.size());
}

RECOMP_DLL_FUNC(AchievementLib_SetBooleanFlag) {
    std::string achievement_id = RECOMP_ARG_STR(0);
    bool value = RECOMP_ARG(bool, 1);

    printf("Set Achievement '%s' to %i\n", achievement_id.c_str(), value);
}
