#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#include "achievements.h"


RECOMP_CALLBACK("*", recomp_on_init) void load_lib () {
    Achievement test[] = { 
        {
            "test_achievement",
            "Test Achievement",
            "An achievement for testing.",
            NULL,
            0,
            NULL,
            NULL
        }
    };


}