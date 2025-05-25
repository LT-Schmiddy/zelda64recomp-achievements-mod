#ifndef __ACHIEVEMENTS_UI__
#define __ACHIEVEMENTS_UI__

#include "recompui.h"
#include "recompui_event_structs.h"
#include "menu_helpers.h"

typedef struct {
    bool constructed;
    bool visible;
    bool _toggled_visible;
    RecompuiContext context;
    UiFrame frame;
    RecompuiResource header;
    RecompuiResource headerLabel;
    RecompuiResource body;
    RecompuiResource closeButton;

} AchievementMenu;

extern AchievementMenu achievementMenu;

void AchievementsMenu_Init();
void AchievementsMenu_Construct();
#endif