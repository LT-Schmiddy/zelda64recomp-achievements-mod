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
    switch (item) {
        // Item Screen
        case ITEM_OCARINA_OF_TIME:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_ocarina", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOW:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bow", gSaveContext.fileNum, 1);
            break;
        case ITEM_QUIVER_40:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bow_upgrade_40", gSaveContext.fileNum, 1);
            break;
        case ITEM_QUIVER_50:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bow_upgrade_50", gSaveContext.fileNum, 1);
            break;
        case ITEM_ARROW_FIRE:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_fire_arrow", gSaveContext.fileNum, 1);
            break;
        case ITEM_ARROW_ICE:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_ice_arrow", gSaveContext.fileNum, 1);
            break;
        case ITEM_ARROW_LIGHT:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_light_arrow", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOMB_BAG_20:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bomb_bag", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOMB_BAG_30:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bomb_bag_upgrade_30", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOMB_BAG_40:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bomb_bag_upgrade_40", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOMBCHU:
        case ITEM_BOMBCHUS_20:
        case ITEM_BOMBCHUS_10:
        case ITEM_BOMBCHUS_5:
        case ITEM_BOMBCHUS_1:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bombchus", gSaveContext.fileNum, 1);
            break;
        case ITEM_DEKU_STICK:
        case ITEM_DEKU_STICKS_5:
        case ITEM_DEKU_STICKS_10:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_sticks", gSaveContext.fileNum, 1);
            break;
        case ITEM_DEKU_NUT:
        case ITEM_DEKU_NUTS_5:
        case ITEM_DEKU_NUTS_10:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_nuts", gSaveContext.fileNum, 1);
            break;
        case ITEM_MAGIC_BEANS:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_magic_beans", gSaveContext.fileNum, 1);
            break;
        case ITEM_POWDER_KEG:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_powder_keg", gSaveContext.fileNum, 1);
            break;
        case ITEM_PICTOGRAPH_BOX:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_pictobox", gSaveContext.fileNum, 1);
            break;
        case ITEM_LENS_OF_TRUTH:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_lens_of_truth", gSaveContext.fileNum, 1);
            break;
        case ITEM_HOOKSHOT:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_hookshot", gSaveContext.fileNum, 1);
            break;
        case ITEM_SWORD_GREAT_FAIRY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_great_fairy_sword", gSaveContext.fileNum, 1);
            break;
        // Masks
        case ITEM_MASK_DEKU:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_deku", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_GORON:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_goron", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_ZORA:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_zora", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_FIERCE_DEITY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_fierce_diety", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_GREAT_FAIRY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_great_fairy", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_KAFEIS_MASK:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_kafei", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_BREMEN:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_bremen", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_KAMARO:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_kamaro", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_BLAST:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_blast", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_TRUTH:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_truth", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_BUNNY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_bunny_hood", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_KEATON:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_keaton", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_POSTMAN:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_postman", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_SCENTS:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_scents", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_DON_GERO:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_don_gero", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_ROMANI:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_romani", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_GARO:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_garo", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_CAPTAIN:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_captain", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_STONE:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_stone", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_CIRCUS_LEADER:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_circus_leader", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_ALL_NIGHT:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_all_night", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_GIBDO:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_gibdo", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_COUPLE:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_couple", gSaveContext.fileNum, 1);
            break;
        case ITEM_MASK_GIANT:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_mask_giant", gSaveContext.fileNum, 1);
            break;
        // Remains
        case ITEM_REMAINS_ODOLWA:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_remains_odolwa", gSaveContext.fileNum, 1);
            break;
        case ITEM_REMAINS_GOHT:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_remains_goht", gSaveContext.fileNum, 1);
            break;
        case ITEM_REMAINS_GYORG:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_remains_gyorg", gSaveContext.fileNum, 1);
            break;
        case ITEM_REMAINS_TWINMOLD:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_remains_twinmold", gSaveContext.fileNum, 1);
            break;
        // Songs
        case ITEM_SONG_EPONA:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_epona", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_SOARING:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_soaring", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_STORMS:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_storms", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_SONATA:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_sonata", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_LULLABY_INTRO:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_lullaby_intro", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_LULLABY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_lullaby", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_NOVA:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_new_wave", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_ELEGY:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_elegy", gSaveContext.fileNum, 1);
            break;
        case ITEM_SONG_OATH:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_song_oath", gSaveContext.fileNum, 1);
            break;
        // Other Quest Screen
        case ITEM_SWORD_RAZOR:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_sword_razor", gSaveContext.fileNum, 1);
            break;
        case ITEM_SWORD_GILDED:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_sword_gilded", gSaveContext.fileNum, 1);
            break;
        case ITEM_SHIELD_MIRROR:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_shield_mirror", gSaveContext.fileNum, 1);
            break;
        case ITEM_BOMBERS_NOTEBOOK:
            Achievements_SetU32Flag(ACHIEVEMENT_SET_ID, "get_bombers_notebook", gSaveContext.fileNum, 1);
            break;
        default:
            break;
    }
}