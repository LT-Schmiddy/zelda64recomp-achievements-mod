#include "modding.h"
#include "recomputils.h"
#include "z64save.h"
#include "global.h"

#include "sys_flashrom.h"
#include "z64horse.h"
#include "overlays/gamestates/ovl_file_choose/z_file_select.h"

#include "achievements.h"

#define SAVE_TYPE_AUTOSAVE 2 

RECOMP_HOOK("Sram_EraseSave") void pre_Sram_EraseSave(FileSelectState* fileSelect2, SramContext* sramCtx, s32 fileNum) {

}

RECOMP_HOOK("Sram_CopySave") void pre_Sram_CopySave(FileSelectState* fileSelect2, SramContext* sramCtx) {
    FileSelectState* fileSelect = fileSelect2;

}




RECOMP_CALLBACK("*", recomp_on_load_save) void load_achiement_flags() {
    if (gSaveContext.save.isOwlSave == 0) {
        AchievementNative_RevertDiskToSOTState(gSaveContext.fileNum);
    }

    AchievementNative_ReadFlagsFromDisk(gSaveContext.fileNum);
}

// This is a completely cursed way to check run on an autosave.
RECOMP_HOOK("Lib_MemCpy") void save_achiement_flags_autosave() {
    if (gSaveContext.save.isOwlSave != SAVE_TYPE_AUTOSAVE) {return;}
    recomp_printf("Should be autosaving...\n");

    AchievementNative_WriteFlagsToDisk(gSaveContext.fileNum);
}

RECOMP_CALLBACK("*", recomp_on_owl_save) void save_achiement_flags_owl() {
    AchievementNative_WriteFlagsToDisk(gSaveContext.fileNum);
}

RECOMP_HOOK_RETURN("Sram_SaveEndOfCycle") void save_quickBottle_SOT() {
    AchievementNative_WriteFlagsToDisk(gSaveContext.fileNum);
    AchievementNative_MakeDiskSOTState(gSaveContext.fileNum);
}

RECOMP_CALLBACK("*", recomp_on_moon_crash) void revert_achiement_flags_mooncrash() {
    AchievementNative_RevertDiskToSOTState(gSaveContext.fileNum);
    AchievementNative_ReadFlagsFromDisk(gSaveContext.fileNum);
}

