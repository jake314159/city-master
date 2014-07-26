#include "menu_manager.h"
#include "city_master.h"
#include "drawing_functions.h"
#include "extern_strings.h"

#define ABS(X) (((X)>0) ? (X) : (-(X)))
#define DRAG_SENSITIVITY 5

#define MENU_LENGTH 8
#define MENU_LONGEST_SUBMENU 6
SPRITE menu[MENU_LENGTH][MENU_LONGEST_SUBMENU] = {
    {SPRITE_BUILD_ZONE_RES1, SPRITE_BUILD_ZONE_RES1, SPRITE_BUILD_ZONE_RES2, SPRITE_BUILD_ZONE_RES3, SPRITE_BUILD_ZONE_RETAIL, NULL_SPRITE},
    {SPRITE_BUILD_POWER_GENRAL, SPRITE_BUILD_POWER_GAS, SPRITE_BUILD_POWER_SOLAR, SPRITE_BUILD_POWER_WIND, SPRITE_BUILD_POWER_NUCLEAR, NULL_SPRITE},
    {SPRITE_SERVICES_GENRAL, SPRITE_SERVICES_HOSPITAL, SPRITE_BUILD_SERVICES_POLICE, NULL_SPRITE},
    {SPRITE_BUILD_SCHOOL, SPRITE_BUILD_SCHOOL, NULL_SPRITE},
    {SPRITE_BUILD_CULTURE_GENRAL, SPRITE_BUILD_CULTURE_STADIUM, SPRITE_BUILD_CULTURE_PARK, NULL_SPRITE},
    {SPRITE_BUILD_ROAD, NULL_SPRITE},
    {SPRITE_WASTE_GENERAL, SPRITE_WASTE_GENERAL, SPRITE_WASTE_RECYCLE, NULL_SPRITE}, //Waste management
    {SPRITE_BUILD_DESTROY, NULL_SPRITE}
};

int openMenu = -1; //-1 == not open

int hoverMenuY = -1;
int hoverMenuX = 0;

void draw_menu(SDL_Renderer* ren)
{
    Point p;
    p.x = 16; //placed based on centre so x should be half the width
    p.y = BUILDBAR_TILE_START;
    int i;
    for(i=0; i<MENU_LENGTH; i++) {
        drawTile(ren, &p, getClip(SPRITE_BUILD_BACKGROUND));
        drawTile(ren, &p, getClip(menu[i][0]));
        p.y += BUILDBAR_TILE_SPACING; //tile spacing
    }

    p.x = BUILDBAR_TILE_SPACING + 16; //+16 as x is for the centre
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

    if(hoverMenuY >= 0) {
        char* menuText = 0;
        switch(menu[hoverMenuY][hoverMenuX]) {
            case SPRITE_BUILD_ZONE_RES1:
                if(hoverMenuX == 0) menuText = &_binary_MODE_TEXT_ZONE_start;
                else                menuText = &_binary_MODE_TEXT_RESIDENTIAL_1_start;
                break;
            case SPRITE_BUILD_ZONE_RES2:
                menuText = &_binary_MODE_TEXT_RESIDENTIAL_2_start;
                break;
            case SPRITE_BUILD_ZONE_RES3:
                menuText = &_binary_MODE_TEXT_RESIDENTIAL_3_start;
                break;
            case SPRITE_BUILD_SCHOOL:
                if(hoverMenuX == 0) menuText = &_binary_VALUE_TEXT_EDUCATION_start;
                else                menuText = &_binary_MODE_TEXT_SCHOOL_start;
                break;
            case SPRITE_BUILD_POWER_GENRAL:
                menuText = &_binary_MODE_TEXT_BUILD_POWER_start;
                break;
            case SPRITE_BUILD_POWER_GAS:
                menuText = &_binary_MODE_TEXT_BUILD_POWER_GAS_start;
                break;
            case SPRITE_BUILD_POWER_SOLAR:
                menuText = &_binary_MODE_TEXT_BUILD_POWER_SOLAR_start;
                break;
            case SPRITE_BUILD_POWER_WIND:
                menuText = &_binary_MODE_TEXT_BUILD_POWER_WIND_start;
                break;
            case SPRITE_BUILD_POWER_NUCLEAR:
                menuText = &_binary_MODE_TEXT_BUILD_POWER_NUCLEAR_start;
                break;
            case SPRITE_SERVICES_GENRAL:
                menuText = &_binary_MODE_TEXT_BUILD_SERVICES_start;
                break;
            case SPRITE_BUILD_SERVICES_POLICE:
                menuText = &_binary_MODE_TEXT_BUILD_SERVICE_POLICE_start;
                break;
            case SPRITE_SERVICES_HOSPITAL:
                menuText = &_binary_MODE_TEXT_BUILD_SERVICE_HOSPITAL_start;
                break;
            case SPRITE_BUILD_CULTURE_GENRAL:
                menuText = &_binary_MODE_TEXT_CULTURE_start;
                break;
            case SPRITE_BUILD_CULTURE_STADIUM:
                menuText = &_binary_MODE_TEXT_CULTURE_STADIUM_start;
                break;
            case SPRITE_BUILD_CULTURE_PARK:
                menuText = &_binary_MODE_TEXT_CULTURE_PARK_start;
                break;
            case SPRITE_BUILD_ROAD:
                menuText = &_binary_MODE_TEXT_BUILD_ROAD_start;
                break;
            case SPRITE_WASTE_GENERAL:
                if(hoverMenuX == 0) menuText = &_binary_MODE_TEXT_WASTE_MANAGEMENT_start;
                else                menuText = &_binary_MODE_TEXT_WASTE_LANDFIL_start;
                break;
            case SPRITE_WASTE_RECYCLE:
                menuText = &_binary_MODE_TEXT_WASTE_RECYCLE_PLANT_start;
                break;
            default:
                break;
        }
        if(menuText != 0) {
            int i = 0;
            if(hoverMenuY == openMenu) {
                while(menu[hoverMenuY][i] != NULL_SPRITE) {
                    i++;
                }
            }
            draw_string_default(ren, 
                        BUILDBAR_TILE_SPACING+BUILDBAR_TILE_SPACING*i, 
                        BUILDBAR_TILE_START + hoverMenuY*BUILDBAR_TILE_SPACING - (BUILDBAR_TILE_SPACING) + ((BUILDBAR_TILE_SPACING>>2)), 
                        menuText);
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
            case SPRITE_BUILD_ZONE_RES3:
                setMode(MODE_BUILD_RESIDENTIAL_3);
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
            case SPRITE_BUILD_SCHOOL:
                setMode(MODE_BUILD_SCHOOL);
                break;
            case SPRITE_BUILD_POWER_NUCLEAR:
                setMode(MODE_BUILD_POWER_NUCLEAR);
                break;
            case SPRITE_BUILD_CULTURE_STADIUM:
                setMode(MODE_BUILD_STADIUM);
                break;
            case SPRITE_BUILD_CULTURE_PARK:
                setMode(MODE_BUILD_PARK);
                break;
            case SPRITE_WASTE_GENERAL: //Landfill
                setMode(MODE_BUILD_LANDFILL);
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

void hover_menu(Point *p)
{
    int itemClicked = (p->y - BUILDBAR_TILE_START+BUILDBAR_TILE_SPACING)/(BUILDBAR_TILE_SPACING);
    if(p->x < 32) {
        // It was on the left bar
        bool valid_item_y = (itemClicked >=0 && itemClicked < MENU_LENGTH);
        if(valid_item_y)     {
            hoverMenuY = itemClicked;
            hoverMenuX = 0;
        } else {
            hoverMenuY = -1;
        }
    } else if(itemClicked == openMenu){

        //You might have been clicking on a sub menu!
        int x = (p->x+BUILDBAR_TILE_SPACING)/(BUILDBAR_TILE_SPACING)-1;
        int i = 0;
        while(i < x && menu[itemClicked][i] != NULL_SPRITE) {
            i++;
        }
        if(menu[itemClicked][i] != NULL_SPRITE) {
            hoverMenuX = x;
            hoverMenuY = itemClicked;
        } else {
            hoverMenuY = -1;
        }
    } else {
            hoverMenuY = -1;
    }
}
