

CC = gcc
CCFLAGS = -Wall
LIBS = -I'/usr/local/include/SDL2' -I'/usr/include/SDL2' -lSDL2 -L/usr/local/lib -Wl,-rpath='/usr/local/lib' -lSDL2_image -lSDL2_ttf
OUTPUT = bin/city_master

FILES = city_master drawing_functions draw_utils menu_manager mouse_functions resource_manager SDL_functions tile_info animation_functions

IMAGE_FILES = 001_ground 002_highlight 003_single_tile_buildings 004_road 005_build_icons 006_zone_residential_1 007_zone_residential_2 008_power_stations 009_zone_retail 010_double_size_buildings 011_x4_buildings 012_cars

OBJ_F = $(addprefix bin/,$(FILES:=.o))
IMG_F = $(addprefix images/parts/,$(IMAGE_FILES:=.png))

main: $(OBJ_F) bin/res/strings/*
	$(CC) $^ -o $(OUTPUT) $(LIBS) $(CCFLAGS)

bin/%.o: src/%.c 
	$(CC) -c -MD $(LIBS) $(CCFLAGS) $< -o $@

# pull in dependency info for *existing* .o files
-include $(OBJ_F:.o=.d)

sprite-sheet: $(IMG_F)
	python sprite_line_maker.py images/tile_sheet.png h images/parts/*.png

images/parts/%.png: images/%/*.png
	python sprite_line_maker.py $@ v $^

