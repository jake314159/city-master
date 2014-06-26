#include <stdbool.h>
#include "tile_info.h"

//const int MAP_SIZE_X = 32;
//const int MAP_SIZE_Y = 32;
#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

typedef enum {
    MODE_VIEW,
    MODE_BUILD_RESIDENTIAL_1,
    MODE_BUILD_RESIDENTIAL_2,
    MODE_BUILD_ROAD,
    MODE_BUILD_POWER_GAS,
    MODE_BUILD_DESTROY
} MODE;

void setMode(MODE mode);
MODE getMode();
bool build_tile(int x, int y, TILE_TYPE t);
