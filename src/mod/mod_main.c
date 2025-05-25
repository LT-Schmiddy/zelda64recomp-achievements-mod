#include "mod_main.h"

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "achievements_ui.h"
#include "achievement_list.h"


RECOMP_CALLBACK("*", recomp_on_init) void load_lib () {
    recomp_printf("NUMBER OF ACHIEVEMENTS: %i\n");
    u32 count = GetAchievementCount();

    AchievementLib_Init();

    // Recomp argument helpers don't support double pointers.
    // Passing achievements over one at a time for now.
    for (u32 i = 0; i < count; i++){
        AchievementLib_Declare(&gAchievements[i]);
    }

    AchievementsMenu_Init();
    AchievementsMenu_Construct();

}