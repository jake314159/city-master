#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "city_master.h"
#include "drawing_functions.h"
#include "route_finder.h"

extern TILE_TYPE map_value[MAP_SIZE_X][MAP_SIZE_Y];
extern int screen_x, screen_y;

#define REQUIRES_POLICE 1
#define REQUIRES_MEDICAL 2
#define REQUIRES_FIRE 4
#define EMERGENCY_TYPE_OFSET 4

#define NUMBER_OF_EMERGENCIES 1
typedef enum {
    NONE = 0,
    EMERGENCY_CAR_CRASH = (REQUIRES_POLICE | REQUIRES_MEDICAL | REQUIRES_FIRE) | (0 << EMERGENCY_TYPE_OFSET)
} EMERGENCY_TYPE;

SDL_Rect emergency_clip[NUMBER_OF_EMERGENCIES];

bool emergency_active = false;
int x;
int y;
EMERGENCY_TYPE type = NONE;
int counter;
int police_distance;
int medical_distance;
int fire_distance;

SDL_Rect emergency_notification_box = {0,0,200,150};

void init_emergency()
{
    printf("Car crash: %x\nSize of emergency: %d\n\n", EMERGENCY_CAR_CRASH, sizeof(EMERGENCY_TYPE));
    emergency_clip[(EMERGENCY_CAR_CRASH>>EMERGENCY_TYPE_OFSET)].x = 1652;
    emergency_clip[(EMERGENCY_CAR_CRASH>>EMERGENCY_TYPE_OFSET)].y = 0;
    emergency_clip[(EMERGENCY_CAR_CRASH>>EMERGENCY_TYPE_OFSET)].w = 100;
    emergency_clip[(EMERGENCY_CAR_CRASH>>EMERGENCY_TYPE_OFSET)].h = 130;
}

void set_service_distance()
{
    int x2, y2;
    int distanceSq_police = 1000000;
    int distanceSq_medical = 1000000;
    for(x2=1; x2<MAP_SIZE_X; x2++) {
        for(y2=1;y2<MAP_SIZE_Y; y2++) {
            if(map_value[x2][y2] == TILE_SERVICE_BUILDING_POLICE) {
                int disSqTemp = (x-x2)*(x-x2) + (y-y2)*(y-y2);
                if(disSqTemp < distanceSq_police) distanceSq_police = disSqTemp;
            }
            if(map_value[x2][y2] == TILE_SERVICE_BUILDING_HOSPITAL) {
                int disSqTemp = (x-x2)*(x-x2) + (y-y2)*(y-y2);
                if(disSqTemp < distanceSq_medical) distanceSq_medical = disSqTemp;
            }
        }
    }

    police_distance = (int)sqrt(distanceSq_police)>>3; //divide by 8
    medical_distance = (int)sqrt(distanceSq_medical)>>3;
    fire_distance = 10;//400;
}

// Not a very good random function but good enough for now
bool find_random_road(int *xTarget, int *yTarget)
{
    int number_of_roads = -1;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            if(isRoad(map_value[x][y])) {
                number_of_roads++;
            }
        }
    }
    if(number_of_roads <0 ) return false; //There are no roads

    int r = rand()%number_of_roads;
    int x, y;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            if(isRoad(map_value[x][y]) && --r == 0) {
                *xTarget = x;
                *yTarget = y;
                return true;
            }
        }
    }
}

void start_emergency()
{
    if(emergency_active) return;

    int random_number = rand()%1;
    switch(random_number) {
        case 0:
            type = EMERGENCY_CAR_CRASH;
            bool success = find_random_road(&x, &y);
            if(!success) return; //fail
            counter = 3000;
            break;
    }
    set_service_distance();
    emergency_active = true;
    printf("Emergency activated %x %d %d %d\n", type, x, y, counter);
}

void move_camera_to_emergency()
{
    if(!emergency_active) return;
    move_camera_to_grid_location(x, y);
}

bool contains_emergency(int x, int y)
{
    if(!emergency_active) return false;
}

bool active_emergency()
{
    return emergency_active;
}

void draw_emergency_box(SDL_Renderer* ren)
{
    int ofset_x=0, ofset_y=-40;
    Point p = {x, y};
    p.x *= GRID_TILE_SIZE;
    p.y *= GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(&p);
    //printf("(%d,%d)\n", p.x, p.y);
    p.x += screen_x;
    p.y += screen_y;
    p.x += ofset_x;
    p.y += ofset_y;
    emergency_notification_box.x = p.x;
    emergency_notification_box.y = p.y;
    //renderTextureClip(sheet, ren, (p.x - ((clip->w)>>1)), (p->y - clip->h), clip);
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
    SDL_RenderFillRect(ren, &emergency_notification_box);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
    emergency_notification_box.y += 30;
    emergency_notification_box.h -=30;
    SDL_RenderFillRect(ren, &emergency_notification_box);
    emergency_notification_box.h +=30;

    SDL_Color text_color = {0,0,0};
    p.x += 5;
    draw_string_default(ren, p.x, p.y, "Car crash");
    if((type | REQUIRES_POLICE) != 0) {
        p.y += 30;
        draw_string_default(ren, p.x, p.y, "Police");
        draw_int(ren, get_large_font(), text_color, p.x+100, p.y, police_distance,  "", "km");
    }
    if((type | REQUIRES_MEDICAL) != 0) {
        p.y += 30;
        draw_string_default(ren, p.x, p.y, "Ambulance");
        draw_int(ren, get_large_font(), text_color, p.x+100, p.y, medical_distance,  "", "km");
    }
    if((type | REQUIRES_FIRE) != 0) {
        p.y += 30;
        draw_string_default(ren, p.x, p.y, "Fire");
        draw_int(ren, get_large_font(), text_color, p.x+100, p.y, fire_distance,  "", "km");
    }
}

void draw_emergency(SDL_Renderer* ren)
{
    if(!emergency_active) return;
    Point p = {x, y};
    drawTileFromGridPoint(ren, &p, &emergency_clip[(type>>EMERGENCY_TYPE_OFSET)]);
    draw_emergency_box(ren);
}

// Gets ran once per frame
void update_emergency()
{
    if(!emergency_active) return;
    counter--;
    if(counter%100 ==0) {
        if(police_distance>0) police_distance--;
        if(medical_distance>0) medical_distance--;
        if(fire_distance>0) fire_distance--;
    }

    bool success = true;
    if((type | REQUIRES_POLICE) != 0 && police_distance != 0) success = false;
    else if((type | REQUIRES_MEDICAL) != 0 && medical_distance != 0) success = false;
    else if((type | REQUIRES_FIRE) != 0 && fire_distance != 0) success = false;
    
    if(success) {
        printf("Emergency delt with successfully\n");
        emergency_active = false;
    } else if(!success && counter <= 0) {
        printf("Emergency not delt with. FAIL!\n");
        emergency_active = false;
    }
}

