#ifndef ____CHECK_ALREADY_IMPORTED_CITY_MASTER____
#define ____CHECK_ALREADY_IMPORTED_CITY_MASTER____ 1

#include <stdbool.h>
#include "tile_info.h"

//const int MAP_SIZE_X = 32;
//const int MAP_SIZE_Y = 32;
#define MAP_SIZE_X 128
#define MAP_SIZE_Y 128

typedef enum {
    MODE_VIEW,
    MODE_BUILD_RESIDENTIAL_1,
    MODE_BUILD_RESIDENTIAL_2,
    MODE_BUILD_ROAD,
    MODE_BUILD_POWER_GAS,
    MODE_BUILD_DESTROY,
    MODE_BUILD_HOSPITAL,
    MODE_BUILD_RETAIL,
    MODE_BUILD_POWER_SOLAR,
    MODE_BUILD_POLICE,
    MODE_BUILD_POWER_WIND,
    MODE_BUILD_SCHOOL,
    MODE_BUILD_LANDFILL,
	MODE_BUILD_POWER_NUCLEAR,
    MODE_BUILD_STADIUM,
    MODE_BUILD_PARK,
    MODE_BUILD_RESIDENTIAL_3
} MODE;

void setMode(MODE mode);
MODE getMode();
bool build_tile(int x, int y, TILE_TYPE t);
int costOfPlannedBuild();

void load_into_current_game(char *fileName);
void save_current_game(char *fileName);

#endif
