#include "mod_main.h"

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "achievements_ui.h"
#include "achievement_list.h"


RECOMP_CALLBACK("*", recomp_on_init) void load_lib () {
    u32 count = GetAchievementCount();
    recomp_printf("NUMBER OF ACHIEVEMENTS: %i\n", count);
    char* savepath = recomp_get_save_file_path();
    AchievementLib_Init(savepath);
    recomp_free(savepath);
    // Recomp argument helpers don't support double pointers.
    // Passing achievements over one at a time for now.
    for (u32 i = 0; i < count; i++){
        AchievementLib_Declare(ACHIEVEMENT_SET_ID, &gAchievements[i]);
    }

    AchievementsMenu_Init();
    AchievementsMenu_Construct();

}