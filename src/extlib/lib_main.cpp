#include <filesystem>
#include <iostream>
#include <string>
#include <bit>
#include <string.h>


#include "achievements.h"

#include "sqlite3.h"
#include "lib_recomp.hpp"
 
extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
}

unsigned int reverse_byte_order(unsigned int x) {
    return ((x >> 24) & 0xFF) | ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000) | ((x << 24) & 0xFF000000);
}

RECOMP_DLL_FUNC(load_achievement) {
    Achievement* achievement = RECOMP_ARG(Achievement*, 0);

    // std::cout << "Pos: " << achievement->icon_size << "\n";
    printf("Achievement SIZE NATIVE: %llu\n", sizeof(Achievement));
    printf("ICON SIZE NATIVE: %i\n", achievement->icon_size);

    printf("Achievement ID: %s\n", ptr_to_string(rdram, (PTR(const char*))achievement->id).c_str());

}