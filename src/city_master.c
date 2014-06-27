#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "city_master.h"
#include "SDL_functions.h"
#include "draw_utils.h"
#include "resource_manager.h"

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define FRAME_TIME_DELAY 20

const char* WINDOW_NAME = "City Master";
const int SCREEN_WIDTH = 900;//640;
const int SCREEN_HEIGHT = 620;//480;

int screen_x, screen_y = 0;
TILE_TYPE map_value[MAP_SIZE_X][MAP_SIZE_Y] = {0};

MODE mode = MODE_VIEW;

Point down_point;
Point up_point;

bool ready_to_place = false;
bool updating_plan = false;
Point plan_up;
Point plan_down;

int build_prob = 1500;
int build_finish_prob = 600;

extern int reqired_power;
extern int power_avalible;

int balanceChangeCounterStart = 100;
int balanceChangeCounter = 100;
int lastBalanceChange;

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

void placePlannedBuild()
{
    if(!ready_to_place) return;
    Point p, p2;
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
        case MODE_BUILD_DESTROY:
            for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                    p.x = x;
                    p.y = y;
                    build_tile(p.x, p.y, TILE_GRASS); //TODO Do a proper destroy function
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

    if(t == TILE_SERVICE_BUILDING_HOSPITAL) addHospitalToCount();


    if(canAfford(getCost(t)) && power_avalible >= reqired_power + getPowerUsage(t)) {
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
            break;
        case TILE_RESIDENTIAL_1_BUILDING:
        case TILE_RESIDENTIAL_2_BUILDING:
            prob = build_finish_prob;
            break;
        default:
            prob = build_finish_prob;
            break;
    }

    return rand()%prob==0;
}

void map_update()
{
    int x, y, pop;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {

            pop += getTilePopulation(map_value[x][y]);

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
                default:
                    break;
            }
        }
    }
    setPopulation(pop);
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
    
    SDL_Event e;
    bool quit = false;
    while (!quit){

        SDL_Delay(FRAME_TIME_DELAY);
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
                        screen_x += 10;
                        break;
                    case SDLK_RIGHT:
                        screen_x -= 10;
                        break;
                    case SDLK_UP:
                        screen_y += 10;
                        break;
                    case SDLK_DOWN:
                        screen_y -= 10;
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
                        || mode == MODE_BUILD_DESTROY)) {
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
                            if(u.x == d.x && u.y == d.y) {
                                ready_to_place = false; //as we are placing it
                                if(canBuildOn(map_value[u.x][u.y])) {
                                    build_tile(u.x, u.y, TILE_RESIDENTIAL_1_ZONE);
                                }
                            } else {
                                planRoad(u, d); //Plan to build a bilding is the same as planning a road -- //TODO RENAME
                            }
                            break;
                        case MODE_BUILD_RESIDENTIAL_2:
                            if(u.x == d.x && u.y == d.y) {
                                ready_to_place = false; //as we are placing it
                                if(canBuildOn(map_value[u.x][u.y])) {
                                    build_tile(u.x, u.y, TILE_RESIDENTIAL_2_ZONE);
                                }
                            } else {
                                planRoad(u, d); //Plan to build a bilding is the same as planning a road -- //TODO RENAME
                            }
                            break;
                        case MODE_BUILD_ROAD:
                            if(u.x == d.x && u.y == d.y) {
                                if(canBuildOn(map_value[u.x][u.y])) {
                                    placeRoad(u);
                                }
                            } else {
                                planRoad(u, d);
                            }
                            break;
                        case MODE_BUILD_DESTROY:
                            if(u.x == d.x && u.y == d.y) {
                                build_tile(u.x, u.y, TILE_GRASS);
                            }
                            break;
                        case MODE_BUILD_POWER_GAS:
                            if(u.x == d.x && u.y == d.y) {
                                if(canBuildOn(map_value[u.x][u.y]) && canBuildOn(map_value[u.x+1][u.y]) 
                                        && canBuildOn(map_value[u.x][u.y+1]) && canBuildOn(map_value[u.x+1][u.y+1])) {
                                    if(canAfford(getCost(TILE_POWER_GAS_P1)+getCost(TILE_POWER_GAS_P2)+
                                            getCost(TILE_POWER_GAS_P3)+getCost(TILE_POWER_GAS_P4))) {
                                        power_avalible += getPowerProduction(TILE_POWER_GAS_P1);
                                        power_avalible += getPowerProduction(TILE_POWER_GAS_P2);
                                        power_avalible += getPowerProduction(TILE_POWER_GAS_P3);
                                        power_avalible += getPowerProduction(TILE_POWER_GAS_P4);
                                        build_tile(u.x, u.y, TILE_POWER_GAS_P1);
                                        build_tile(u.x+1, u.y, TILE_POWER_GAS_P2);
                                        build_tile(u.x, u.y+1, TILE_POWER_GAS_P3);
                                        build_tile(u.x+1, u.y+1, TILE_POWER_GAS_P4);
                                    }
                                }
                            }
                            break;
                        case MODE_BUILD_HOSPITAL:
                            if(u.x == d.x && u.y == d.y) {
                                if(canBuildOn(map_value[u.x][u.y])) {
                                    build_tile(u.x, u.y, TILE_SERVICE_BUILDING_HOSPITAL);
                                }
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
}
