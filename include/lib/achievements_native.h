#ifndef __ACHIEVEMENTS_NATIVE__
#define __ACHIEVEMENTS_NATIVE__

// #ifdef COMBINED_INTELLISENSE
// #undef MIPS
// #else 
// #endif

// #ifdef MIPS
#include "modding.h"
RECOMP_IMPORT(".", void AchievementNative_Init());
RECOMP_IMPORT(".", void AchievementNative_Declare(Achievement* achievement));
RECOMP_IMPORT(".", void AchievementNative_SetBooleanFlag(const char* achievement_id, ACH_U32 value));
// #endif

#endif