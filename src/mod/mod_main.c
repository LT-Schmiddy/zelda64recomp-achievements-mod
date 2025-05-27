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
    unsigned char* savepath = recomp_get_save_file_path();
    AchievementNative_Init(recomp_get_config_u32("log_level"), 2, savepath);
    recomp_free(savepath);
    // Recomp argument helpers don't support double pointers.
    // Passing achievements over one at a time for now.
    for (u32 i = 0; i < count; i++){
        AchievementNative_Declare(ACHIEVEMENT_SET_ID, &gAchievements[i]);
    }

    AchievementsMenu_Init();
    AchievementsMenu_Construct();

}

void Achievements_SetU32Flag(const char* ach_set, const char* ach_id, u32 slot, u32 value) {
    AchievementNative_SetU32Flag(ach_set, ach_id, slot, value);
}