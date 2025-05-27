#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

class AchievementSet;

#include "sqlite3.h"
#include "lib_recomp.hpp"
#include "achievements.h"

#define DB_FILE_EXT ".AchievementNative.db"
#define DB_FLAG_TABLE "AchievementFlag"
#define DB_UNLOCK_TABLE "AchievementUnlock"

namespace fs = std::filesystem;

class AchievementController {
public: 
    AchievementController(uint8_t* recomp_rdram, fs::path p_path);
    ~AchievementController();

    int initDatabase(fs::path p_path);
    int updateSavePath(fs::path p_path);

    int setFlag(std::string ach_set, std::string key, int slot, size_t size, void* data);
    int getFlag(std::string ach_set, std::string key, int slot, size_t size, void* write_data);
    int hasFlag(std::string ach_set, std::string key, int slot);
    int deleteFlag(std::string ach_set, std::string key, int slot);
    
    // These are meant to affect all slots:
    int deleteSlotFlags(int slot);
    int copySlotFlags(int dst_slot, int src_slot);

    void declareAchievement(std::string ach_set, Achievement* achievement);
    uint8_t* getRdram();
    void setRdram(uint8_t* p_recomp_rdram);
    int getCurrentSlot();

private:
    uint8_t* recomp_rdram = NULL;
    int current_slot = 0;
    sqlite3* db;
    int kvState = -1;
    fs::path db_path;

    std::unordered_map<std::string, std::shared_ptr<AchievementSet>> achievement_sets;
};