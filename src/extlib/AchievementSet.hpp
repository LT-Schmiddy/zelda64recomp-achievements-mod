#include <string>
#include <map>
#include <memory>

#include "AchievementFlag.hpp"
#include "AchievementWrapper.hpp"

class AchievementSet {
public:
    AchievementSet(std::string ach_set);
    ~AchievementSet();

    std::map<std::string, std::shared_ptr<AchievementWrapper>> achievments;
    std::map<std::string, std::shared_ptr<AchievementFlag>> flags;

};