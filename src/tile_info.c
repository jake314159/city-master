
#include "tile_info.h"

SDL_Rect tileClips[NUMBER_OF_TILES];

void initClips()
{
    tileClips[TILE_GRASS].x = 0;
    tileClips[TILE_GRASS].y = 0;
    tileClips[TILE_GRASS].w = 100;
    tileClips[TILE_GRASS].h = 65;

    tileClips[TILE_HIGHLIGHT_BLUE].x = 200;
    tileClips[TILE_HIGHLIGHT_BLUE].y = 0;
    tileClips[TILE_HIGHLIGHT_BLUE].w = 100;
    tileClips[TILE_HIGHLIGHT_BLUE].h = 65;

    tileClips[TILE_BUILDING].x = 100;
    tileClips[TILE_BUILDING].y = 0;
    tileClips[TILE_BUILDING].w = 100;
    tileClips[TILE_BUILDING].h = 65*2;
}

SDL_Rect* getTileClip(TILE_TYPE t)
{
    return &tileClips[t];
}
