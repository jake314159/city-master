#include "menu_manager.h"
#include "city_master.h"
#include "drawing_functions.h"

#define ABS(X) (((X)>0) ? (X) : (-(X)))
#define DRAG_SENSITIVITY 5

#define MENU_LENGTH 5
#define MENU_LONGEST_SUBMENU 6
SPRITE menu[MENU_LENGTH][MENU_LONGEST_SUBMENU] = {
    {SPRITE_BUILD_ZONE_RES1, SPRITE_BUILD_ZONE_RES1, SPRITE_BUILD_ZONE_RES2, SPRITE_BUILD_ZONE_RETAIL, NULL_SPRITE},
    {SPRITE_BUILD_POWER_GENRAL, SPRITE_BUILD_POWER_GAS, SPRITE_BUILD_POWER_SOLAR, SPRITE_BUILD_POWER_WIND, NULL_SPRITE},
    {SPRITE_SERVICES_GENRAL, SPRITE_SERVICES_HOSPITAL, SPRITE_BUILD_SERVICES_POLICE, NULL_SPRITE},
    {SPRITE_BUILD_ROAD, NULL_SPRITE},
    {SPRITE_BUILD_DESTROY, NULL_SPRITE}
};

int openMenu = -1; //-1 == not open

void draw_menu(SDL_Renderer* ren)
{
    Point p;
    p.x = 0;
    p.y = BUILDBAR_TILE_START;
    int i;
    for(i=0; i<MENU_LENGTH; i++) {
        drawTile(ren, &p, getClip(SPRITE_BUILD_BACKGROUND));
        drawTile(ren, &p, getClip(menu[i][0]));
        p.y += BUILDBAR_TILE_SPACING; //tile spacing
    }

    p.x = BUILDBAR_TILE_SPACING;
    p.y = BUILDBAR_TILE_START + openMenu*BUILDBAR_TILE_SPACING;
    if(openMenu >=0) {
        i = 1;
        while(menu[openMenu][i] != NULL_SPRITE) {
            drawTile(ren, &p, getClip(SPRITE_BUILD_BACKGROUND));
            drawTile(ren, &p, getClip(menu[openMenu][i]));
            p.x += BUILDBAR_TILE_SPACING;
            i++;
        }
    }
    
}

void button_click(int menu_x, int menu_y, SPRITE sprite)
{
    if(menu_y > 0) {
        switch(sprite) {
            case SPRITE_BUILD_ZONE_RES1:
                setMode(MODE_BUILD_RESIDENTIAL_1);
                break;
            case SPRITE_BUILD_ZONE_RES2:
                setMode(MODE_BUILD_RESIDENTIAL_2);
                break;
            case SPRITE_BUILD_ZONE_RETAIL:
                setMode(MODE_BUILD_RETAIL);
                break;
            case SPRITE_BUILD_POWER_GAS:
                setMode(MODE_BUILD_POWER_GAS);
                break;
            case SPRITE_SERVICES_HOSPITAL:
                setMode(MODE_BUILD_HOSPITAL);
                break;
            case SPRITE_BUILD_POWER_SOLAR:
                setMode(MODE_BUILD_POWER_SOLAR);
                break;
            case SPRITE_BUILD_POWER_WIND:
                setMode(MODE_BUILD_POWER_WIND);
                break;
            case SPRITE_BUILD_SERVICES_POLICE:
                setMode(MODE_BUILD_POLICE);
                break;
            default:
                break;
        }
    } else {
        switch(sprite) {
            case SPRITE_BUILD_ROAD:
                setMode(MODE_BUILD_ROAD);
                break;
            case SPRITE_BUILD_DESTROY:
                setMode(MODE_BUILD_DESTROY);
                break;
            default:
                break;
        }
    }
}

bool check_touch_menu(Point *p)
{
    return p->x < 32;
}

bool touch_menu(Point *down, Point *up)
{
    if(ABS(down->x - up->x) <= DRAG_SENSITIVITY && ABS(down->y - up->y) <= DRAG_SENSITIVITY) {
        //It was a click
        int itemClicked = (up->y - BUILDBAR_TILE_START+BUILDBAR_TILE_SPACING)/(BUILDBAR_TILE_SPACING);
        if(up->x < 32) {
            // It was on the left bar
            bool valid_item_y = (itemClicked >=0 && itemClicked < MENU_LENGTH);
            if(valid_item_y && itemClicked != openMenu)     openMenu = itemClicked;
            else                                            openMenu = -1;
            button_click(itemClicked, 0, menu[itemClicked][0]);
            /*
            return valid_item;
        }*/
            return valid_item_y;
        } else if(itemClicked == openMenu) {
            //You might have been clicking on a sub menu!
            int x = (up->x+BUILDBAR_TILE_SPACING)/(BUILDBAR_TILE_SPACING)-1;
            int i = 0;
            while(i < x && menu[itemClicked][i] != NULL_SPRITE) {
                //printf("Loop %d -- %d\n", i, x);
                i++;
            }
            if(menu[itemClicked][i] != NULL_SPRITE) {
                button_click(itemClicked, x, menu[itemClicked][i]);
                return true;
            }
        }
    }
    openMenu = -1;
    return false;
}
