#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_IMPORT(".", u32 test_func());

RECOMP_CALLBACK("*", recomp_on_init) void load_lib () {
    recomp_printf("TEST_FUNC: %i\n", test_func());
}