#include <stdbool.h>
#include "mouse_functions.h"
#include "city_master.h"
#include "drawing_functions.h"
#include "menu_manager.h"

#define ABS(X) (((X)>0) ? (X) : (-(X)))
#define DRAG_SENSITIVITY 5

extern int window_size_x;
extern int window_size_y;
extern bool show_sidebar;

bool check_touch_HUD(Point *p)
{
    if(p->x > window_size_x-30 && p->y < 30) return true;
    return check_touch_menu(p);
}

bool touch_HUD(Point *down, Point *up)
{
    if(up->x > window_size_x-100-80 && up->y < 30 && up->x < window_size_x-80) {
        show_sidebar = !show_sidebar;
        return true;
    }
    return touch_menu(down, up);
}

void check_hover(Point *p)
{
    hover_menu(p);
}
