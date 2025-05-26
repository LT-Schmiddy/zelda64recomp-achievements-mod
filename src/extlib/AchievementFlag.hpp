#include <string>
#include <vector>
#include <memory>
#include "lib_recomp.hpp"
#include "achievements.h"
#include "AchievementWrapper.hpp"


class AchievementFlagWrapper {
public:
    AchievementFlagDefinition* flag = NULL;

    std::vector<std::shared_ptr<AchievementFlagWrapper>> achievement;

    AchievementFlagWrapper();
    AchievementFlagType getType();
};