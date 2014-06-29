#include "draw_utils.h"

extern int screen_x, screen_y;

Point isoTo2D(Point *p)
{
    int tempX, tempY;
    tempX = (2 * p->y + p->x) / 2;
    tempY = (2 * p->y - p->x) / 2;
    p->x = tempX;
    p->y = tempY;
}

Point twoDToIso(Point *p)
{
    int tempX, tempY;
    tempX = p->x - p->y;
    tempY = (p->x + p->y) / 2;
    p->x = tempX;
    p->y = tempY;
}

void mouseToGrid(int mouseX, int mouseY, Point* p)
{
    Point mouse;
    mouse.x = mouseX;
    mouse.y = mouseY;
    mouse.x -= screen_x;
    mouse.y -= screen_y;
    mouse.y += 65;
    mouse.x -= GRID_TILE_SIZE/2;
    mouse.y -= GRID_TILE_SIZE/2;
    isoTo2D(&mouse);
    mouse.x = (int)((float)(mouse.x-(GRID_TILE_SIZE/2))/(float)GRID_TILE_SIZE);
    mouse.y = (int)((float)(mouse.y)/(float)GRID_TILE_SIZE);
    p->x = mouse.x+1;
    p->y = mouse.y;
}

