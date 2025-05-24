#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "achievements.h"


Achievement gAchievements[] = { 
    {
        "test_achievement",
        "Test Achievement",
        "An achievement for testing.",
        NULL,
        10,
        NULL,
        {
            10
        },
        NULL
    }
};

RECOMP_IMPORT(".", void load_achievement(Achievement* achievement))

RECOMP_CALLBACK("*", recomp_on_init) void load_lib () {
    recomp_printf("Achievement SIZE MOD: %lu\n", sizeof(Achievement));
    recomp_printf("ICON SIZE MOD: %i\n", gAchievements[0].icon_size);
    load_achievement(&gAchievements[0]);

}