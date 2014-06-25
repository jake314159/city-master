
#include <SDL.h>
#include <SDL_image.h>

#define NUMBER_OF_TILES 2
typedef enum {
    TILE_GRASS = 0,
    TILE_BUILDING = 1,
    TILE_HIGHLIGHT_BLUE = 2
} TILE_TYPE;

#define NUMBER_OF_SPRITES 2
typedef enum {
    SPRITE_BUILD_ROAD = 0,
    SPRITE_BUILD_BUILDING = 1
} SPRITE;


void initClips();
SDL_Rect* getTileClip(TILE_TYPE t);
SDL_Rect* getClip(SPRITE s);
