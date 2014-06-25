
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

//Number NOT including the road tiles!
#define NUMBER_OF_TILES 6
typedef enum {
    TILE_GRASS = 0,
    TILE_BUILDING = 1,
    TILE_HIGHLIGHT_BLUE = 2,
    TILE_HIGHLIGHT_RED = 3,
    TILE_HIGHLIGHT_YELLOW = 4,
    TILE_HIGHLIGHT_GREEN = 5,

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

#define NUMBER_OF_SPRITES 4
typedef enum {
    SPRITE_BUILD_BACKGROUND = 0,
    SPRITE_BUILD_ZONE = 1,
    SPRITE_BUILD_ROAD = 2,
    SPRITE_BUILD_DESTROY = 3
} SPRITE;


void initClips();
SDL_Rect* getTileClip(TILE_TYPE t);
SDL_Rect* getClip(SPRITE s);
// Gets the type of road based on which directions there are roads and which there aren't
TILE_TYPE typeOfRoad(bool north, bool east, bool south, bool west);
bool isRoad(TILE_TYPE t);
