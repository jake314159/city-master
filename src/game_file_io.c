#include "game_file_io.h"

typedef struct {
    int32_t PROGRAM_VERSION_NUMBER; 
    int32_t SAVE_VERSION_NUMBER;    // The same program version may have different save version numbers
    int32_t MAGIC_NUMBER;
    int32_t CHECKSUM;
} SAVE_FILE_HEADER;

void save_game(char* fileName, GAME_SAVE *save)
{
    SAVE_FILE_HEADER head;
    head.PROGRAM_VERSION_NUMBER = 1;
    head.SAVE_VERSION_NUMBER = 1;
    head.MAGIC_NUMBER = 0x4F00D843;
    //Checksum uses "Longitudinal redundancy check"
    head.CHECKSUM = head.PROGRAM_VERSION_NUMBER ^ head.SAVE_VERSION_NUMBER ^ head.MAGIC_NUMBER;

    //Do save checksum
    uint32_t checksum = save->map_size_x ^ save->map_size_y ^ save->screen_x ^ save->screen_y ^ save->save_time;
    int x, y;
    for(x=1; x<save->map_size_x; x++) {
        for(y=1;y<save->map_size_y; y++) {
            checksum ^= save->map_value[x][y];
        }
    }
    save->CHECKSUM = checksum;

    FILE *file= fopen(fileName, "wb");
    if (file != NULL) {
        fwrite(&head, sizeof(SAVE_FILE_HEADER), 1, file);
        fwrite(save, sizeof(GAME_SAVE), 1, file);
        fclose(file);
    }
}

bool read_game(char *fileName, GAME_SAVE *save)
{
    bool success = false;
    SAVE_FILE_HEADER head;
    FILE * file= fopen(fileName, "rb");
    if (file != NULL) {
        fread(&head, sizeof(SAVE_FILE_HEADER), 1, file);
        if(head.PROGRAM_VERSION_NUMBER==1 && head.SAVE_VERSION_NUMBER==1 && head.MAGIC_NUMBER == 0x4F00D843) {
            fread(save, sizeof(GAME_SAVE), 1, file);
            success = true;
        }
        fclose(file);
    }
    return success;
}

