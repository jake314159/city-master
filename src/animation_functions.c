#include "animation_functions.h"
#include "city_master.h"
#include "tile_info.h"
#include "drawing_functions.h"
#include "resource_manager.h"


#define MAX_NUMBER_OF_CARS 100
#define EVEN_MASK 1
#define _BV(X) (1 << (X))


/*
 * What is the significance of SIN(26.5) and SIN(63.5) ?
 *     With isometric 3d each plain is normaly separated by 120 degrees
 *     which will mean when you work it out that to work out movement
 *     accross the flat plain you will need to be using SIN(30) and 
 *     SIN(60) to sort out the angles. The tiles used however use a 
 *     slightly different definition of isometric which means you should
 *     substitute SIN(30) for SIN(26.5) and SIN(60) for SIN(63.5)
 */
#define SIN_30 0.5f
#define SIN_26_5 0.4461978131f
#define SIN_60 0.8660254f
#define SIN_63_5 0.8949343616f

typedef enum {
    NORTH=0, EAST=1, SOUTH=2, WEST=3
} DIR;

typedef struct {
    uint16_t x;     // Grid location
    uint16_t y;
    DIR dir;        // If there is a junction which way are we going
    uint8_t img;    // What car image to use
    uint8_t frame;  // Frame currently on
} ANIMATION_CAR;

typedef struct {
    int ofset_x, ofset_y;
} OFSET;

extern TILE_TYPE map_value[MAP_SIZE_X][MAP_SIZE_Y];

ANIMATION_CAR cars[MAX_NUMBER_OF_CARS];
int number_of_cars = 0;
SDL_Rect car_clips[4]; //NORTH, EAST, SOUTH, WEST

DIR pick_car_direction(ANIMATION_CAR *car)
{
    int dirOptions = 0;
    if((_BV(NORTH) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(SOUTH) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(EAST) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(WEST) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;

    int optionPicked = rand()%dirOptions;
    
    if((_BV(NORTH) & (map_value[car->x][car->y]-199)) != 0) {
        if(optionPicked == 0) return NORTH;
        else                  optionPicked--;
    }
    if((_BV(SOUTH) & (map_value[car->x][car->y]-199)) != 0) {
        if(optionPicked == 0) return SOUTH;
        else                  optionPicked--;
    }
    if((_BV(EAST) & (map_value[car->x][car->y]-199)) != 0) {
        if(optionPicked == 0) return EAST;
        else                  optionPicked--;
    }
    if((_BV(WEST) & (map_value[car->x][car->y]-199)) != 0) {
        if(optionPicked == 0) return WEST;
        else                  optionPicked--;
    }

    return SOUTH;
}

void remove_car()
{
    number_of_cars--;
}

void add_car()
{
    if(number_of_cars == MAX_NUMBER_OF_CARS) return; //

    bool filled = false;
    int x, y, i;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            if(isRoad(map_value[x][y]) && (!filled || (rand()&63)==0)) {
                cars[number_of_cars].x = x;
                cars[number_of_cars].y = y;
                cars[number_of_cars].dir = pick_car_direction(&cars[number_of_cars]); //TODO
                cars[number_of_cars].img = 0;
                cars[number_of_cars].frame = 0;
                number_of_cars++;
                filled = true;;
            }
        }
    }
}

void init_animation()
{
    int i;
    for(i=0; i<4; i++) {
        car_clips[i].x = 1532;
        car_clips[i].y = 20*i;
        car_clips[i].w = 20;
        car_clips[i].h = 20;
    }
}

void getOfset(int car_number, OFSET *ofset)
{
    //Ofsets found by eye so are magic numbers
    //TODO Calculate the values better
    switch(cars[car_number].dir) {
        case NORTH:
            ofset->ofset_x = -10-SIN_63_5*25 + (SIN_63_5*(cars[car_number].frame+4)*2.5f);
            ofset->ofset_y = -30+SIN_26_5*25 - (SIN_26_5*(cars[car_number].frame+4)*2.5f);
            break;
        case SOUTH:
            ofset->ofset_x = 50-SIN_63_5*10 - (SIN_63_5*cars[car_number].frame*2.5f);
            ofset->ofset_y = -45+SIN_26_5*10 + (SIN_26_5*cars[car_number].frame*2.5f);
            break;
        case EAST:
            ofset->ofset_x = -13+SIN_63_5*5 + (SIN_63_5*(cars[car_number].frame-2)*2.5f);
            ofset->ofset_y = -60+SIN_26_5*25 + (SIN_26_5*(cars[car_number].frame-2)*2.5f);
            break;
        case WEST:
            ofset->ofset_x = 23 - (SIN_63_5*(cars[car_number].frame+2)*2.5f);
            ofset->ofset_y = -15 - (SIN_26_5*(cars[car_number].frame+2)*2.5f);
            break;
    }

}

void turn(ANIMATION_CAR *car)
{
    int dirOptions = 0;
    if((_BV(NORTH) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(SOUTH) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(EAST) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;
    if((_BV(WEST) & (map_value[car->x][car->y]-199)) != 0) dirOptions += 1;

    if(dirOptions > 2 && (rand()&1)==0) { //X&1 == X%2
        int optionPicked = rand()%dirOptions;
        if((_BV(NORTH) & (map_value[car->x][car->y]-199)) != 0) {
            if(optionPicked == 0 && car->dir != SOUTH) car->dir = NORTH;
            else                  optionPicked--;
        }
        if((_BV(SOUTH) & (map_value[car->x][car->y]-199)) != 0) {
            if(optionPicked == 0 && car->dir != NORTH) car->dir = SOUTH;
            else                  optionPicked--;
        }
        if((_BV(EAST) & (map_value[car->x][car->y]-199)) != 0) {
            if(optionPicked == 0 && car->dir != WEST) car->dir = EAST;
            else                  optionPicked--;
        }
        if((_BV(WEST) & (map_value[car->x][car->y]-199)) != 0) {
            if(optionPicked == 0 && car->dir != EAST) car->dir = WEST;
            else                  optionPicked--;
        }
    }
}

void move_car_to_next_pos(ANIMATION_CAR *car)
{
    car->frame = 0;
    int oldX = car->x;
    int oldY = car->y;
    switch(car->dir) {
        case NORTH:
            car->y -= 1;
            break;
        case SOUTH:
            car->y += 1;
            break;
        case EAST:
            car->x += 1;
            break;
        case WEST:
            car->x -= 1;
            break;
    }
    //If there is a car in the new x,y values wait for it to move
    int i;
    for(i=0; i<number_of_cars; i++) {
        if(&cars[i] != car && (cars[i].x == car->x && cars[i].y == car->y) && !( 
            (cars[i].dir == SOUTH && car->dir == NORTH) ||
            (cars[i].dir == NORTH && car->dir == SOUTH) ||
            (cars[i].dir == EAST && car->dir == WEST) ||
            (cars[i].dir == WEST && car->dir == EAST)) 
            && (rand()&3)!=0) {
            car->x = oldX;
            car->y = oldY;
            car->frame = 22;
        }
    }
}

void draw_animation_tile(SDL_Renderer* ren, int x, int y)
{
    int i;
    for(i=0; i<number_of_cars; i++) {
        if(cars[i].x == x && cars[i].y ==y) {
            Point p = {cars[i].x, cars[i].y};
            //Point p2 = p;
            OFSET ofset;
            getOfset(i, &ofset);
            drawTileFromGridPointWithOfset(ren, &p, ofset.ofset_x, ofset.ofset_y, &car_clips[cars[i].img*4+cars[i].dir]);
            //draw_highlight(ren, &p2);
        }
    }
}

void draw_animation_overlay(SDL_Renderer* ren)
{
    //1 car per 500 people (on the road)
    if(number_of_cars*500 < getPopulation()) add_car();
    else if(number_of_cars*550 < getPopulation()) remove_car();

    int i;
    for(i=0; i<number_of_cars; i++) {
        if(cars[i].frame == 22) {
            turn(&cars[i]);
            move_car_to_next_pos(&cars[i]);
        } else {
            if(cars[i].frame == 11) { //half way through
                if( (_BV(cars[i].dir) & (map_value[cars[i].x][cars[i].y]-199)) == 0) {
                    // We are on a corner we should turn
                    cars[i].dir = pick_car_direction(&cars[i]);
                }
            } 
            cars[i].frame = (cars[i].frame+1);
        }
    }
}

