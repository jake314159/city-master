
#include "tile_info.h"

SDL_Rect tileClips[NUMBER_OF_TILES];
SDL_Rect spriteClips[NUMBER_OF_SPRITES];
SDL_Rect roadClips[16];

int tilePowerRequirements[NUMBER_OF_TILES];

void initClips()
{
    tilePowerRequirements[TILE_GRASS] = 0;
    tilePowerRequirements[TILE_BUILDING] = 0;
    tilePowerRequirements[TILE_HIGHLIGHT_BLUE] = 0;
    tilePowerRequirements[TILE_HIGHLIGHT_RED] = 0;
    tilePowerRequirements[TILE_HIGHLIGHT_YELLOW] = 0;
    tilePowerRequirements[TILE_HIGHLIGHT_GREEN] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_1_ZONE] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_1_BUILDING] = 50;
    tilePowerRequirements[TILE_RESIDENTIAL_1_B1] = 100;
    tilePowerRequirements[TILE_RESIDENTIAL_2_ZONE] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_2_BUILDING] = 30;
    tilePowerRequirements[TILE_RESIDENTIAL_2_B1] = 60;
    tilePowerRequirements[TILE_SERVICE_BUILDING_HOSPITAL] = 1000;

    // Tiles
    tileClips[TILE_GRASS].x = 0;
    tileClips[TILE_GRASS].y = 0;
    tileClips[TILE_GRASS].w = 100;
    tileClips[TILE_GRASS].h = 65;

    tileClips[TILE_HIGHLIGHT_BLUE].x = 100;
    tileClips[TILE_HIGHLIGHT_BLUE].y = 0;
    tileClips[TILE_HIGHLIGHT_BLUE].w = 100;
    tileClips[TILE_HIGHLIGHT_BLUE].h = 65;

    tileClips[TILE_HIGHLIGHT_RED].x = 100;
    tileClips[TILE_HIGHLIGHT_RED].y = 65;
    tileClips[TILE_HIGHLIGHT_RED].w = 100;
    tileClips[TILE_HIGHLIGHT_RED].h = 65;

    tileClips[TILE_HIGHLIGHT_YELLOW].x = 100;
    tileClips[TILE_HIGHLIGHT_YELLOW].y = 65*2;
    tileClips[TILE_HIGHLIGHT_YELLOW].w = 100;
    tileClips[TILE_HIGHLIGHT_YELLOW].h = 65;

    tileClips[TILE_HIGHLIGHT_GREEN].x = 100;
    tileClips[TILE_HIGHLIGHT_GREEN].y = 65*3;
    tileClips[TILE_HIGHLIGHT_GREEN].w = 100;
    tileClips[TILE_HIGHLIGHT_GREEN].h = 65;

    tileClips[TILE_BUILDING].x = 200;
    tileClips[TILE_BUILDING].y = 0;
    tileClips[TILE_BUILDING].w = 100;
    tileClips[TILE_BUILDING].h = 65*2;

    tileClips[TILE_SERVICE_BUILDING_HOSPITAL].x = 200;
    tileClips[TILE_SERVICE_BUILDING_HOSPITAL].y = 65*2;
    tileClips[TILE_SERVICE_BUILDING_HOSPITAL].w = 100;
    tileClips[TILE_SERVICE_BUILDING_HOSPITAL].h = 65*2;

    tileClips[TILE_RESIDENTIAL_1_ZONE].x = 432;
    tileClips[TILE_RESIDENTIAL_1_ZONE].y = 0;
    tileClips[TILE_RESIDENTIAL_1_ZONE].w = 100;
    tileClips[TILE_RESIDENTIAL_1_ZONE].h = 65;

    tileClips[TILE_RESIDENTIAL_1_BUILDING].x = 432;
    tileClips[TILE_RESIDENTIAL_1_BUILDING].y = 65;
    tileClips[TILE_RESIDENTIAL_1_BUILDING].w = 100;
    tileClips[TILE_RESIDENTIAL_1_BUILDING].h = 65;

    tileClips[TILE_RESIDENTIAL_1_B1].x = 432;
    tileClips[TILE_RESIDENTIAL_1_B1].y = 65*2;
    tileClips[TILE_RESIDENTIAL_1_B1].w = 100;
    tileClips[TILE_RESIDENTIAL_1_B1].h = 65*2;

    tileClips[TILE_RESIDENTIAL_2_ZONE].x = 532;
    tileClips[TILE_RESIDENTIAL_2_ZONE].y = 0;
    tileClips[TILE_RESIDENTIAL_2_ZONE].w = 100;
    tileClips[TILE_RESIDENTIAL_2_ZONE].h = 65;

    tileClips[TILE_RESIDENTIAL_2_BUILDING].x = 532;
    tileClips[TILE_RESIDENTIAL_2_BUILDING].y = 65;
    tileClips[TILE_RESIDENTIAL_2_BUILDING].w = 100;
    tileClips[TILE_RESIDENTIAL_2_BUILDING].h = 65;

    tileClips[TILE_RESIDENTIAL_2_B1].x = 532;
    tileClips[TILE_RESIDENTIAL_2_B1].y = 65*2;
    tileClips[TILE_RESIDENTIAL_2_B1].w = 100;
    tileClips[TILE_RESIDENTIAL_2_B1].h = 65;

    
    tileClips[TILE_POWER_GAS_P1].x = 632;
    tileClips[TILE_POWER_GAS_P1].y = 0;
    tileClips[TILE_POWER_GAS_P1].w = 100;
    tileClips[TILE_POWER_GAS_P1].h = 65*2;

    tileClips[TILE_POWER_GAS_P2].x = 732;
    tileClips[TILE_POWER_GAS_P2].y = 0;
    tileClips[TILE_POWER_GAS_P2].w = 100;
    tileClips[TILE_POWER_GAS_P2].h = 65*2;

    tileClips[TILE_POWER_GAS_P3].x = 632;
    tileClips[TILE_POWER_GAS_P3].y = 65*2;
    tileClips[TILE_POWER_GAS_P3].w = 100;
    tileClips[TILE_POWER_GAS_P3].h = 65;

    tileClips[TILE_POWER_GAS_P4].x = 732;
    tileClips[TILE_POWER_GAS_P4].y = 65*2;
    tileClips[TILE_POWER_GAS_P4].w = 100;
    tileClips[TILE_POWER_GAS_P4].h = 65;


    //Sprites
    spriteClips[SPRITE_BUILD_BACKGROUND].x = 400;
    spriteClips[SPRITE_BUILD_BACKGROUND].y = 0;
    spriteClips[SPRITE_BUILD_BACKGROUND].w = 32;
    spriteClips[SPRITE_BUILD_BACKGROUND].h = 32;

    spriteClips[SPRITE_BUILD_ZONE_RES1].x = 400;
    spriteClips[SPRITE_BUILD_ZONE_RES1].y = 32;
    spriteClips[SPRITE_BUILD_ZONE_RES1].w = 32;
    spriteClips[SPRITE_BUILD_ZONE_RES1].h = 32;

    spriteClips[SPRITE_BUILD_ROAD].x = 400;
    spriteClips[SPRITE_BUILD_ROAD].y = 32*2;
    spriteClips[SPRITE_BUILD_ROAD].w = 32;
    spriteClips[SPRITE_BUILD_ROAD].h = 32;

    spriteClips[SPRITE_BUILD_DESTROY].x = 400;
    spriteClips[SPRITE_BUILD_DESTROY].y = 32*3;
    spriteClips[SPRITE_BUILD_DESTROY].w = 32;
    spriteClips[SPRITE_BUILD_DESTROY].h = 32;

    spriteClips[SPRITE_BUILD_ZONE_RES2].x = 400;
    spriteClips[SPRITE_BUILD_ZONE_RES2].y = 32*4;
    spriteClips[SPRITE_BUILD_ZONE_RES2].w = 32;
    spriteClips[SPRITE_BUILD_ZONE_RES2].h = 32;

    spriteClips[SPRITE_BUILD_POWER_GENRAL].x = 400;
    spriteClips[SPRITE_BUILD_POWER_GENRAL].y = 32*5;
    spriteClips[SPRITE_BUILD_POWER_GENRAL].w = 32;
    spriteClips[SPRITE_BUILD_POWER_GENRAL].h = 32;

    spriteClips[SPRITE_BUILD_POWER_GAS].x = 400;
    spriteClips[SPRITE_BUILD_POWER_GAS].y = 32*6;
    spriteClips[SPRITE_BUILD_POWER_GAS].w = 32;
    spriteClips[SPRITE_BUILD_POWER_GAS].h = 32;

    spriteClips[SPRITE_SERVICES_GENRAL].x = 400;
    spriteClips[SPRITE_SERVICES_GENRAL].y = 32*7;
    spriteClips[SPRITE_SERVICES_GENRAL].w = 32;
    spriteClips[SPRITE_SERVICES_GENRAL].h = 32;

    spriteClips[SPRITE_SERVICES_HOSPITAL].x = 400;
    spriteClips[SPRITE_SERVICES_HOSPITAL].y = 32*8;
    spriteClips[SPRITE_SERVICES_HOSPITAL].w = 32;
    spriteClips[SPRITE_SERVICES_HOSPITAL].h = 32;

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

bool canBuildOn(TILE_TYPE t)
{
    return t == TILE_GRASS;
}

int getPowerUsage(TILE_TYPE t) 
{
    return tilePowerRequirements[t];
}

int getPowerProduction(TILE_TYPE t) {
    int powerProduction;
    switch(t) {
        case TILE_POWER_GAS_P1:
        case TILE_POWER_GAS_P2:
        case TILE_POWER_GAS_P3:
        case TILE_POWER_GAS_P4:
            powerProduction = 1000;
            break;
        default:
            powerProduction = 0;
    }
    return powerProduction;
}

int getCost(TILE_TYPE t)
{
    if(t >= TILE_ROAD_0 && t <= TILE_ROAD_14) return 1;

    int cost;
    switch(t) {
        case TILE_POWER_GAS_P1:
        case TILE_POWER_GAS_P2:
        case TILE_POWER_GAS_P3:
        case TILE_POWER_GAS_P4:
            cost = 80; //total of £360,000
            break;
        case TILE_SERVICE_BUILDING_HOSPITAL:
            cost = 500;
            break;
        case TILE_RESIDENTIAL_1_ZONE:
        case TILE_RESIDENTIAL_2_ZONE:
            cost = 1;
            break;
        default:
            cost = 0;
            break;
    }
    return cost;
}

int getIncome(TILE_TYPE t)
{
    if(t >= TILE_ROAD_0 && t <= TILE_ROAD_14) return -1;

    int income;
    switch(t) {
        case TILE_POWER_GAS_P1:
        case TILE_POWER_GAS_P2:
        case TILE_POWER_GAS_P3:
        case TILE_POWER_GAS_P4:
            income = -10; //total of -£40,000
            break;
        case TILE_SERVICE_BUILDING_HOSPITAL:
            income = -100;
            break;
        case TILE_RESIDENTIAL_1_B1:
            income = 4;
        case TILE_RESIDENTIAL_2_B1:
            income = 6;
            break;
        default:
            income = 0;
            break;
    }
    return income;
}

