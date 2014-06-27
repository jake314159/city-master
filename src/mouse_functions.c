#include <stdio.h>
#include "mouse_functions.h"
#include "city_master.h"
#include "drawing_functions.h"
#include "menu_manager.h"

#define ABS(X) (((X)>0) ? (X) : (-(X)))
#define DRAG_SENSITIVITY 5

bool check_touch_HUD(Point *p)
{
    return check_touch_menu(p);
}

bool touch_HUD(Point *down, Point *up)
{
    return touch_menu(down, up);

    //return false; //Didn't click on anything in the HUD
}
