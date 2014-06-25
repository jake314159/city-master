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

Point down_point;
Point up_point;

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
                    case SDLK_ESCAPE:
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
                    default:
                        break;
                }
            } else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                mouseToGrid(e.button.x, e.button.y, &down_point);
            } else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                mouseToGrid(e.button.x, e.button.y, &up_point);

                if(up_point.x == down_point.x && up_point.y == down_point.y) {
                    map_value[up_point.x][up_point.y] = map_value[up_point.x][up_point.y]==0 ? 1 : 0;
                }
            }
        }

        SDL_RenderClear(ren);
        draw_city(ren);
        SDL_RenderPresent(ren);
    }

    destroy_drawing();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
}
