#include "drawing_functions.h"
#include "city_master.h"

extern int map_value[MAP_SIZE_X][MAP_SIZE_Y];
extern int screen_x, screen_y;
extern Point down_point;
extern Point up_point;

const int fontSize = 48;
const char* fontFile = "fonts/sample.ttf";

SDL_Texture *sheet;
TTF_Font *font;

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
            drawTile(ren, &p, getTileClip(map_value[x][y]));
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
}

void draw_HUD(SDL_Renderer* ren)
{
    int i;
    Point p;
    p.x = 0;
    p.y = BUILDBAR_TILE_START;
    for(i=0; i<5; i++) {
        drawTile(ren, &p, getClip(SPRITE_BUILD_BACKGROUND));
        p.y += BUILDBAR_TILE_SPACING; //tile spacing
    }
    
    p.y = BUILDBAR_TILE_START;
    drawTile(ren, &p, getClip(SPRITE_BUILD_ZONE));
    p.y += BUILDBAR_TILE_SPACING;
    drawTile(ren, &p, getClip(SPRITE_BUILD_ROAD));
    p.y += BUILDBAR_TILE_SPACING;
    drawTile(ren, &p, getClip(SPRITE_BUILD_DESTROY));
    p.y += BUILDBAR_TILE_SPACING;
}

