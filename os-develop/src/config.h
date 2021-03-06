#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define RODOOS_TOTAL_INTERRUPS 512

// 100MB HEAP SIZE
#define RODOOS_HEAP_SIZE_BYTES 104857600
#define RODOOS_HEAP_BLOCK_SIZE 4096

#define RODOOS_HEAP_ADDRESS 0x01000000
#define RODOOS_HEAP_TABLE_ADDRESS 0x00007E00

#define RODOOS_SECTOR_SIZE 512

#define RODOOS_MAX_FILESYSTEMS 12
#define RODOOS_MAX_FILE_DESCRIPTORS 512

#define RODOOS_MAX_PATH 108
#endif // !CONFIG_H