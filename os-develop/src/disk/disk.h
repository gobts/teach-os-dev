#ifndef DISK_H
#define DISK_H

#include "fs/file.h"

typedef unsigned int RODOOS_DISK_TYPE;

// Representa el disco real en el sistema

#define RODOOS_DISK_TYPE_REAL 0


struct disk
{
    RODOOS_DISK_TYPE type;
    int sector_size;

    // the id od the disk
    int id;
    
    struct filesystem* filesystem;

    void* fs_private;
};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif // !DISK_H