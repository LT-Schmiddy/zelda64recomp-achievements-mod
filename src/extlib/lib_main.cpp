#include <filesystem>
#include <string>

#include "sqlite3.h"
#include "lib_recomp.hpp"

extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
}

RECOMP_DLL_FUNC(test_func) {
    RECOMP_RETURN(u32, 6);
}