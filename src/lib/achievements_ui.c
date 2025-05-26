#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "achievements.h"


// #include "input_handling.h"
#include "achievements_ui.h"

AchievementMenu achievementMenu;

void AchievementsMenu_Init() {
    achievementMenu.constructed = false;
    achievementMenu.visible = false;    
}


void AchievementsMenu_SetVisible(bool visible){
    achievementMenu.visible = visible;
    achievementMenu._toggled_visible = true;
}

void AchievementsMenu_CloseCallback(RecompuiResource button, const RecompuiEventData* data, void* userdata) {
    AchievementsMenu_SetVisible(false);
}

void AchievementsMenu_Construct() {
    // Construct Menu Here:
    RecompuiColor bg_color;
    bg_color.r = 255;
    bg_color.g = 255;
    bg_color.b = 255;
    bg_color.a = 0.5f * 255;

    RecompuiColor border_color;
    border_color.r = 255;
    border_color.g = 255;
    border_color.b = 255;
    border_color.a = 0.7f * 255;

    RecompuiColor modal_color;
    modal_color.r = 8;
    modal_color.g = 7;
    modal_color.b = 13;
    modal_color.a = 0.9f * 255;

    const float body_padding = 64.0f;
    const float modal_height = RECOMPUI_TOTAL_HEIGHT - (2 * body_padding);
    const float modal_max_width = modal_height * (16.0f / 9.0f);
    const float modal_border_width = 5.1f;
    const float modal_border_radius = 16.0f;

    achievementMenu.context = recompui_create_context();
    recompui_open_context(achievementMenu.context);
    createUiFrame(achievementMenu.context, &achievementMenu.frame);
    // Adjust the container's properties.
    recompui_set_width(achievementMenu.frame.container, 1200.0f, UNIT_DP);
    recompui_set_height(achievementMenu.frame.container, 800.0f, UNIT_DP);
    recompui_set_display(achievementMenu.frame.container, DISPLAY_FLEX);
    recompui_set_flex_direction(achievementMenu.frame.container, FLEX_DIRECTION_COLUMN);
    recompui_set_align_items(achievementMenu.frame.container, ALIGN_ITEMS_STRETCH);
    recompui_set_justify_content(achievementMenu.frame.container, JUSTIFY_CONTENT_FLEX_START);

    // Remove the padding on the frame's container so that the divider line has the full width of the container.
    recompui_set_padding(achievementMenu.frame.container, 0.0f, UNIT_DP);

    // Create the header.
    achievementMenu.header = recompui_create_element(achievementMenu.context, achievementMenu.frame.container);
    recompui_set_flex_grow(achievementMenu.header, 0.0f);
    recompui_set_flex_shrink(achievementMenu.header, 0.0f);
    recompui_set_display(achievementMenu.header, DISPLAY_FLEX);
    recompui_set_flex_direction(achievementMenu.header, FLEX_DIRECTION_ROW);
    recompui_set_justify_content(achievementMenu.header, JUSTIFY_CONTENT_SPACE_BETWEEN);
    recompui_set_border_bottom_width(achievementMenu.header, 1.1f, UNIT_DP);
    recompui_set_height_auto(achievementMenu.header);
    recompui_set_padding(achievementMenu.header, 16.0f, UNIT_DP);
    recompui_set_align_items(achievementMenu.header, ALIGN_ITEMS_CENTER);

    RecompuiColor divider_color;
    divider_color.r = 255;
    divider_color.g = 255;
    divider_color.b = 255;
    divider_color.a = 25;
    recompui_set_border_bottom_color(achievementMenu.header, &divider_color);

    achievementMenu.headerLabel = recompui_create_label(achievementMenu.context, achievementMenu.header, "Achievements", LABELSTYLE_LARGE);
    achievementMenu.closeButton = recompui_create_button(achievementMenu.context, achievementMenu.header, "Generate", BUTTONSTYLE_PRIMARY);
    recompui_register_callback(achievementMenu.closeButton, AchievementsMenu_CloseCallback, NULL);


    recompui_set_text_align(achievementMenu.headerLabel, TEXT_ALIGN_CENTER);
    recompui_set_margin_left(achievementMenu.headerLabel, 32.0f, UNIT_DP);

    // Create the body.
    achievementMenu.body = recompui_create_element(achievementMenu.context, achievementMenu.frame.container);
    recompui_set_display(achievementMenu.body, DISPLAY_BLOCK);
    recompui_set_overflow_y(achievementMenu.body, OVERFLOW_SCROLL);
    recompui_close_context(achievementMenu.context);
    
    achievementMenu.constructed = true;
}

// RECOMP_HOOK("KaleidoScope_DrawQuestStatus") void pre_KaleidoScope_DrawQuestStatus(PlayState* play) {
//     PauseContext* pauseCtx = &play->pauseCtx;

//     if (pauseCtx->pageIndex == PAUSE_QUEST && BtnStateCUp.press) {

//         AchievementsMenu_SetVisible(!achievementMenu.visible);

//         recomp_printf("achievementMenu.visible = %i\n", achievementMenu.visible);
//     }

//     if (achievementMenu._toggled_visible) {
//         if (achievementMenu.visible) {
//             recompui_show_context(achievementMenu.context);
//         }
//         else {
//             recompui_hide_context(achievementMenu.context);
//         }
//         achievementMenu._toggled_visible = false;
//     }
// }