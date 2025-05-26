#include <filesystem>
#include <iostream>
#include <string>
#include <bit>
#include <string.h>
#include "achievements.h"

#include "sqlite3.h"
#include "lib_recomp.hpp"

 
extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
    
}


uint8_t* recomp_rdram = NULL;

RECOMP_DLL_FUNC(AchievementNative_Init) {
    recomp_rdram = rdram;
}

RECOMP_DLL_FUNC(AchievementNative_Declare) {
    Achievement* achievement = RECOMP_ARG(Achievement*, 0);

    printf("Achievement ID: %s\n", ptr_to_string(rdram, (PTR(const char*))achievement->id).c_str());
}

RECOMP_DLL_FUNC(AchievementNative_SetBooleanFlag) {
    std::string achievement_id = RECOMP_ARG_STR(0);
    bool value = RECOMP_ARG(bool, 1);

    printf("Set Achievement '%s' to %i\n", achievement_id.c_str(), value);
}
