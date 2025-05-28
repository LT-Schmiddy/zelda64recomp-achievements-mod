#include "modding.h"
#include "global.h"

#include "../achievement_list.h"
#include "../mod_main.h"

RECOMP_HOOK_RETURN("func_80A0B35C") void post_yoseizo_give() {
    if (gSaveContext.save.saveInfo.playerData.isMagicAcquired) {
        Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_magic", gSaveContext.fileNum, 1);
    }
    if (gSaveContext.save.saveInfo.playerData.isDoubleMagicAcquired) {
        Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_magic_double", gSaveContext.fileNum, 1);
    }
    if (gSaveContext.save.saveInfo.playerData.doubleDefense) {
        Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_magic_double", gSaveContext.fileNum, 1);
    }
}