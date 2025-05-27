#include <iostream>
#include <string.h>

#include "AchievementController.hpp"

#include "AchievementWrapper.hpp"
#include "AchievementFlag.hpp"
#include "AchievementSet.hpp"

AchievementController::AchievementController(uint8_t* p_recomp_rdram, fs::path p_path) {
    recomp_rdram = p_recomp_rdram;
    updateSavePath(p_path);
}

AchievementController::~AchievementController() {}


int AchievementController::initDatabase(fs::path p_path) {
    if (sqlite3_open(db_path.string().c_str(), &db) != SQLITE_OK) {
        printf("[AchievementNative] Failed init, can't open database: %s\n", sqlite3_errmsg(db));
        kvState = 0;
        return kvState;
    }

    const char *flag_sql = 
        "CREATE TABLE IF NOT EXISTS " DB_FLAG_TABLE " ("
        "ach_set TEXT,"
        "key TEXT,"
        "slot INTEGER,"
        "value BLOB NOT NULL,"
        "PRIMARY KEY(ach_set, key, slot)"
    ");";
    
    kvState = sqlite3_exec(db, flag_sql, 0, 0, 0) == SQLITE_OK;
    if (!kvState) {
        printf("[AchievementNative] Failed init, failed table '%s' creation: %s\n", DB_FLAG_TABLE, sqlite3_errmsg(db));
    } else {
        printf("[AchievementNative] Initialized '%s'\n", DB_FLAG_TABLE);
    }

    const char *unlock_sql = 
        "CREATE TABLE IF NOT EXISTS " DB_UNLOCK_TABLE " ("
        "ach_set TEXT,"
        "key TEXT,"
        "unlocked INTEGER,"
        "PRIMARY KEY(ach_set, key)"
    ");";
    
    kvState = sqlite3_exec(db, unlock_sql, 0, 0, 0) == SQLITE_OK;
    if (!kvState) {
        printf("[AchievementNative] Failed init, failed table '%s' creation: %s\n", DB_UNLOCK_TABLE, sqlite3_errmsg(db));
    } else {
        printf("[AchievementNative] Initialized '%s'\n", DB_UNLOCK_TABLE);
    }

    return kvState;

}

int AchievementController::updateSavePath(fs::path p_path) {
    fs::path new_path = fs::path(p_path).replace_extension(DB_FILE_EXT);

    if (kvState == -1) {
        db_path = new_path;
        printf("[AchievementNative] Initializing " DB_FLAG_TABLE " at %s\n", new_path.string().c_str());
        initDatabase(new_path);
        return kvState;
    } else if (new_path != db_path) {
        // Restarting DB
        printf("[AchievementNative] Reloading " DB_FLAG_TABLE " at %s\n", new_path.string().c_str());
        db_path = new_path;
        sqlite3_close(db);
        initDatabase(new_path);
        return kvState;
    } else {
        // printf("[ProxyRecomp_KV] No state change needed. %s\n", new_path.string().c_str());
    }
    return kvState;
}

int AchievementController::setFlag(std::string ach_set, std::string key, int slot, size_t size, void* data) {
    if (!kvState) {
        printf("[AchievementNative] Failed SET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "INSERT INTO " DB_FLAG_TABLE " (ach_set, slot, key, value) VALUES (?, ?, ?, ?) ON CONFLICT(ach_set, key, slot) DO UPDATE SET value = excluded.value;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed SET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_text(stmt, 1, ach_set.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, slot);
    sqlite3_bind_text(stmt, 3, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 4, data, size, SQLITE_STATIC);
    int res = sqlite3_step(stmt) == SQLITE_DONE;
    if (!res) {
        printf("[AchievementNative] Failed SET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);

    return res;
}

int AchievementController::getFlag(std::string ach_set, std::string key, int slot, size_t size, void* write_data) {
    if (!kvState) {
        printf("[AchievementNative] Failed GET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT value FROM " DB_FLAG_TABLE " WHERE ach_set = ? AND key = ? AND slot = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed GET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_text(stmt, 1, ach_set.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, slot);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        size_t stored_size = sqlite3_column_bytes(stmt, 0);
        if (stored_size != size) {  // Fail if sizes don't match
            printf("[AchievementNative] Failed GET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return 0;
        }
        memcpy(write_data, sqlite3_column_blob(stmt, 0), stored_size);
        sqlite3_finalize(stmt);
        return 1;
    }

    // No need to log this I don't think?
    sqlite3_finalize(stmt);
    return 0;
}

int AchievementController::hasFlag(std::string ach_set, std::string key, int slot) {
    if (!kvState) {
        printf("[AchievementNative] Failed REMOVE %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT 1 FROM " DB_FLAG_TABLE " WHERE key = ? AND slot = ? LIMIT 1;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed REMOVE %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }
    
    sqlite3_bind_text(stmt, 1, ach_set.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, slot);

    // Return 1 if the key exists, 0 otherwise
    int exists = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return exists;
}

int AchievementController::deleteFlag(std::string ach_set, std::string key, int slot) {
    if (!kvState) {
        printf("[AchievementNative] Failed REMOVE %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "DELETE FROM " DB_FLAG_TABLE " REMOVE ach_set = ? AND key = ? AND slot = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed GET %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_text(stmt, 1, ach_set.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, key.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, slot);
    int res = sqlite3_step(stmt) == SQLITE_DONE;
    if (!res) {
        printf("[AchievementNative] Failed REMOVE %s (ach_set %s, slot %d): %s\n", ach_set.c_str(), key.c_str(), slot, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    return res;
}

int AchievementController::deleteSlotFlags(int slot) {
    if (!kvState) {
        printf("[AchievementNative] Failed REMOVE slot %d: %s\n", slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "DELETE FROM " DB_FLAG_TABLE " WHERE slot = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed REMOVE slot %d: %s\n", slot, sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, slot);
    int res = sqlite3_step(stmt) == SQLITE_DONE;
    if (!res) {
        printf("[AchievementNative] Failed REMOVE slot %d: %s\n", slot, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);

    printf("[AchievementNative] REMOVE slot %d succeeded\n", slot);
    return res;
}

int AchievementController::copySlotFlags(int new_slot, int old_slot) {
    if (!kvState) {
        printf("[AchievementNative] Failed COPY slot %d -> slot %d: %s\n", old_slot, new_slot, sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "Insert INTO " DB_FLAG_TABLE " (key, slot, value) SELECT key, ?, value FROM storage004 WHERE slot = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("[AchievementNative] Failed COPY slot %d -> slot %d: %s\n", old_slot, new_slot, sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, new_slot);
    sqlite3_bind_int(stmt, 2, old_slot);
    int res = sqlite3_step(stmt) == SQLITE_DONE;
    if (!res) {
        printf("[AchievementNative] Failed COPY slot %d -> slot %d: %s\n", old_slot, new_slot, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    return res;
}

void AchievementController::declareAchievement(std::string ach_set, Achievement* achievement) {
    if (!achievement_sets.contains(ach_set)) {
        printf("Creating new achievement set %s\n", ach_set.c_str());
        std::shared_ptr<AchievementSet> new_set = std::make_shared<AchievementSet>(this, ach_set);

        auto pair = std::pair<std::string, std::shared_ptr<AchievementSet>>(ach_set, new_set);
        achievement_sets.insert(pair);
    }
    printf("Creating new achievement in %s\n", ach_set.c_str());
    achievement_sets.at(ach_set)->declareAchievement(achievement);

}

uint8_t* AchievementController::getRdram() {
    return recomp_rdram;
}

void AchievementController::setRdram(uint8_t* p_recomp_rdram) {
    recomp_rdram = p_recomp_rdram;
}

int AchievementController::getCurrentSlot() {
    return current_slot;
}