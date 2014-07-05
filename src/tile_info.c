#include "tile_info.h"
#include "resource_manager.h"

#define SIN_30 0.5f
#define SIN_26_5 0.4461978131f
#define SIN_60 0.8660254f
#define SIN_63_5 0.8949343616f

SDL_Rect tileClips[NUMBER_OF_TILES];
SDL_Rect spriteClips[NUMBER_OF_SPRITES];
SDL_Rect roadClips[16];

int tilePowerRequirements[NUMBER_OF_TILES] = {0};
int tilePopulation[NUMBER_OF_TILES] = {0};

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
    tilePowerRequirements[TILE_RESIDENTIAL_1_B2] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_1_B3] = 50;
    tilePowerRequirements[TILE_RESIDENTIAL_2_ZONE] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_2_BUILDING] = 30;
    tilePowerRequirements[TILE_RESIDENTIAL_2_B1] = 60;
    tilePowerRequirements[TILE_RESIDENTIAL_2_B2] = 60;
    tilePowerRequirements[TILE_RESIDENTIAL_2_B3] = 60;
    tilePowerRequirements[TILE_SERVICE_BUILDING_HOSPITAL] = 1000;
    tilePowerRequirements[TILE_RETAIL_ZONE] = 0;
    tilePowerRequirements[TILE_RETAIL_BUILDING] = 30;
    tilePowerRequirements[TILE_RETAIL_B1] = 100;
    tilePowerRequirements[TILE_POWER_GAS_P1] = 0;
    tilePowerRequirements[TILE_POWER_GAS_P2] = 0;
    tilePowerRequirements[TILE_POWER_GAS_P3] = 0;
    tilePowerRequirements[TILE_POWER_GAS_P4] = 0;
    tilePowerRequirements[TILE_POWER_NUCLEAR_P1] = 0;
    tilePowerRequirements[TILE_POWER_NUCLEAR_P2] = 0;
    tilePowerRequirements[TILE_POWER_NUCLEAR_P3] = 0;
    tilePowerRequirements[TILE_POWER_NUCLEAR_P4] = 0;
    tilePowerRequirements[TILE_POWER_SOLAR] = 0;
    tilePowerRequirements[TILE_SERVICE_BUILDING_POLICE] = 400;
    tilePowerRequirements[TILE_POWER_WIND] = 0;
    tilePowerRequirements[TILE_COMMUNITY_SCHOOL_P1] = 500;
    tilePowerRequirements[TILE_COMMUNITY_SCHOOL_P2] = 0;
    tilePowerRequirements[TILE_COMMUNITY_SCHOOL_P3] = 0;
    tilePowerRequirements[TILE_COMMUNITY_SCHOOL_P4] = 0;
    tilePowerRequirements[TILE_LANDFILL_1] = 0;
    tilePowerRequirements[TILE_LANDFILL_2] = 0;
    tilePowerRequirements[TILE_LANDFILL_3] = 0;
    tilePowerRequirements[TILE_CULTURE_STADIUM_P1] = 500;
    tilePowerRequirements[TILE_CULTURE_PARK_P1] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_3_ZONE] = 0;
    tilePowerRequirements[TILE_RESIDENTIAL_3_BUILDING] = 60;
    tilePowerRequirements[TILE_RESIDENTIAL_3_B1] = 90;
    tilePowerRequirements[TILE_RESIDENTIAL_3_B2] = 90;

    tilePopulation[TILE_GRASS] = 0;
    tilePopulation[TILE_BUILDING] = 0;
    tilePopulation[TILE_HIGHLIGHT_BLUE] = 0;
    tilePopulation[TILE_HIGHLIGHT_RED] = 0;
    tilePopulation[TILE_HIGHLIGHT_YELLOW] = 0;
    tilePopulation[TILE_HIGHLIGHT_GREEN] = 0;
    tilePopulation[TILE_RESIDENTIAL_1_ZONE] = 0;
    tilePopulation[TILE_RESIDENTIAL_1_BUILDING] = 0;
    tilePopulation[TILE_RESIDENTIAL_1_B1] = 40;
    tilePopulation[TILE_RESIDENTIAL_1_B2] = 0;
    tilePopulation[TILE_RESIDENTIAL_1_B3] = 6;
    tilePopulation[TILE_RESIDENTIAL_2_ZONE] = 0;
    tilePopulation[TILE_RESIDENTIAL_2_BUILDING] = 0;
    tilePopulation[TILE_RESIDENTIAL_2_B1] = 6;
    tilePopulation[TILE_RESIDENTIAL_2_B2] = 10;
    tilePopulation[TILE_RESIDENTIAL_2_B3] = 6;
    tilePopulation[TILE_SERVICE_BUILDING_HOSPITAL] = 0;
    tilePopulation[TILE_RETAIL_ZONE] = 0;
    tilePopulation[TILE_RETAIL_BUILDING] = 0;
    tilePopulation[TILE_RETAIL_B1] = 0;
    tilePopulation[TILE_POWER_GAS_P1] = 0;
    tilePopulation[TILE_POWER_GAS_P2] = 0;
    tilePopulation[TILE_POWER_GAS_P3] = 0;
    tilePopulation[TILE_POWER_GAS_P4] = 0;
    tilePopulation[TILE_POWER_SOLAR] = 0;
    tilePopulation[TILE_SERVICE_BUILDING_POLICE] = 0;
    tilePopulation[TILE_POWER_WIND] = 0;
    tilePopulation[TILE_COMMUNITY_SCHOOL_P1] = 0;
    tilePopulation[TILE_COMMUNITY_SCHOOL_P2] = 0;
    tilePopulation[TILE_COMMUNITY_SCHOOL_P3] = 0;
    tilePopulation[TILE_COMMUNITY_SCHOOL_P4] = 0;
    tilePopulation[TILE_LANDFILL_1] = 0;
    tilePopulation[TILE_LANDFILL_2] = 0;
    tilePopulation[TILE_LANDFILL_3] = 0;
    tilePopulation[TILE_RESIDENTIAL_3_ZONE] = 0;
    tilePopulation[TILE_RESIDENTIAL_3_BUILDING] = 0;
    tilePopulation[TILE_RESIDENTIAL_3_B1] = 2;
    tilePopulation[TILE_RESIDENTIAL_3_B2] = 4;

    // Tiles
    tileClips[TILE_GRASS].x = 0;
    tileClips[TILE_GRASS].y = 0;
    tileClips[TILE_GRASS].w = 100;
    tileClips[TILE_GRASS].h = 65;

    tileClips[TILE_TREES_1].x = 0;
    tileClips[TILE_TREES_1].y = 65;
    tileClips[TILE_TREES_1].w = 100;
    tileClips[TILE_TREES_1].h = 65;

    tileClips[TILE_TREES_2].x = 0;
    tileClips[TILE_TREES_2].y = 65*2;
    tileClips[TILE_TREES_2].w = 100;
    tileClips[TILE_TREES_2].h = 65;

    tileClips[TILE_TREES_3].x = 0;
    tileClips[TILE_TREES_3].y = 65*3;
    tileClips[TILE_TREES_3].w = 100;
    tileClips[TILE_TREES_3].h = 130;

    tileClips[TILE_LANDFILL_1].x = 0;
    tileClips[TILE_LANDFILL_1].y = 65*5;
    tileClips[TILE_LANDFILL_1].w = 100;
    tileClips[TILE_LANDFILL_1].h = 65;

    tileClips[TILE_LANDFILL_2].x = 0;
    tileClips[TILE_LANDFILL_2].y = 65*6;
    tileClips[TILE_LANDFILL_2].w = 100;
    tileClips[TILE_LANDFILL_2].h = 65;

    tileClips[TILE_LANDFILL_3].x = 0;
    tileClips[TILE_LANDFILL_3].y = 65*7;
    tileClips[TILE_LANDFILL_3].w = 100;
    tileClips[TILE_LANDFILL_3].h = 65;

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

    tileClips[TILE_SERVICE_BUILDING_POLICE].x = 200;
    tileClips[TILE_SERVICE_BUILDING_POLICE].y = 65*4;
    tileClips[TILE_SERVICE_BUILDING_POLICE].w = 100;
    tileClips[TILE_SERVICE_BUILDING_POLICE].h = 65*2;

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

    tileClips[TILE_RESIDENTIAL_1_B2].x = 432;
    tileClips[TILE_RESIDENTIAL_1_B2].y = 65*4;
    tileClips[TILE_RESIDENTIAL_1_B2].w = 100;
    tileClips[TILE_RESIDENTIAL_1_B2].h = 65;

    tileClips[TILE_RESIDENTIAL_1_B3].x = 432;
    tileClips[TILE_RESIDENTIAL_1_B3].y = 65*5;
    tileClips[TILE_RESIDENTIAL_1_B3].w = 100;
    tileClips[TILE_RESIDENTIAL_1_B3].h = 65;

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

    tileClips[TILE_RESIDENTIAL_2_B2].x = 532;
    tileClips[TILE_RESIDENTIAL_2_B2].y = 65*3;
    tileClips[TILE_RESIDENTIAL_2_B2].w = 100;
    tileClips[TILE_RESIDENTIAL_2_B2].h = 130;

    tileClips[TILE_RESIDENTIAL_2_B3].x = 532;
    tileClips[TILE_RESIDENTIAL_2_B3].y = 65*5;
    tileClips[TILE_RESIDENTIAL_2_B3].w = 100;
    tileClips[TILE_RESIDENTIAL_2_B3].h = 130;

    
    tileClips[TILE_POWER_GAS_P1].x = 0;
    tileClips[TILE_POWER_GAS_P1].y = 0;
    tileClips[TILE_POWER_GAS_P1].w = 0;
    tileClips[TILE_POWER_GAS_P1].h = 0;

    tileClips[TILE_POWER_GAS_P2].x = 0;
    tileClips[TILE_POWER_GAS_P2].y = 0;
    tileClips[TILE_POWER_GAS_P2].w = 0;
    tileClips[TILE_POWER_GAS_P2].h = 0;

    tileClips[TILE_POWER_GAS_P3].x = 0;
    tileClips[TILE_POWER_GAS_P3].y = 0;
    tileClips[TILE_POWER_GAS_P3].w = 100; // Grass should be under here to fix the layers
    tileClips[TILE_POWER_GAS_P3].h = 65;

    tileClips[TILE_POWER_GAS_P4].x = 632;
    tileClips[TILE_POWER_GAS_P4].y = 0;
    tileClips[TILE_POWER_GAS_P4].w = 100*2;
    tileClips[TILE_POWER_GAS_P4].h = 65*3;

    tileClips[TILE_POWER_NUCLEAR_P1].x = 0;
    tileClips[TILE_POWER_NUCLEAR_P1].y = 0;
    tileClips[TILE_POWER_NUCLEAR_P1].w = 0;
    tileClips[TILE_POWER_NUCLEAR_P1].h = 0;

    tileClips[TILE_POWER_NUCLEAR_P2].x = 0;
    tileClips[TILE_POWER_NUCLEAR_P2].y = 0;
    tileClips[TILE_POWER_NUCLEAR_P2].w = 0;
    tileClips[TILE_POWER_NUCLEAR_P2].h = 0;

    tileClips[TILE_POWER_NUCLEAR_P3].x = 0;
    tileClips[TILE_POWER_NUCLEAR_P3].y = 0;
    tileClips[TILE_POWER_NUCLEAR_P3].w = 100; // Grass should be under here to fix the layers
    tileClips[TILE_POWER_NUCLEAR_P3].h = 65;

    tileClips[TILE_POWER_NUCLEAR_P4].x = 632;
    tileClips[TILE_POWER_NUCLEAR_P4].y = 65*7;
    tileClips[TILE_POWER_NUCLEAR_P4].w = 100*2;
    tileClips[TILE_POWER_NUCLEAR_P4].h = 65*3;

    tileClips[TILE_POWER_SOLAR].x = 632;
    tileClips[TILE_POWER_SOLAR].y = 65*3;
    tileClips[TILE_POWER_SOLAR].w = 100;
    tileClips[TILE_POWER_SOLAR].h = 65*2;

    tileClips[TILE_POWER_WIND].x = 632;
    tileClips[TILE_POWER_WIND].y = 65*5;
    tileClips[TILE_POWER_WIND].w = 100;
    tileClips[TILE_POWER_WIND].h = 65*2;

    tileClips[TILE_RETAIL_ZONE].x = 832;
    tileClips[TILE_RETAIL_ZONE].y = 0;
    tileClips[TILE_RETAIL_ZONE].w = 100;
    tileClips[TILE_RETAIL_ZONE].h = 65;

    tileClips[TILE_RETAIL_BUILDING].x = 832;
    tileClips[TILE_RETAIL_BUILDING].y = 65;
    tileClips[TILE_RETAIL_BUILDING].w = 100;
    tileClips[TILE_RETAIL_BUILDING].h = 65;

    tileClips[TILE_RETAIL_B1].x = 832;
    tileClips[TILE_RETAIL_B1].y = 65*2;
    tileClips[TILE_RETAIL_B1].w = 100;
    tileClips[TILE_RETAIL_B1].h = 65*2;

    tileClips[TILE_COMMUNITY_SCHOOL_P1].x = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P1].y = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P1].w = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P1].h = 0;

    tileClips[TILE_COMMUNITY_SCHOOL_P2].x = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P2].y = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P2].w = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P2].h = 0;

    tileClips[TILE_COMMUNITY_SCHOOL_P3].x = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P3].y = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P3].w = 100; // Grass should be under here to fix the layers
    tileClips[TILE_COMMUNITY_SCHOOL_P3].h = 65;

    tileClips[TILE_COMMUNITY_SCHOOL_P4].x = 932;
    tileClips[TILE_COMMUNITY_SCHOOL_P4].y = 0;
    tileClips[TILE_COMMUNITY_SCHOOL_P4].w = 100*2;
    tileClips[TILE_COMMUNITY_SCHOOL_P4].h = 65*3;

    tileClips[TILE_CULTURE_PARK_P1].x = 0;
    tileClips[TILE_CULTURE_PARK_P1].y = 0;
    tileClips[TILE_CULTURE_PARK_P1].w = 0;
    tileClips[TILE_CULTURE_PARK_P1].h = 0;

    tileClips[TILE_CULTURE_PARK_P2].x = 0;
    tileClips[TILE_CULTURE_PARK_P2].y = 0;
    tileClips[TILE_CULTURE_PARK_P2].w = 0;
    tileClips[TILE_CULTURE_PARK_P2].h = 0;

    tileClips[TILE_CULTURE_PARK_P3].x = 0;
    tileClips[TILE_CULTURE_PARK_P3].y = 0;
    tileClips[TILE_CULTURE_PARK_P3].w = 100; // Grass should be under here to fix the layers
    tileClips[TILE_CULTURE_PARK_P3].h = 65;

    tileClips[TILE_CULTURE_PARK_P4].x = 932;
    tileClips[TILE_CULTURE_PARK_P4].y = 65*3;
    tileClips[TILE_CULTURE_PARK_P4].w = 100*2;
    tileClips[TILE_CULTURE_PARK_P4].h = 65*2;

    tileClips[TILE_CULTURE_STADIUM_P1].x = 0;
    tileClips[TILE_CULTURE_STADIUM_P1].y = 0;
    tileClips[TILE_CULTURE_STADIUM_P1].w = 0;
    tileClips[TILE_CULTURE_STADIUM_P1].h = 0;

    tileClips[TILE_CULTURE_STADIUM_P2].x = 0;
    tileClips[TILE_CULTURE_STADIUM_P2].y = 0;
    tileClips[TILE_CULTURE_STADIUM_P2].w = 100;
    tileClips[TILE_CULTURE_STADIUM_P2].h = 65;

    tileClips[TILE_CULTURE_STADIUM_P3].x = 1132;
    tileClips[TILE_CULTURE_STADIUM_P3].y = 0;
    tileClips[TILE_CULTURE_STADIUM_P3].w = 400;
    tileClips[TILE_CULTURE_STADIUM_P3].h = 300;

    /*tileClips[TILE_CULTURE_STADIUM_P3].x = 0;
    tileClips[TILE_CULTURE_STADIUM_P3].y = 0;
    tileClips[TILE_CULTURE_STADIUM_P3].w = 100; // Grass should be under here to fix the layers
    tileClips[TILE_CULTURE_STADIUM_P3].h = 65;

    tileClips[TILE_CULTURE_STADIUM_P4].x = 932;
    tileClips[TILE_CULTURE_STADIUM_P4].y = 65*5;
    tileClips[TILE_CULTURE_STADIUM_P4].w = 100*2;
    tileClips[TILE_CULTURE_STADIUM_P4].h = 65*3;
*/
    tileClips[TILE_POWER_SOLAR].x = 632;
    tileClips[TILE_POWER_SOLAR].y = 65*3;
    tileClips[TILE_POWER_SOLAR].w = 100;
    tileClips[TILE_POWER_SOLAR].h = 65*2;

    tileClips[TILE_RESIDENTIAL_3_ZONE].x = 1552;
    tileClips[TILE_RESIDENTIAL_3_ZONE].y = 0;
    tileClips[TILE_RESIDENTIAL_3_ZONE].w = 100;
    tileClips[TILE_RESIDENTIAL_3_ZONE].h = 65;

    tileClips[TILE_RESIDENTIAL_3_BUILDING].x = 1552;
    tileClips[TILE_RESIDENTIAL_3_BUILDING].y = 65;
    tileClips[TILE_RESIDENTIAL_3_BUILDING].w = 100;
    tileClips[TILE_RESIDENTIAL_3_BUILDING].h = 65;

    tileClips[TILE_RESIDENTIAL_3_B1].x = 1552;
    tileClips[TILE_RESIDENTIAL_3_B1].y = 65*2;
    tileClips[TILE_RESIDENTIAL_3_B1].w = 100;
    tileClips[TILE_RESIDENTIAL_3_B1].h = 65*2;

    tileClips[TILE_RESIDENTIAL_3_B2].x = 1552;
    tileClips[TILE_RESIDENTIAL_3_B2].y = 65*4;
    tileClips[TILE_RESIDENTIAL_3_B2].w = 100;
    tileClips[TILE_RESIDENTIAL_3_B2].h = 65*2;


    //Sprites
	int i;
	for(i=0; i<NUMBER_OF_SPRITES; i++) {
		spriteClips[i].x = 400;
		spriteClips[i].y = 32*i;
		spriteClips[i].w = 32;
		spriteClips[i].h = 32;
	}

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
    return t == TILE_GRASS || t == TILE_TREES_1 || t == TILE_TREES_2 || t == TILE_TREES_3 || t == TILE_LANDFILL_3;
}

int getPowerUsage(TILE_TYPE t) 
{
    if(t >= TILE_ROAD_0 && t <= TILE_ROAD_14) return 0;
    return tilePowerRequirements[t];
}

int getPowerProduction(TILE_TYPE t) {
    int powerProduction;
    switch(t) {
        case TILE_POWER_GAS_P1:
        case TILE_POWER_GAS_P2:
        case TILE_POWER_GAS_P3:
        case TILE_POWER_GAS_P4:
            powerProduction = 4000;
            break;
        case TILE_POWER_SOLAR:
            powerProduction = 180;
            break;
        case TILE_POWER_WIND:
            powerProduction = 280;
            break;
        case TILE_POWER_NUCLEAR_P1:
            powerProduction = 120000;
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
        case TILE_POWER_NUCLEAR_P1:
            cost = 1500; //£1.5M
			break;
        case TILE_POWER_SOLAR:
            cost = 60;
            break;
        case TILE_POWER_WIND:
            cost = 20;
            break;
        case TILE_SERVICE_BUILDING_HOSPITAL:
            cost = 500;
            break;
        case TILE_COMMUNITY_SCHOOL_P1:
            cost = 150;
            break;
        case TILE_SERVICE_BUILDING_POLICE:
            cost = 150;
            break;
        case TILE_RESIDENTIAL_1_ZONE:
        case TILE_RESIDENTIAL_2_ZONE:
        case TILE_RESIDENTIAL_3_ZONE:
        case TILE_RETAIL_ZONE:
            cost = 1;
            break;
        case TILE_LANDFILL_1:
            cost = 5;
            break;
        case TILE_CULTURE_STADIUM_P1:
            cost = 600;
            break;
        case TILE_CULTURE_PARK_P1:
            cost = 50;
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
            income = -80;
            break;
        case TILE_POWER_NUCLEAR_P1:
            income = -250;
            break;
        case TILE_POWER_WIND:
            income = -8; 
            break;
        case TILE_SERVICE_BUILDING_HOSPITAL:
            income = -500 - (int)((getPolutionPerPerson()>0.f ? getPolutionPerPerson()<1.f ? getPolutionPerPerson() : 1.f : 0.f)*500.f);
            break;
        case TILE_SERVICE_BUILDING_POLICE:
            income = -260;
            break;
        case TILE_COMMUNITY_SCHOOL_P1:
            income = -280;
            break;
        case TILE_RESIDENTIAL_1_B1:
        case TILE_RESIDENTIAL_1_B2:
        case TILE_RESIDENTIAL_1_B3:
            income = 15;
        case TILE_RESIDENTIAL_2_B1:
        case TILE_RESIDENTIAL_2_B2:
        case TILE_RESIDENTIAL_2_B3:
            income = 10;
            break;
        case TILE_RESIDENTIAL_3_B1:
        case TILE_RESIDENTIAL_3_B2:
            income = 22;
            break;
        case TILE_RETAIL_B1:
            income = 30;
            break;
        default:
            income = 0;
            break;
    }
    return income;
}

int getTilePopulation(TILE_TYPE t)
{
    if(t >= TILE_ROAD_0 && t <= TILE_ROAD_14) return 0;
    return tilePopulation[t];
}

int getAmountOfPolution(TILE_TYPE t)
{
    int polutionAmount = 0;
    switch(t) {
        case TILE_POWER_GAS_P1:
            polutionAmount = 300;
            break;
        case TILE_LANDFILL_1:
        case TILE_LANDFILL_2:
        case TILE_LANDFILL_3:
            polutionAmount = 10;
            break;
        default:
            polutionAmount = 0;
            break;
    }
    return polutionAmount;
}

