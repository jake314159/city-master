
// 65x100 but grid size is 50px pre isometric transform
#define GRID_TILE_SIZE 49
//50

typedef struct {
  int x, y;
} Point;

Point isoTo2D(Point *p);
Point twoDToIso(Point *p);
void mouseToGrid(int mouseX, int mouseY, Point* p);
