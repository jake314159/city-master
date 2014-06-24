

CC = gcc
LIBS = -I'/usr/local/include/SDL2' -I'/usr/include/SDL2' -lSDL2 -L/usr/local/lib -Wl,-rpath='/usr/local/lib' -lSDL2_image -lSDL2_ttf
OUTPUT = bin/city_master

main: src/*.c
	$(CC) src/*.c -o $(OUTPUT) $(LIBS)
