#include <stdio.h>
#include "mouse_functions.h"
#include "city_master.h"
#include "drawing_functions.h"

#define ABS(X) (((X)>0) ? (X) : (-(X)))
#define DRAG_SENSITIVITY 5

bool touch_HUD(Point *down, Point *up)
{
    if(ABS(down->x - up->x) <= DRAG_SENSITIVITY && ABS(down->y - up->y) <= DRAG_SENSITIVITY) {
        //It was a click
        if(up->x < 32) {
            // It was on the left bar
            int itemClicked = (up->y - BUILDBAR_TILE_START+BUILDBAR_TILE_SPACING)/(BUILDBAR_TILE_SPACING);
            printf("Clicked on item %d\n", itemClicked);
            bool valid_item;
            switch(itemClicked) {
                case 0:
                    setMode(MODE_BUILD_RESIDENTIAL_1);
                    valid_item = true;
                    break;
                case 1:
                    setMode(MODE_BUILD_ROAD);
                    valid_item = true;
                    break;
                case 2:
                    setMode(MODE_BUILD_DESTROY);
                    break;
                default:
                    valid_item = false;
            }
            return valid_item;
        }
    }

    return false; //Didn't click on anything in the HUD
}
