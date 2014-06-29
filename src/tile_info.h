#ifndef ____CHECK_ALREADY_IMPORTED_TILE_INFO____
#define ____CHECK_ALREADY_IMPORTED_TILE_INFO____ 1

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

//Number NOT including the road tiles!
#define NUMBER_OF_TILES 33
typedef enum {
    TILE_GRASS = 0,
    TILE_BUILDING = 1,
    TILE_HIGHLIGHT_BLUE = 2,
    TILE_HIGHLIGHT_RED = 3,
    TILE_HIGHLIGHT_YELLOW = 4,
    TILE_HIGHLIGHT_GREEN = 5,
    TILE_RESIDENTIAL_1_ZONE = 6,
    TILE_RESIDENTIAL_1_BUILDING = 7,
    TILE_RESIDENTIAL_1_B1 = 8,
    TILE_RESIDENTIAL_2_ZONE = 9,
    TILE_RESIDENTIAL_2_BUILDING = 10,
    TILE_RESIDENTIAL_2_B1 = 11,

    TILE_POWER_GAS_P1 = 12, //Made of 4 parts
    TILE_POWER_GAS_P2 = 13,
    TILE_POWER_GAS_P3 = 14,
    TILE_POWER_GAS_P4 = 15,

    TILE_SERVICE_BUILDING_HOSPITAL = 16,

    TILE_RETAIL_ZONE = 17,
    TILE_RETAIL_BUILDING = 18,
    TILE_RETAIL_B1 = 19,

    TILE_POWER_SOLAR = 20,

    TILE_SERVICE_BUILDING_POLICE = 21,
    TILE_POWER_WIND = 22,

    TILE_TREES_1 = 23,
    TILE_TREES_2 = 24,
    TILE_TREES_3 = 25,

    TILE_COMMUNITY_SCHOOL_P1 = 26, //Made of 4 parts
    TILE_COMMUNITY_SCHOOL_P2 = 27,
    TILE_COMMUNITY_SCHOOL_P3 = 28,
    TILE_COMMUNITY_SCHOOL_P4 = 29,

    TILE_LANDFILL_1 = 30,
    TILE_LANDFILL_2 = 31,
    TILE_LANDFILL_3 = 32,

    TILE_ROAD_0 = 200,
    TILE_ROAD_1 = 201,
    TILE_ROAD_2 = 202,
    TILE_ROAD_3 = 203,
    TILE_ROAD_4 = 204,
    TILE_ROAD_5 = 205,
    TILE_ROAD_6 = 206,
    TILE_ROAD_7 = 207,
    TILE_ROAD_8 = 208,
    TILE_ROAD_9 = 209,
    TILE_ROAD_10= 210,
    TILE_ROAD_11= 211,
    TILE_ROAD_12= 212,
    TILE_ROAD_13= 213,
    TILE_ROAD_14= 214
} TILE_TYPE;

#define NUMBER_OF_SPRITES 14
typedef enum {
    NULL_SPRITE = -1, //IMPORTANT:: Don't try to use this as it will cause buffer overflows
    SPRITE_BUILD_BACKGROUND = 0,
    SPRITE_BUILD_ZONE_RES1 = 1,
    SPRITE_BUILD_ROAD = 2,
    SPRITE_BUILD_DESTROY = 3,
    SPRITE_BUILD_ZONE_RES2 = 4,
    SPRITE_BUILD_POWER_GENRAL = 5,
    SPRITE_BUILD_POWER_GAS = 6,
    SPRITE_SERVICES_GENRAL = 7,
    SPRITE_SERVICES_HOSPITAL = 8,
    SPRITE_BUILD_ZONE_RETAIL = 9,
    SPRITE_BUILD_POWER_SOLAR = 10,
    SPRITE_BUILD_SERVICES_POLICE = 11,
    SPRITE_BUILD_POWER_WIND = 12,
    SPRITE_BUILD_SCHOOL = 13
} SPRITE;


void initClips();
SDL_Rect* getTileClip(TILE_TYPE t);
SDL_Rect* getClip(SPRITE s);
// Gets the type of road based on which directions there are roads and which there aren't
TILE_TYPE typeOfRoad(bool north, bool east, bool south, bool west);
bool isRoad(TILE_TYPE t);

bool canBuildOn(TILE_TYPE t);
int getPowerUsage(TILE_TYPE t);
int getPowerProduction(TILE_TYPE t);
int getCost(TILE_TYPE t);
int getIncome(TILE_TYPE t);
int getTilePopulation(TILE_TYPE t);

#endif
