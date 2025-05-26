#include "basic_defs.h"
#include "achievements.h"
#include "achievements_native.h"

void Achievements_Init() {
    AchievementNative_Init();
}

void Achievements_DeclareSet(const char* set_name, Achievement** achievements, unsigned int count) {
    for (unsigned int i = 0; i < count; i++){
        AchievementNative_Declare(&achievements[i]);
    }
}