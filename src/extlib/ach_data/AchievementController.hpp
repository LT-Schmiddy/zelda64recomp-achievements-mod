#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

class AchievementSet;

#include "sqlite3.h"
#include "lib_recomp.hpp"

#define DB_FILE_EXT ".AchievementNative.db"
#define DB_FLAG_TABLE "AchievementFlag"

namespace fs = std::filesystem;

class AchievementController {
public: 
    AchievementController(fs::path p_path);
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

    void loadAchievement(std::string ach_set, Achievement* achievement);

private:
    sqlite3* db;
    int kvState = -1;
    fs::path db_path;

    std::unordered_map<std::string, std::shared_ptr<AchievementSet>> achievement_sets;
};