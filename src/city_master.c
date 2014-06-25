#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "city_master.h"
#include "SDL_functions.h"
#include "tile_info.h"
#include "draw_utils.h"

#define FRAME_TIME_DELAY 20

const char* WINDOW_NAME = "City Master";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int screen_x, screen_y = 0;
int map_value[MAP_SIZE_X][MAP_SIZE_Y] = {0};

MODE mode = MODE_VIEW;

Point down_point;
Point up_point;

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
    map_value[u.x][u.y] = typeOfRoad(isRoad(map_value[u.x][u.y-1]), isRoad(map_value[u.x+1][u.y]), 
                                isRoad(map_value[u.x][u.y+1]), isRoad(map_value[u.x-1][u.y]));
}

void placeRoad(Point u)
{
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
        SDL_WINDOW_OPENGL                  // flags - see below
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
                        mode = MODE_VIEW;
                        break;
                    default:
                        break;
                }
            } else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                down_point.x = e.button.x;
                down_point.y = e.button.y;
                //
            } else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                up_point.x = e.button.x;
                up_point.y = e.button.y;

                if( !touch_HUD(&down_point, &up_point)) {
                    Point u, d;
                    mouseToGrid(up_point.x, up_point.y, &u);
                    mouseToGrid(down_point.x, down_point.y, &d);
                    if(u.x == d.x && u.y == d.y) {
                        switch(mode) {
                            case MODE_BUILD_RESIDENTIAL_1:
                                map_value[u.x][u.y] = TILE_BUILDING;
                                break;
                            case MODE_BUILD_ROAD://map_value[MAP_SIZE_X][MAP_SIZE_Y] 
                                if(u.x >1 && u.y>1 && u.x < MAP_SIZE_X-1 && u.y < MAP_SIZE_Y-1) {
                                // if not on edge of map
                                    placeRoad(u);
                                }
                                break;
                            default:
                                break;
                        }
                        //map_value[u.x][u.y] = map_value[u.x][u.y]==0 ? 1 : 0;
                    }
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
