#include <string>
#include <vector>
#include <memory>
#include "lib_recomp.hpp"
#include "achievements.h"
#include "AchievementWrapper.hpp"


class AchievementFlag {
public:
    AchievementFlagDefinition* flag = NULL;

    std::vector<std::shared_ptr<AchievementWrapper>> achievements;

    AchievementFlag();
    AchievementFlagType getType();
};