#include "modding.h"
#include "global.h"

typedef enum {
    ACHIEVEMENT_FLAG_BOOLEAN,
    ACHIEVEMENT_FLAG_UNSIGNED_INT,
    ACHIEVEMENT_FLAG_SIGNED_INT,
    ACHIEVEMENT_FLAG_FLOAT,
    ACHIEVEMENT_FLAG_STRING,
    ACHIEVEMENT_FLAG_MAX = 0xFFFFFFFF
} AchievementFlagType;

typedef struct {
    const char* id;
    AchievementFlagType type;
} AchievementFlag;

typedef struct {
    u32 ra_id;
} AchievementRAInfo;

typedef struct {
    const char* id;
    const char* display_name;
    const char* description;
    const u8* icon;
    const u32 icon_size;
    const char* additional_flags; // Optional. Can be NULL. Comma-seperated list.
    const AchievementRAInfo ra_info; // Optional. Can be NULL.
    const char* script; // Optional. Can be NULL.
} Achievement;

