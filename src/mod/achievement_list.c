#include "achievement_list.h"


Achievement gAchievements[] = { 
    {
        "test_achievement",
        "Test Achievement",
        "An achievement for testing.",
        NULL,
        0,
        NULL,
        {
            0
        },
        NULL
    }
};

u32 GetAchievementCount() {
    return ARRAY_COUNT(gAchievements);
}