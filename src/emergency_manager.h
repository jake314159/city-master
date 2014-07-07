#include <stdbool.h>

void init_emergency();
bool contains_emergency(int x, int y);
bool active_emergency();
void draw_emergency(SDL_Renderer* ren);
void start_emergency();
void update_emergency();
void move_camera_to_emergency();
