#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "city_master.h"
#include "SDL_functions.h"
#include "draw_utils.h"
#include "resource_manager.h"
#include "drawing_functions.h"
#include "mouse_functions.h"

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define ABS(X) (((X)>0) ? (X) : (-(X)))

#define FRAME_TIME_DELAY 20

const char* WINDOW_NAME = "City Master";
const int SCREEN_WIDTH = 900;//640;
const int SCREEN_HEIGHT = 620;//480;

int screen_x, screen_y = 0;
TILE_TYPE map_value[MAP_SIZE_X][MAP_SIZE_Y] = {{0}};

MODE mode = MODE_VIEW;

Point down_point;
Point up_point;

bool ready_to_place = false;
bool updating_plan = false;
Point plan_up;
Point plan_down;

int build_prob = 1500;
int build_finish_prob = 600;
int landfill_fill_prob = 65536;

extern int reqired_power;
extern int power_avalible;

extern int number_of_shops;
const int target_population_per_shop = 250;
const float target_population_per_police = 4000;
const float target_population_per_school = 2800;

int balanceChangeCounterStart = 100;
int balanceChangeCounter = 100;
int lastBalanceChange;

int window_size_x;
int window_size_y;

void setMode(MODE m)
{
    mode = m;
}

MODE getMode()
{
    return mode;
}

//sets the road to the correct type
void typeRoad(Point u)
{
    TILE_TYPE t = typeOfRoad(isRoad(map_value[u.x][u.y-1]), isRoad(map_value[u.x+1][u.y]), 
                                isRoad(map_value[u.x][u.y+1]), isRoad(map_value[u.x-1][u.y]));
    build_tile(u.x, u.y, t);
}

void fill_map()
{
    int x, y;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            if(rand()%10 == 0) {
                int r = (rand()%6);
                if(r <3) {
                    map_value[x][y] = TILE_TREES_1 + r;
                } else {
                    map_value[x][y] = TILE_TREES_1 + r%2;
                }
            }
        }
    }
}

void placeRoad(Point u)
{
    if(u.x >1 && u.y>1 && u.x < MAP_SIZE_X-1 && u.y < MAP_SIZE_Y-1 && canBuildOn(map_value[u.x][u.y])) {
        typeRoad(u);
        u.x += 1;
        if(isRoad(map_value[u.x][u.y])) typeRoad(u);
        u.x -= 2;
        if(isRoad(map_value[u.x][u.y])) typeRoad(u);
        u.x += 1;

        u.y += 1;
        if(isRoad(map_value[u.x][u.y])) typeRoad(u);
        u.y -= 2;
        if(isRoad(map_value[u.x][u.y])) typeRoad(u);
        u.y += 1;
    }
}

void planRoad(Point u, Point d)
{
    ready_to_place = true;
    plan_up.x = u.x;
    plan_up.y = u.y;
    plan_down.x = d.x;
    plan_down.y = d.y;
}

int costOfPlannedBuild()
{
    if(!ready_to_place) return 0;

    int cost = 0, x, y;
    Point p;

    switch(mode) {
        case MODE_BUILD_ROAD:
            cost = getCost(TILE_ROAD_0)*(ABS(plan_down.y-plan_up.y)+ABS(plan_down.x-plan_up.x));
            break;
        case MODE_BUILD_RESIDENTIAL_1:;
            cost = getCost(TILE_RESIDENTIAL_1_ZONE)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_RESIDENTIAL_2:;
            cost = getCost(TILE_RESIDENTIAL_2_ZONE)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_LANDFILL:;
            cost = getCost(TILE_LANDFILL_1)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_RETAIL:;
            cost = getCost(TILE_RETAIL_ZONE)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_POWER_SOLAR:;
            cost = getCost(TILE_POWER_SOLAR)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_POWER_WIND:;
            cost = getCost(TILE_POWER_WIND)*((ABS(plan_down.y-plan_up.y)+1)*(ABS(plan_down.x-plan_up.x)+1));
            break;
        case MODE_BUILD_DESTROY:
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    build_tile(p.x, p.y, TILE_GRASS); //TODO Do a proper destroy function
                }
            }

            break;
        case MODE_BUILD_HOSPITAL:
            cost = getCost(TILE_SERVICE_BUILDING_HOSPITAL);
            break;
        case MODE_BUILD_POLICE:
            cost = getCost(TILE_SERVICE_BUILDING_POLICE);
            break;
        case MODE_BUILD_POWER_GAS:;
            cost += getCost(TILE_POWER_GAS_P1);
            cost += getCost(TILE_POWER_GAS_P2);
            cost += getCost(TILE_POWER_GAS_P3);
            cost += getCost(TILE_POWER_GAS_P4);
            break;
        case MODE_BUILD_POWER_NUCLEAR:;
            cost = getCost(TILE_POWER_NUCLEAR_P1);
            break;
        case MODE_BUILD_SCHOOL:;
            cost = getCost(TILE_COMMUNITY_SCHOOL_P1);
            break;
        case MODE_BUILD_STADIUM:;
            cost = getCost(TILE_CULTURE_STADIUM_P1);
            break;
        case MODE_BUILD_PARK:;
            cost = getCost(TILE_CULTURE_PARK_P1);
            break;
        default:
            break;
    }
    return cost;
}

void placePlannedBuild()
{
    if(!ready_to_place) return;
    Point p;
    int x, y;
    switch(mode) {
        case MODE_BUILD_ROAD:
            p = plan_down;
            placeRoad(plan_down);
            placeRoad(plan_up);
            while(p.x != plan_up.x) {
                if(p.x < plan_up.x) {
                    p.x += 1;
                } else {
                    p.x -=1;
                }
                placeRoad(p);
            }
            while(p.y != plan_up.y) {
                if(p.y < plan_up.y) {
                    p.y += 1;
                } else {
                    p.y -=1;
                }
                placeRoad(p);
            }
            break;
        case MODE_BUILD_RESIDENTIAL_1:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y])) {
                        build_tile(p.x, p.y, TILE_RESIDENTIAL_1_ZONE);
                    }
                }
            }

            break;
        case MODE_BUILD_RESIDENTIAL_2:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y])) {
                        build_tile(p.x, p.y, TILE_RESIDENTIAL_2_ZONE);
                    }
                }
            }

            break;
        case MODE_BUILD_LANDFILL:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y]) && map_value[p.x][p.y] != TILE_LANDFILL_3) {
                        build_tile(p.x, p.y, TILE_LANDFILL_1);
                    }
                }
            }

            break;
        case MODE_BUILD_RETAIL:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y])) {
                        build_tile(p.x, p.y, TILE_RETAIL_ZONE);
                    }
                }
            }

            break;
        case MODE_BUILD_POWER_SOLAR:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y])) {
                        build_tile(p.x, p.y, TILE_POWER_SOLAR);
                        power_avalible += getPowerProduction(TILE_POWER_SOLAR);
                    }
                }
            }

            break;
        case MODE_BUILD_POWER_WIND:;
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    if(canBuildOn(map_value[p.x][p.y])) {
                        build_tile(p.x, p.y, TILE_POWER_WIND);
                        power_avalible += getPowerProduction(TILE_POWER_WIND);
                    }
                }
            }

            break;
        case MODE_BUILD_DESTROY:
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    build_tile(p.x, p.y, TILE_GRASS); //TODO Do a proper destroy function
                }
            }

            break;
        case MODE_BUILD_HOSPITAL:
            build_tile(plan_up.x, plan_up.y, TILE_SERVICE_BUILDING_HOSPITAL);
            setMode(MODE_VIEW);
            break;
        case MODE_BUILD_POLICE:
            build_tile(plan_up.x, plan_up.y, TILE_SERVICE_BUILDING_POLICE);
            setMode(MODE_VIEW);
            break;
        case MODE_BUILD_POWER_GAS:;
            if(canBuildOn(map_value[plan_up.x][plan_up.y]) && canBuildOn(map_value[plan_up.x+1][plan_up.y]) 
                    && canBuildOn(map_value[plan_up.x][plan_up.y+1]) && canBuildOn(map_value[plan_up.x+1][plan_up.y+1])) {
                if(canAfford(getCost(TILE_POWER_GAS_P1)+getCost(TILE_POWER_GAS_P2)+
                        getCost(TILE_POWER_GAS_P3)+getCost(TILE_POWER_GAS_P4))) {
                    power_avalible += getPowerProduction(TILE_POWER_GAS_P1);
                    power_avalible += getPowerProduction(TILE_POWER_GAS_P2);
                    power_avalible += getPowerProduction(TILE_POWER_GAS_P3);
                    power_avalible += getPowerProduction(TILE_POWER_GAS_P4);
                    build_tile(plan_up.x, plan_up.y, TILE_POWER_GAS_P1);
                    build_tile(plan_up.x+1, plan_up.y, TILE_POWER_GAS_P2);
                    build_tile(plan_up.x, plan_up.y+1, TILE_POWER_GAS_P3);
                    build_tile(plan_up.x+1, plan_up.y+1, TILE_POWER_GAS_P4);
                }
            }
            break;
        case MODE_BUILD_POWER_NUCLEAR:;
            if(canBuildOn(map_value[plan_up.x][plan_up.y]) && canBuildOn(map_value[plan_up.x+1][plan_up.y]) 
                    && canBuildOn(map_value[plan_up.x][plan_up.y+1]) && canBuildOn(map_value[plan_up.x+1][plan_up.y+1])) {
                if(canAfford(getCost(TILE_POWER_NUCLEAR_P1)+getCost(TILE_POWER_NUCLEAR_P2)+
                        getCost(TILE_POWER_NUCLEAR_P3)+getCost(TILE_POWER_NUCLEAR_P4))) {
                    power_avalible += getPowerProduction(TILE_POWER_NUCLEAR_P1);
                    build_tile(plan_up.x, plan_up.y, TILE_POWER_NUCLEAR_P1);
                    build_tile(plan_up.x+1, plan_up.y, TILE_POWER_NUCLEAR_P2);
                    build_tile(plan_up.x, plan_up.y+1, TILE_POWER_NUCLEAR_P3);
                    build_tile(plan_up.x+1, plan_up.y+1, TILE_POWER_NUCLEAR_P4);
                    setMode(MODE_VIEW);
                }
            }
            break;
        case MODE_BUILD_SCHOOL:;
            if(canBuildOn(map_value[plan_up.x][plan_up.y]) && canBuildOn(map_value[plan_up.x+1][plan_up.y]) 
                    && canBuildOn(map_value[plan_up.x][plan_up.y+1]) && canBuildOn(map_value[plan_up.x+1][plan_up.y+1])) {
                if(canAfford(getCost(TILE_COMMUNITY_SCHOOL_P1)+getCost(TILE_COMMUNITY_SCHOOL_P2)+
                        getCost(TILE_COMMUNITY_SCHOOL_P3)+getCost(TILE_COMMUNITY_SCHOOL_P4))) {
                    build_tile(plan_up.x, plan_up.y, TILE_COMMUNITY_SCHOOL_P1);
                    build_tile(plan_up.x+1, plan_up.y, TILE_COMMUNITY_SCHOOL_P2);
                    build_tile(plan_up.x, plan_up.y+1, TILE_COMMUNITY_SCHOOL_P3);
                    build_tile(plan_up.x+1, plan_up.y+1, TILE_COMMUNITY_SCHOOL_P4);
                }
            }
            break;
        case MODE_BUILD_STADIUM:;
            bool canBuildOn_test = plan_up.x > 0 && plan_up.y > 0 && plan_up.x+4 < MAP_SIZE_X && plan_down.y+4 < MAP_SIZE_Y;
            int x1, y1;
            for(x1 = 0; x1<4; x1++) {
                for(y1 = 0; y1<4; y1++) {
                    if(!canBuildOn(map_value[plan_up.x+x1][plan_up.y+y1])) {
                        canBuildOn_test = false;
                        break;
                    }
                }
            }
            if(canBuildOn_test) {
                if(canAfford(getCost(TILE_CULTURE_STADIUM_P1))) {
                    for(x1 = 0; x1<4; x1++) {
                        for(y1 = 0; y1<4; y1++) {
                            build_tile(plan_up.x+x1, plan_up.y+y1, TILE_CULTURE_STADIUM_P1);
                        }
                    }
                    build_tile(plan_up.x+3, plan_up.y+0, TILE_CULTURE_STADIUM_P2);
                    build_tile(plan_up.x+3, plan_up.y+1, TILE_CULTURE_STADIUM_P2);
                    build_tile(plan_up.x+3, plan_up.y+2, TILE_CULTURE_STADIUM_P2);
                    build_tile(plan_up.x+3, plan_up.y+3, TILE_CULTURE_STADIUM_P3);
                    setMode(MODE_VIEW);
                }
            }
            break;
        case MODE_BUILD_PARK:;
            if(canBuildOn(map_value[plan_up.x][plan_up.y]) && canBuildOn(map_value[plan_up.x+1][plan_up.y]) 
                    && canBuildOn(map_value[plan_up.x][plan_up.y+1]) && canBuildOn(map_value[plan_up.x+1][plan_up.y+1])) {
                if(canAfford(getCost(TILE_CULTURE_PARK_P1)+getCost(TILE_CULTURE_PARK_P2)+
                        getCost(TILE_CULTURE_PARK_P3)+getCost(TILE_CULTURE_PARK_P4))) {
                    build_tile(plan_up.x, plan_up.y, TILE_CULTURE_PARK_P1);
                    build_tile(plan_up.x+1, plan_up.y, TILE_CULTURE_PARK_P2);
                    build_tile(plan_up.x, plan_up.y+1, TILE_CULTURE_PARK_P3);
                    build_tile(plan_up.x+1, plan_up.y+1, TILE_CULTURE_PARK_P4);
                }
            }
            break;
        default:
            break;
    }

    ready_to_place = false;
    plan_down.x = 0;
    plan_down.y = 0;
}

bool build_tile(int x, int y, TILE_TYPE t)
{
    if(x <= 0 || y <= 0 || x >= MAP_SIZE_X || y >= MAP_SIZE_Y) return false;

    if(canAfford(getCost(t)) && power_avalible >= reqired_power + getPowerUsage(t)) {

        if(t == TILE_SERVICE_BUILDING_HOSPITAL) addHospitalToCount();
        else if(t == TILE_SERVICE_BUILDING_POLICE) addPoliceToCount();
        else if(t == TILE_COMMUNITY_SCHOOL_P1) addSchoolToCount();

        map_value[x][y] = t;
        changeBalance(-getCost(t));
        reqired_power += getPowerUsage(t);
        return true;
    } else {
        return false;
    }
}

bool grid_supplied(int x, int y, TILE_TYPE changeTo)
{
    bool road = isRoad(map_value[x+1][y]) || isRoad(map_value[x+1][y+1]) || isRoad(map_value[x+1][y-1]) || 
                isRoad(map_value[x-1][y]) || isRoad(map_value[x-1][y+1]) || isRoad(map_value[x-1][y-1]);
    bool power = (power_avalible >= reqired_power-getPowerUsage(map_value[x][y])+getPowerUsage(changeTo));
    return road && power;
}

bool build_prob_check(TILE_TYPE t)
{
    int prob;
    switch(t) {
        case TILE_RESIDENTIAL_1_ZONE:
        case TILE_RESIDENTIAL_2_ZONE:
            prob = build_prob;
            if(getNumberOfHospitals() == 0) prob *= 10; //Who would move somewhere without a hospital?
            if(populationPerPolice() > target_population_per_police) prob *= 10;
            if(populationPerSchool() > target_population_per_school) prob *= 4;
            if(!enoughWasteDisposal()) prob *= 10;
            break;
        case TILE_RESIDENTIAL_1_BUILDING:
        case TILE_RESIDENTIAL_2_BUILDING:
        case TILE_RETAIL_BUILDING:
            prob = build_finish_prob;
            break;
        case TILE_RETAIL_ZONE:;
            // How many shops we need to get to the optimum number
            float shops_short_by = ((float)getPopulation()/(float)target_population_per_shop) - (float)number_of_shops;
            if(shops_short_by > 0)  prob =  1500;
            else                    prob = 15000;

            if(!enoughWasteDisposal())  prob *= 10;

            break;
        default:
            prob = build_finish_prob;
            break;
    }

    return rand()%prob==0;
}

void map_update()
{
    int x, y, pop = 0, shopC = 0, waste_disposal_capacity=0;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {

            pop += getTilePopulation(map_value[x][y]);

            if(map_value[x][y] == TILE_LANDFILL_1 || map_value[x][y] == TILE_LANDFILL_2) {
                waste_disposal_capacity += 1;
            }

            if(map_value[x][y] == TILE_RETAIL_B1) shopC += 1;

            switch(map_value[x][y]) {
                case TILE_RESIDENTIAL_1_ZONE:
                    if(grid_supplied(x, y, TILE_RESIDENTIAL_1_BUILDING) && build_prob_check(TILE_RESIDENTIAL_1_ZONE)) {
                        //map_value[x][y] = TILE_RESIDENTIAL_1_BUILDING;
                        build_tile(x, y, TILE_RESIDENTIAL_1_BUILDING);
                        reqired_power = reqired_power - getPowerUsage(TILE_RESIDENTIAL_1_ZONE);
                    }
                    break;
                case TILE_RESIDENTIAL_1_BUILDING:
                    if(grid_supplied(x, y, TILE_RESIDENTIAL_1_B1) && build_prob_check(TILE_RESIDENTIAL_1_BUILDING)) {
                        //map_value[x][y] = TILE_RESIDENTIAL_1_B1;
                        build_tile(x, y, TILE_RESIDENTIAL_1_B1);
                        reqired_power = reqired_power - getPowerUsage(TILE_RESIDENTIAL_1_BUILDING);
                    }
                    break;
                case TILE_RESIDENTIAL_2_ZONE:
                    if(grid_supplied(x, y, TILE_RESIDENTIAL_2_BUILDING) && build_prob_check(TILE_RESIDENTIAL_2_ZONE)) { 
                        //map_value[x][y] = TILE_RESIDENTIAL_2_BUILDING;
                        build_tile(x, y, TILE_RESIDENTIAL_2_BUILDING);
                        reqired_power = reqired_power - getPowerUsage(TILE_RESIDENTIAL_2_ZONE);
                    }
                    break;
                case TILE_RESIDENTIAL_2_BUILDING:
                    if(grid_supplied(x, y, TILE_RESIDENTIAL_2_B1) && build_prob_check(TILE_RESIDENTIAL_2_BUILDING)) {
                        //map_value[x][y] = TILE_RESIDENTIAL_2_B1;
                        build_tile(x, y, TILE_RESIDENTIAL_2_B1);
                        reqired_power = reqired_power - getPowerUsage(TILE_RESIDENTIAL_2_BUILDING);
                    }
                    break;
                case TILE_RETAIL_ZONE:
                    if(grid_supplied(x, y, TILE_RETAIL_BUILDING) && build_prob_check(TILE_RETAIL_ZONE)) { 
                        //map_value[x][y] = TILE_RESIDENTIAL_2_BUILDING;
                        build_tile(x, y, TILE_RETAIL_BUILDING);
                        reqired_power = reqired_power - getPowerUsage(TILE_RETAIL_ZONE);
                    }
                    break;
                case TILE_RETAIL_BUILDING:
                    if(grid_supplied(x, y, TILE_RETAIL_B1) && build_prob_check(TILE_RETAIL_BUILDING)) {
                        //map_value[x][y] = TILE_RESIDENTIAL_2_B1;
                        build_tile(x, y, TILE_RETAIL_B1);
                        reqired_power = reqired_power - getPowerUsage(TILE_RETAIL_BUILDING);
                    }
                    break;
                case TILE_LANDFILL_1:
                    if(rand()%landfill_fill_prob==0) {
                        build_tile(x, y, TILE_LANDFILL_2);
                    }
                    break;
                case TILE_LANDFILL_2:
                    if(rand()%landfill_fill_prob==0) {
                        build_tile(x, y, TILE_LANDFILL_3);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    setPopulation(pop);
    number_of_shops = shopC;
    setWasteDisposalCapacity(waste_disposal_capacity);
}

void inc_balance()
{
    int x, y;
    int balanceChange = 0;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            balanceChange += getIncome(map_value[x][y]);
        }
    }
    lastBalanceChange = balanceChange;
    changeBalance(balanceChange);
}

int main(int argc, char* argv[]) 
{
    SDL_Window *window;                    // Declare a pointer

    if(init_SDL_all() != 0) {
        return logSDLError("SDL init");
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        WINDOW_NAME,                       // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL  | SDL_WINDOW_RESIZABLE                  // flags - see below
    );

    if (window == NULL) {
        return logSDLError("Could not create window");
    }

    SDL_Renderer* ren;

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == NULL) {
        return logSDLError("Could not create renderer");
    }

    srand(time(NULL));

    if(!init_drawing(ren)) exit(1);

    initClips();
    fill_map();
    
    SDL_Event e;
    bool quit = false;
    while (!quit){

        SDL_Delay(FRAME_TIME_DELAY);
        SDL_GetWindowSize(window, &window_size_x, &window_size_y);

        map_update();
        if(--balanceChangeCounter == 0) {
            balanceChangeCounter = balanceChangeCounterStart;
            inc_balance();
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym){
                    case SDLK_q:
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDLK_LEFT:
                        screen_x += 30;
                        break;
                    case SDLK_RIGHT:
                        screen_x -= 30;
                        break;
                    case SDLK_UP:
                        screen_y += 30;
                        break;
                    case SDLK_DOWN:
                        screen_y -= 30;
                        break;
                    case SDLK_ESCAPE:
                        if(ready_to_place) {
                            ready_to_place = false;
                            plan_down.x = 0;
                            plan_down.y = 0;
                        } else {
                            mode = MODE_VIEW;
                        }
                        break;
                    case SDLK_RETURN:
                        if(ready_to_place) placePlannedBuild();
                        break;
                    default:
                        break;
                }
            } else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                down_point.x = e.button.x;
                down_point.y = e.button.y;
                if((mode == MODE_BUILD_ROAD || mode == MODE_BUILD_RESIDENTIAL_1 || mode == MODE_BUILD_RESIDENTIAL_2 
                        || mode == MODE_BUILD_DESTROY || mode == MODE_BUILD_RETAIL || mode == MODE_BUILD_POWER_SOLAR
                        || mode == MODE_BUILD_HOSPITAL || mode == MODE_BUILD_POWER_GAS || mode == MODE_BUILD_POLICE
                        || mode == MODE_BUILD_POWER_WIND || mode == MODE_BUILD_SCHOOL || mode == MODE_BUILD_LANDFILL
                        || mode == MODE_BUILD_POWER_NUCLEAR || mode == MODE_BUILD_STADIUM || mode == MODE_BUILD_PARK)) {
                    Point d;
                    mouseToGrid(down_point.x, down_point.y, &d);
                    updating_plan = true;
                    ready_to_place = true;
                    plan_down.x = d.x;
                    plan_down.y = d.y;
                }
            } else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                up_point.x = e.button.x;
                up_point.y = e.button.y;
                updating_plan = false;

                if( !touch_HUD(&down_point, &up_point)) {
                    Point u, d;
                    mouseToGrid(up_point.x, up_point.y, &u);
                    mouseToGrid(down_point.x, down_point.y, &d);
                    
                    switch(mode) {
                        case MODE_BUILD_RESIDENTIAL_1:
                        case MODE_BUILD_RESIDENTIAL_2:
                        case MODE_BUILD_LANDFILL:
                        case MODE_BUILD_RETAIL:
                        case MODE_BUILD_POWER_SOLAR:
                        case MODE_BUILD_POWER_WIND:
                        case MODE_BUILD_ROAD:
                        case MODE_BUILD_HOSPITAL:
                        case MODE_BUILD_POLICE:
                        case MODE_BUILD_POWER_GAS:
                        case MODE_BUILD_POWER_NUCLEAR:
                        case MODE_BUILD_SCHOOL:
                        case MODE_BUILD_STADIUM:
                        case MODE_BUILD_PARK:
                            planRoad(u, plan_down);
                            break;
                        case MODE_BUILD_DESTROY:
                            if(u.x == d.x && u.y == d.y) {
                                build_tile(u.x, u.y, TILE_GRASS);
                            }
                            break;
                        default:
                            break;
                    }
                    //map_value[u.x][u.y] = map_value[u.x][u.y]==0 ? 1 : 0;
                } else {
                    updating_plan = false;
                    ready_to_place = false;
                    plan_down.x = 0;
                    plan_down.y = 0;
                }

            } else if(e.type == SDL_MOUSEMOTION) {
                if(updating_plan) {
                    Point u;
                    mouseToGrid(e.button.x, e.button.y, &u);
                    plan_up = u;
                }
            }
        }

        SDL_RenderClear(ren);
        draw_city(ren);
        draw_HUD(ren);
        SDL_RenderPresent(ren);
    }

    destroy_drawing();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

	return 0;
}
