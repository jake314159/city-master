
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "SDL_functions.h"

#define FRAME_TIME_DELAY 20

// 65x100 but grid size is 50px pre isometric transform
#define GRID_TILE_SIZE 49
//50

typedef struct {
  int x, y;
} Point;

const char* WINDOW_NAME = "Tetris clone";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int fontSize = 48;
const char* fontFile = "fonts/sample.ttf";

//const int MAP_SIZE_X = 32;
//const int MAP_SIZE_Y = 32;
#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

SDL_Rect clip_grass;
SDL_Rect clip_building;
SDL_Rect clip_highlight;
SDL_Texture *sheet;
TTF_Font *font;

int screen_x, screen_y = 0;
int map_value[MAP_SIZE_X][MAP_SIZE_Y] = {0};

Point down_point;
Point up_point;

Point isoTo2D(Point *p)
{
    int tempX, tempY;
    tempX = (2 * p->y + p->x) / 2;
    tempY = (2 * p->y - p->x) / 2;
    p->x = tempX;
    p->y = tempY;
}

/*Point isoTo2D(Point *p)
{
    int tempX, tempY;
    tempX = (2 * p->y + p->x) / 2;
    tempY = p->y - (p->x/2);
    p->x = tempX;
    p->y = tempY;
}*/
	
	
Point twoDToIso(Point *p)
{
    int tempX, tempY;
    tempX = p->x - p->y;
    tempY = (p->x + p->y) / 2;
    p->x = tempX;
    p->y = tempY;
}

void drawTile(SDL_Renderer* ren, Point *p, SDL_Rect *clip)
{
    renderTextureClip(sheet, ren, p->x, (p->y - clip->h), clip); //
}

void draw_city(SDL_Renderer* ren)
{
    Point p;
    int x,y;
    for(x=1; x<=MAP_SIZE_X; x++) {
        for(y=1;y<=MAP_SIZE_Y;y++) {
            p.x = x*GRID_TILE_SIZE;
            p.y = y*GRID_TILE_SIZE;
            //printf("(%d,%d) -> ", p.x, p.y);
            twoDToIso(&p);
            //printf("(%d,%d)\n", p.x, p.y);
            p.x += screen_x;
            p.y += screen_y;
            if(map_value[x][y] != 0) {
                drawTile(ren, &p, &clip_building);
            } else {
                drawTile(ren, &p, &clip_grass);
            }
        }
    }
    p.x = down_point.x*GRID_TILE_SIZE;
    p.y = down_point.y*GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(&p);
    //printf("(%d,%d)\n", p.x, p.y);
    p.x += screen_x;
    p.y += screen_y;
    drawTile(ren, &p, &clip_highlight);

    p.x = up_point.x*GRID_TILE_SIZE;
    p.y = up_point.y*GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(&p);
    //printf("(%d,%d)\n", p.x, p.y);
    p.x += screen_x;
    p.y += screen_y;
    drawTile(ren, &p, &clip_highlight);
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

    font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL){
		return logSDLError("TTF_OpenFont");
	}

    sheet = loadTexture("images/tile_sheet.png", ren);

    clip_grass.x = 0;
    clip_grass.y = 0;
    clip_grass.w = 100;
    clip_grass.h = 65;

    clip_highlight.x = 200;
    clip_highlight.y = 0;
    clip_highlight.w = 100;
    clip_highlight.h = 65;

    clip_building.x = 100;
    clip_building.y = 0;
    clip_building.w = 100;
    clip_building.h = 65*2;
    
    SDL_Event e;
    bool quit = false;
    printf("Now entering the main game loop\n");
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
                Point mouse;
                mouse.x = e.button.x;
                mouse.y = e.button.y;
                //printf("## RAW location is (%d, %d)\n", mouse.x, mouse.y);
                mouse.x -= screen_x;
                mouse.y -= screen_y;
                mouse.y += 65;
                mouse.x -= GRID_TILE_SIZE/2;
                mouse.y -= GRID_TILE_SIZE/2;
                isoTo2D(&mouse);
                //printf("\t\t\tLocation is (%d, %d)\n", mouse.x, mouse.y);
                mouse.x = (int)((float)mouse.x/(float)GRID_TILE_SIZE);
                mouse.y = (int)((float)(mouse.y-(GRID_TILE_SIZE/2))/(float)GRID_TILE_SIZE);
                //printf("Location is (%d, %d)\t%d\n", mouse.x, mouse.y, (mouse.x%4==0 && mouse.y%4==0));
                down_point.x = mouse.x;
                down_point.y = mouse.y;
                down_point.y += 1;
            } else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                Point mouse;
                mouse.x = e.button.x;
                mouse.y = e.button.y;
                mouse.x -= screen_x;
                mouse.y -= screen_y;
                mouse.y += 65;
                mouse.x -= GRID_TILE_SIZE/2;
                mouse.y -= GRID_TILE_SIZE/2;
                isoTo2D(&mouse);
                mouse.x = (int)((float)mouse.x/(float)GRID_TILE_SIZE);
                mouse.y = (int)((float)(mouse.y-(GRID_TILE_SIZE/2))/(float)GRID_TILE_SIZE);
                up_point.x = mouse.x;
                up_point.y = mouse.y;
                up_point.y += 1;

                if(up_point.x == down_point.x && up_point.y == down_point.y) {
                    map_value[up_point.x][up_point.y] = map_value[up_point.x][up_point.y]==0 ? 1 : 0;
                }
            }
        }

        SDL_RenderClear(ren);
        draw_city(ren);
        SDL_RenderPresent(ren);
    }

    

    SDL_DestroyTexture(sheet);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
}
