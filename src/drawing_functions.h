#include <stdbool.h>
#include "SDL_functions.h"
#include "draw_utils.h"
#include "tile_info.h"

#define BUILDBAR_TILE_SPACING 36
#define BUILDBAR_TILE_START 40

bool init_drawing(SDL_Renderer* ren);
void destroy_drawing();
void drawTile(SDL_Renderer* ren, Point *p, SDL_Rect *clip);
void draw_city(SDL_Renderer* ren);
void draw_HUD(SDL_Renderer* ren);
