#include <stdbool.h>
#include "tile_info.h"
#include "draw_utils.h"

void draw_menu(SDL_Renderer* ren);
bool check_touch_menu(Point *p);
bool touch_menu(Point *down, Point *up);
void hover_menu(Point *p);
