#include <string>
#include "lib_recomp.hpp"
#include "achievements.h"

class AchievementWrapper {
public:
    AchievementWrapper(uint8_t* p_recomp_rdram, Achievement* p_achievement);
    ~AchievementWrapper();

    uint8_t* recomp_rdram = NULL;
    Achievement* achievement = NULL;

    std::string getId();
    std::string getDisplayName();
    std::string getDescription();
};