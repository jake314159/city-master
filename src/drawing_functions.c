#include "drawing_functions.h"
#include "city_master.h"
#include "resource_manager.h"
#include "menu_manager.h"
#include "animation_functions.h"
#include "extern_strings.h"

extern int map_value[MAP_SIZE_X][MAP_SIZE_Y];
extern int screen_x, screen_y;
extern Point down_point;
extern Point up_point;

extern int window_size_x;
extern int window_size_y;

extern bool ready_to_place;
extern Point plan_up;
extern Point plan_down;

extern int reqired_power;
extern int power_avalible;
extern int lastBalanceChange;

extern const int target_population_per_shop;
extern const float target_population_per_police;
extern const float target_population_per_school;
extern int number_of_shops;

const int fontSize = 12;
const char* fontFile = "fonts/sample.ttf";

const int fontSizeLarge = 22;

bool show_sidebar = false;

SDL_Texture *sheet;
TTF_Font *font;
TTF_Font *fontLarge;

SDL_Rect top_bar = {0,0,1000,30};
SDL_Color top_bar_text_color = {0,0,0};
SDL_Rect side_bar = {0,40,200,400};
SDL_Rect planned_cost_box = {180, 30,100,20};

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
    renderTextureClip(sheet, ren, (p->x - ((clip->w)>>1)), (p->y - clip->h), clip);
}

void drawTileFromGridPointWithOfset(SDL_Renderer* ren, Point *p, int ofset_x, int ofset_y, SDL_Rect *clip)
{
    p->x *= GRID_TILE_SIZE;
    p->y *= GRID_TILE_SIZE;
    //printf("(%d,%d) -> ", p.x, p.y);
    twoDToIso(p);
    //printf("(%d,%d)\n", p.x, p.y);
    p->x += screen_x;
    p->y += screen_y;
    p->x += ofset_x;
    p->y += ofset_y;
    renderTextureClip(sheet, ren, (p->x - ((clip->w)>>1)), (p->y - clip->h), clip);
}

void drawTile(SDL_Renderer* ren, Point *p, SDL_Rect *clip)
{
    if( (p->x+clip->w) < 0 || p->y < (-clip->w) || (p->y-clip->h) > window_size_y || (p->x - clip->h) > window_size_x) return;
    renderTextureClip(sheet, ren, (p->x - ((clip->w)>>1)), (p->y - clip->h), clip);
}

bool init_drawing(SDL_Renderer* ren)
{
    font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL){
		logSDLError("TTF_OpenFont");
        return false;
	}

    fontLarge = TTF_OpenFont(fontFile, fontSizeLarge);
	if (fontLarge == NULL){
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

void draw_highlight(SDL_Renderer* ren, Point *p)
{
    if(p->x > 0 && p->y > 0 && p->x < MAP_SIZE_X && p->y < MAP_SIZE_Y && canBuildOn(map_value[p->x][p->y])) {
        drawTileFromGridPoint(ren, p, getTileClip(TILE_HIGHLIGHT_GREEN));
    } else {
        drawTileFromGridPoint(ren, p, getTileClip(TILE_HIGHLIGHT_RED));
    }
}

void draw_city(SDL_Renderer* ren)
{
    Point p;
    int x,y;
    SDL_Rect *clip;
    for(x=1; x<MAP_SIZE_X; x++) {
        bool drew_in_this_x = false;
        for(y=1;y<MAP_SIZE_Y; y++) {
            p.x = x*GRID_TILE_SIZE;
            p.y = y*GRID_TILE_SIZE;
            twoDToIso(&p);
            p.x += screen_x;
            p.y += screen_y;
            clip = getTileClip(map_value[x][y]);

            if(p.x < -clip->w) {
                break;
            } else if( p.y > (window_size_y + clip->h) ) {
                break;
            }
            drew_in_this_x = true;
            drawTile(ren, &p, clip);
            draw_animation_tile(ren, x, y);
        }
        if(!drew_in_this_x && p.y > (window_size_y + clip->h)) {
            break;
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
        Point p2;
        switch(getMode()) {
            case MODE_BUILD_ROAD:
                p = plan_down;

                p2 = plan_down;
                draw_highlight(ren, &plan_down);
                plan_down = p2;
                while(p.x != plan_up.x) {
                    if(p.x < plan_up.x) {
                        p.x += 1;
                    } else {
                        p.x -=1;
                    }
                    p2 = p;
                    draw_highlight(ren, &p);
                    p = p2;
                }
                while(p.y != plan_up.y) {
                    if(p.y < plan_up.y) {
                        p.y += 1;
                    } else {
                        p.y -=1;
                    }
                    p2 = p;
                    draw_highlight(ren, &p);
                    p = p2;
                }
                break;
            case MODE_BUILD_RESIDENTIAL_1:
            case MODE_BUILD_RESIDENTIAL_2:
            case MODE_BUILD_DESTROY:
            case MODE_BUILD_LANDFILL:
            case MODE_BUILD_RETAIL:
            case MODE_BUILD_POWER_SOLAR:
            case MODE_BUILD_POWER_WIND:
            ;
                //p = plan_down;
                //p2 = plan_down;
                //drawTileFromGridPoint(ren, &plan_down, getTileClip(TILE_HIGHLIGHT_GREEN));
                //plan_down = p2;
                int x, y;
                for(x = MIN(plan_down.x, plan_up.x); x<=MAX(plan_down.x, plan_up.x); x++) {
                    for(y = MIN(plan_down.y, plan_up.y); y<=MAX(plan_down.y, plan_up.y); y++) {
                        p.x = x;
                        p.y = y;
                        draw_highlight(ren, &p);
                    }
                }
                break;
            case MODE_BUILD_HOSPITAL:
            case MODE_BUILD_POLICE:
            ;
                p.x = plan_up.x;
                p.y = plan_up.y;
                draw_highlight(ren, &p);
                break;
            case MODE_BUILD_POWER_GAS:
            case MODE_BUILD_POWER_NUCLEAR:
            case MODE_BUILD_SCHOOL:
            case MODE_BUILD_PARK:
            ;
                p.x = plan_up.x;
                p.y = plan_up.y;
                draw_highlight(ren, &p);
                p.x = plan_up.x+1;
                p.y = plan_up.y;
                draw_highlight(ren, &p);
                p.x = plan_up.x;
                p.y = plan_up.y+1;
                draw_highlight(ren, &p);
                p.x = plan_up.x+1;
                p.y = plan_up.y+1;
                draw_highlight(ren, &p);
                break;
            case MODE_BUILD_STADIUM:
            ;
                int x1, y1;
                for(x1 = 0; x1<4; x1++) {
                    for(y1 = 0; y1<4; y1++) {
                        p.x = plan_up.x+x1;
                        p.y = plan_up.y+y1;
                        draw_highlight(ren, &p);
                    }
                }
                break;
			default:
				break;
        }
    }
}

void setColorGoodBad(SDL_Renderer* ren, bool good)
{
    if(good)
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
    else //bad
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
}

void draw_scale(SDL_Renderer* ren, SDL_Rect* scale_box, float value) {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderFillRect(ren, scale_box);
    setColorGoodBad(ren, value >=0.5f);
    int old_width = scale_box->w;
    if(value >=0 && value <=1) {
        scale_box->w = old_width*value;
    }
    SDL_RenderFillRect(ren, scale_box);
    scale_box->w = old_width;
}

void draw_HUD(SDL_Renderer* ren)
{
    //Draw the top bar
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
    top_bar.w = window_size_x;
    SDL_RenderFillRect(ren, &top_bar);

    draw_int(ren, font, top_bar_text_color, 20, 0, reqired_power,  "Required: ", " MW");
    draw_int(ren, font, top_bar_text_color, 20, 20, power_avalible, "Avalible: ", " MW");
    draw_int(ren, font, top_bar_text_color, 200, 00, getBalance(), "£", "000");
    draw_int(ren, font, top_bar_text_color, 200, 20, lastBalanceChange, "£", "000");

    draw_int(ren, font, top_bar_text_color, 400, 0, getPopulation(), "Pop: ", "");

    //Draw the side bar
    if(show_sidebar) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        side_bar.x = window_size_x - side_bar.w;
        SDL_RenderFillRect(ren, &side_bar);
        SDL_Rect scaleBox = {window_size_x-100-5,0,100,fontSizeLarge+2};
        int item_y = side_bar.y+5;

        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_POLICE_start);
        scaleBox.y = item_y;
        draw_scale(ren, &scaleBox, (target_population_per_police/populationPerPolice())-0.49f);

        item_y += fontSizeLarge+2;
        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_HEALTH_start);
        setColorGoodBad(ren, getNumberOfHospitals() > 0);
        scaleBox.y = item_y;
        SDL_RenderFillRect(ren, &scaleBox);

        item_y += fontSizeLarge+2;
        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_EDUCATION_start);
        setColorGoodBad(ren, populationPerSchool() < target_population_per_school);
        scaleBox.y = item_y;
        draw_scale(ren, &scaleBox, (target_population_per_school/populationPerSchool())-0.49f);

        item_y += fontSizeLarge+2;
        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_SHOPPING_start);
        float shops_short_by = ((float)getPopulation()/(float)target_population_per_shop) - (float)number_of_shops;
        setColorGoodBad(ren, shops_short_by <= 0);
        scaleBox.y = item_y;
        SDL_RenderFillRect(ren, &scaleBox);

        item_y += fontSizeLarge+2;
        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_POWER_start);
        scaleBox.y = item_y;
        draw_scale(ren, &scaleBox, 1-(reqired_power)/((float)power_avalible));

        item_y += fontSizeLarge+2;
        draw_string(ren, fontLarge, top_bar_text_color, side_bar.x+5, item_y, &_binary_VALUE_TEXT_WASTE_start);
        scaleBox.y = item_y;
        draw_scale(ren, &scaleBox, wasteDisposalUtilisation());
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);

    SDL_Rect open_menu_button = {window_size_x-30,0,30,30};
    SDL_RenderFillRect(ren, &open_menu_button);

    char* modeText = NULL;
    switch(getMode()) {
        case MODE_BUILD_RESIDENTIAL_1:
            modeText = &_binary_MODE_TEXT_RESIDENTIAL_1_start;
            break;
        case MODE_BUILD_RESIDENTIAL_2:
            modeText = &_binary_MODE_TEXT_RESIDENTIAL_2_start;
            break;
        case MODE_BUILD_ROAD:
            modeText = &_binary_MODE_TEXT_BUILD_ROAD_start;
            break;
        case MODE_BUILD_POWER_GAS:
            modeText = &_binary_MODE_TEXT_BUILD_POWER_GAS_start;
            break;
        case MODE_BUILD_DESTROY:
            modeText = &_binary_MODE_TEXT_DESTROY_start;
            break;
        case MODE_BUILD_RETAIL:
            modeText = &_binary_MODE_TEXT_BUILD_RETAIL_start;
            break;
        case MODE_BUILD_HOSPITAL:
            modeText = &_binary_MODE_TEXT_BUILD_HOSPITAL_start;
            break;
        case MODE_BUILD_POWER_SOLAR:
            modeText = &_binary_MODE_TEXT_BUILD_POWER_SOLAR_start;
            break;
        default:
            break;
    }
    if(modeText != NULL) {
        draw_string(ren, font, top_bar_text_color, 5, window_size_y-15, modeText);
    }
    if(ready_to_place) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        SDL_RenderFillRect(ren, &planned_cost_box);
        draw_int(ren, font, top_bar_text_color, 200, 35, costOfPlannedBuild(),  "(-£", "000)");
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    draw_menu(ren);
}

void draw_string_default(SDL_Renderer* ren, int x, int y, char* string)
{
    draw_string(ren, fontLarge, top_bar_text_color, x, y, string);
}

