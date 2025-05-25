#include "input_handling.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "sys_cmpdma.h"
#include "rt64_extended_gbi.h"
#include "recompconfig.h"
#include "recomputils.h"
#include "z64item.h"
#include "z64interface.h"
#include "kaleido_manager.h"
#include "macros.h"
#include "variables.h"
#include "functions.h"
#include "z64player.h"

BtnState BtnStateCUp;

void BtnState_Record( Input* input, BtnState* state, u16 btn, bool should_mask) {
    state->cur = input->cur.button & btn;
    state->prev = input->prev.button & btn;
    state->press = input->press.button & btn;
    state->rel = input->rel.button & btn;

    if (should_mask) {
        input->cur.button &= ~btn;
        input->prev.button &= ~btn;
        input->press.button &= ~btn;
        input->rel.button &= ~btn;
    }

    if (state->press) {
        recomp_printf("BtnStateCUp Pressed\n");
    }
}

RECOMP_CALLBACK("*", recomp_on_play_main) void update_inputs(PlayState* play) {
    
    // Capture input:
    BtnState_Record(CONTROLLER1((GameState*)play), &BtnStateCUp, BTN_CUP, false);
}
