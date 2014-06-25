
#include "tile_info.h"

SDL_Rect tileClips[NUMBER_OF_TILES];
SDL_Rect spriteClips[NUMBER_OF_SPRITES];
SDL_Rect roadClips[16];

void initClips()
{
    // Tiles
    tileClips[TILE_GRASS].x = 0;
    tileClips[TILE_GRASS].y = 0;
    tileClips[TILE_GRASS].w = 100;
    tileClips[TILE_GRASS].h = 65;

    tileClips[TILE_HIGHLIGHT_BLUE].x = 100;
    tileClips[TILE_HIGHLIGHT_BLUE].y = 0;
    tileClips[TILE_HIGHLIGHT_BLUE].w = 100;
    tileClips[TILE_HIGHLIGHT_BLUE].h = 65;

    tileClips[TILE_BUILDING].x = 200;
    tileClips[TILE_BUILDING].y = 0;
    tileClips[TILE_BUILDING].w = 100;
    tileClips[TILE_BUILDING].h = 65*2;


    //Sprites
    spriteClips[SPRITE_BUILD_BACKGROUND].x = 400;
    spriteClips[SPRITE_BUILD_BACKGROUND].y = 0;
    spriteClips[SPRITE_BUILD_BACKGROUND].w = 32;
    spriteClips[SPRITE_BUILD_BACKGROUND].h = 32;

    spriteClips[SPRITE_BUILD_ZONE].x = 400;
    spriteClips[SPRITE_BUILD_ZONE].y = 32;
    spriteClips[SPRITE_BUILD_ZONE].w = 32;
    spriteClips[SPRITE_BUILD_ZONE].h = 32;

    spriteClips[SPRITE_BUILD_ROAD].x = 400;
    spriteClips[SPRITE_BUILD_ROAD].y = 32*2;
    spriteClips[SPRITE_BUILD_ROAD].w = 32;
    spriteClips[SPRITE_BUILD_ROAD].h = 32;

    TILE_TYPE road_i = TILE_ROAD_0;
    for(; road_i<=TILE_ROAD_14; road_i++) {
        roadClips[road_i-200].x = 300;
        roadClips[road_i-200].y = (road_i-200)*65;
        roadClips[road_i-200].w = 100;
        roadClips[road_i-200].h = 65;
    }
}

bool isRoad(TILE_TYPE t)
{
    return t >= TILE_ROAD_0 && t <= TILE_ROAD_14;
}

TILE_TYPE typeOfRoad(bool north, bool east, bool south, bool west)
{
    int roadType = 0;
    if(north) roadType += 1;
    if(east) roadType += 2;
    if(south) roadType += 4;
    if(west) roadType += 8;

    if(roadType == 0) {
        //No neighbours
        return TILE_ROAD_14;
    } else {
        return TILE_ROAD_0 + roadType -1;
    }
}

SDL_Rect* getTileClip(TILE_TYPE t)
{
    if(t >= TILE_ROAD_0 && t <= TILE_ROAD_14) {
        //printf("ROAD TILE! %d,%d,%d,%d,%d\n", t,roadClips[t-200].x, roadClips[t-200].y, roadClips[t-200].h, roadClips[t-200].w);
        return &roadClips[t-200];
    }
    return &tileClips[t];
}

SDL_Rect* getClip(SPRITE s)
{
    return &spriteClips[s];
}
