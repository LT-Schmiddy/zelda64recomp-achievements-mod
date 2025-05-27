#include "modding.h"
#include "global.h"
#include "PR/gs2dex.h"
#include "sys_cfb.h"
#include "sys_cmpdma.h"
#include "sys_ucode.h"
#include "z64lifemeter.h"
#include "zelda_arena.h"
#include "z64snap.h"
#include "z64view.h"
#include "z64voice.h"
#include "attributes.h"

#include "assets/archives/icon_item_static/icon_item_static_yar.h"
#include "assets/interface/parameter_static/parameter_static.h"
#include "assets/interface/do_action_static/do_action_static.h"
#include "assets/misc/story_static/story_static.h"

#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"
#include "overlays/actors/ovl_En_Mm3/z_en_mm3.h"

#include "../achievement_list.h"
#include "../mod_main.h"

RECOMP_HOOK("Item_Give") void pre_Item_Give(PlayState* play, u8 item) {
    if ((item >= ITEM_RUPEE_GREEN) && (item <= ITEM_RUPEE_HUGE)) {
        Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_ocarina", gSaveContext.fileNum, 1);
    }
}