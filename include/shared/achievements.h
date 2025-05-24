
#ifdef __cplusplus
extern "C" {
#endif

// The definitions in this file have to me constructed carefully.
// All numerical types should have a size of 32-bit.
// We also need to make sure that the native side treats pointers
// and unsigned, 32-bit integers

#define PACKED_STRUCT struct __attribute__((packed))

#define ACH_BYTE unsigned char
#define ACH_U32 unsigned int

#ifdef MIPS
#define STRUCT_PTR(type) type*
#else
#define STRUCT_PTR(type) ACH_U32
#endif

typedef enum {
    ACHIEVEMENT_FLAG_BOOLEAN,
    ACHIEVEMENT_FLAG_UNSIGNED_INT,
    ACHIEVEMENT_FLAG_SIGNED_INT,
    ACHIEVEMENT_FLAG_FLOAT,
    ACHIEVEMENT_FLAG_STRING,
    ACHIEVEMENT_FLAG_MAX = 0xFFFFFFFF
} AchievementFlagType;

typedef PACKED_STRUCT {
    STRUCT_PTR(const char) id;
    AchievementFlagType type;
    STRUCT_PTR(const char) default_value; // Write as a string. The extlib will process this into the correct format
} AchievementFlag;

typedef PACKED_STRUCT {
    ACH_U32 ra_id;
} AchievementRAInfo;

typedef PACKED_STRUCT {
    STRUCT_PTR(const char) id;
    STRUCT_PTR(const char) display_name;
    STRUCT_PTR(const char) description;
    STRUCT_PTR(const ACH_BYTE) icon;
    const ACH_U32 icon_size;
    STRUCT_PTR(const char) additional_flags; // Optional. Can be NULL. Comma-seperated list.
    const AchievementRAInfo ra_info; // Optional. Can be NULL.
    STRUCT_PTR(const char) script; // Optional. Can be NULL.
} Achievement;


#ifdef MIPS
RECOMP_IMPORT(".", void init_achievement_lib())
RECOMP_IMPORT(".", void load_achievement(Achievement* achievements))
#endif

#ifdef __cplusplus
}
#endif