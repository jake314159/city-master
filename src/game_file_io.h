#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "tile_info.h"
#include "city_master.h"

typedef struct {
    int32_t map_size_x;
    int32_t map_size_y;
    int32_t screen_x;
    int32_t screen_y;
    int32_t money;
    time_t save_time;
    TILE_TYPE map_value[MAP_SIZE_X][MAP_SIZE_Y];
    char RESERVED[32];
    int32_t CHECKSUM;
} GAME_SAVE;

void save_game(char* fileName, GAME_SAVE *save);
bool read_game(char *fileName, GAME_SAVE *save);
