#include "drawing_functions.h"
#include "city_master.h"
#include "resource_manager.h"
#include "menu_manager.h"

extern int map_value[MAP_SIZE_X][MAP_SIZE_Y];
extern int screen_x, screen_y;
extern Point down_point;
extern Point up_point;

extern bool ready_to_place;
extern Point plan_up;
extern Point plan_down;

extern int reqired_power;
extern int power_avalible;
extern int lastBalanceChange;

const int fontSize = 12;
const char* fontFile = "fonts/sample.ttf";

SDL_Texture *sheet;
TTF_Font *font;

SDL_Rect top_bar = {0,0,1000,30};
SDL_Color top_bar_text_color = {0,0,0};

#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define MAX(A, B) ((A) > (B) ? (A) : (B))

void drawTileFromGridPoint(SDL_Renderer* ren, Point *p, SDL_Rect *clip)
{
    p->x *= GRID_TILE_SIZE;
    p->y *= GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(p);
    //printf("(%d,%d)\n", p.x, p.y);
    p->x += screen_x;
    p->y += screen_y;
    renderTextureClip(sheet, ren, p->x, (p->y - clip->h), clip);
}

void drawTile(SDL_Renderer* ren, Point *p, SDL_Rect *clip)
{
    
    renderTextureClip(sheet, ren, p->x, (p->y - clip->h), clip);
}

bool init_drawing(SDL_Renderer* ren)
{
    font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL){
		logSDLError("TTF_OpenFont");
        return false;
	}

    sheet = loadTexture("images/tile_sheet.png", ren);
    return true;
}

void destroy_drawing()
{
    SDL_DestroyTexture(sheet);
    TTF_CloseFont(font);
}

void draw_city(SDL_Renderer* ren)
{
    Point p;
    int x,y;
    for(x=1; x<MAP_SIZE_X; x++) {
        for(y=1;y<MAP_SIZE_Y; y++) {
            p.x = x*GRID_TILE_SIZE;
            p.y = y*GRID_TILE_SIZE;
            twoDToIso(&p);
            p.x += screen_x;
            p.y += screen_y;
            SDL_Rect *clip = getTileClip(map_value[x][y]);
            drawTile(ren, &p, clip);
        }
    }
    p.x = down_point.x*GRID_TILE_SIZE;
    p.y = down_point.y*GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(&p);
    //printf("(%d,%d)\n", p.x, p.y);
    p.x += screen_x;
    p.y += screen_y;
    drawTile(ren, &p, getTileClip(TILE_HIGHLIGHT_BLUE));

    p.x = up_point.x*GRID_TILE_SIZE;
    p.y = up_point.y*GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(&p);
    //printf("(%d,%d)\n", p.x, p.y);
    p.x += screen_x;
    p.y += screen_y;
    drawTile(ren, &p, getTileClip(TILE_HIGHLIGHT_BLUE));

    if(ready_to_place) {
        Point p2, p3;
        switch(getMode()) {
            case MODE_BUILD_ROAD:
                p = plan_down;

                p2 = plan_down;
                drawTileFromGridPoint(ren, &plan_down, getTileClip(TILE_HIGHLIGHT_GREEN));
                plan_down = p2;
                while(p.x != plan_up.x) {
                    if(p.x < plan_up.x) {
                        p.x += 1;
                    } else {
                        p.x -=1;
                    }
                    p2 = p;
                    drawTileFromGridPoint(ren, &p, getTileClip(TILE_HIGHLIGHT_GREEN));
                    p = p2;
                }
                while(p.y != plan_up.y) {
                    if(p.y < plan_up.y) {
                        p.y += 1;
                    } else {
                        p.y -=1;
                    }
                    p2 = p;
                    drawTileFromGridPoint(ren, &p, getTileClip(TILE_HIGHLIGHT_GREEN));
                    p = p2;
                }
                break;
            case MODE_BUILD_RESIDENTIAL_1:
            case MODE_BUILD_RESIDENTIAL_2:
            case MODE_BUILD_DESTROY:;
                //p = plan_down;
                //p2 = plan_down;
                //drawTileFromGridPoint(ren, &plan_down, getTileClip(TILE_HIGHLIGHT_GREEN));
                //plan_down = p2;
                int x, y;
                for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                    for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                        p.x = x;
                        p.y = y;
                        drawTileFromGridPoint(ren, &p, getTileClip(TILE_HIGHLIGHT_GREEN));
                    }
                }
                break;
        }
    }
}

void draw_HUD(SDL_Renderer* ren)
{
    int i;
    Point p;

    //Draw the top bar
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
    SDL_RenderFillRect(ren, &top_bar);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);

    draw_int(ren, font, top_bar_text_color, 20, 0, reqired_power,  "Required: ", " MW");
    draw_int(ren, font, top_bar_text_color, 20, 20, power_avalible, "Avalible: ", " MW");
    draw_int(ren, font, top_bar_text_color, 200, 00, getBalance(), "£", "000");
    draw_int(ren, font, top_bar_text_color, 200, 20, lastBalanceChange, "£", "000");

    draw_menu(ren);
}

