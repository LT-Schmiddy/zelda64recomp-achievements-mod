#include <filesystem>
#include <iostream>
#include <string>
#include <bit>
#include <map>
#include <string.h>

#include "plog/Log.h"
#include "plog/Init.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Initializers/ConsoleInitializer.h"
#include "achievements.h"

#include "sqlite3.h"
#include "lib_recomp.hpp"

#include "./ach_data/AchievementController.hpp"

 
extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
    
}

std::shared_ptr<AchievementController> controller = NULL;



RECOMP_DLL_FUNC(AchievementLib_Init) {
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init((plog::Severity)RECOMP_ARG(unsigned int, 0), &consoleAppender);

    unsigned int number_of_slots = RECOMP_ARG(unsigned int, 1);
    fs::path savepath = fs::path(RECOMP_ARG_U8STR(2));
    controller = std::make_shared<AchievementController>(rdram, number_of_slots, savepath);
}

RECOMP_DLL_FUNC(AchievementLib_Declare) {
    std::string ach_set = RECOMP_ARG_STR(0);
    Achievement* achievement = RECOMP_ARG(Achievement*, 1);
    controller->setRdram(rdram);
    controller->declareAchievement(ach_set, achievement);
    PLOGV.printf("Achievement ID: %s\n", ptr_to_string(rdram, (PTR(const char*))achievement->id).c_str());

}

RECOMP_DLL_FUNC(AchievementLib_SetBooleanFlag) {
    std::string achievement_id = RECOMP_ARG_STR(0);
    bool value = RECOMP_ARG(bool, 1);

    PLOGI.printf("Set Achievement '%s' to %i\n", achievement_id.c_str(), value);
}
