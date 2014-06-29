

CC = gcc
CCFLAGS = -Wall
LIBS = -I'/usr/local/include/SDL2' -I'/usr/include/SDL2' -lSDL2 -L/usr/local/lib -Wl,-rpath='/usr/local/lib' -lSDL2_image -lSDL2_ttf
OUTPUT = bin/city_master

FILES = city_master drawing_functions draw_utils menu_manager mouse_functions resource_manager SDL_functions tile_info

OBJ_F = $(addprefix bin/,$(FILES:=.o))

main: $(OBJ_F)
	$(CC) $^ -o $(OUTPUT) $(LIBS) $(CCFLAGS)

bin/%.o: src/%.c
	$(CC) -c $(LIBS) $(CCFLAGS) $^ -o $@
