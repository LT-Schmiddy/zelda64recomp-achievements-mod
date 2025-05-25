#ifndef __INPUT_HANDLING__
#define __INPUT_HANDLING__

#include "modding.h"
#include "global.h"

typedef struct {
    bool cur;
    bool prev;
    bool press;
    bool rel;
} BtnState;


extern BtnState BtnStateCUp;



#endif