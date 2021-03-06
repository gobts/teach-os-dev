#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "status.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "fs/fat/fat16.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"

uint16_t* video_men = 0;

uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour) 
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_men[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
    //video_men[(y * VGA_WIDTH) + x] = terminal_make_char(' ', 0);
}

void terminal_writechar(char c, char colour)
{
    if(c == '\n') {
        terminal_col = 0;
        terminal_row += 1;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1; 

    if(terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_men = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0;  x < VGA_WIDTH; x++ ) 
        {
            // video_men[(y * VGA_WIDTH) + x] = terminal_make_char(' ', 0);
            terminal_putchar(x, y, ' ', 0);

        }
    }
    
}

void print(const char* str)
{
    size_t len = strlen(str);
    for( int i = 0; i < len; i++ )
    {
        terminal_writechar(str[i], 15);
    }
}

// extern void problem();

static struct paging_4gb_chunk* kernel_chunk = 0;

void kernel_main() 
{
    terminal_initialize();
    print("Hello World ... \n Como hacemos aquello \n");

    // Initialize the heap
    kheap_init();

    fs_init();

    disk_search_and_init();

    // initialize interruptions table
    idt_init();

    // Setup Paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // switch to kernel paging
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    // char* ptr = kzalloc(4096); 
    // paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x1000, (uint32_t)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);
    // enable paging
    enable_paging();
    
    // Enable the system interrupts
    enable_interrupts();
    // // problem();
    // //outb(0x60, 0xff);

    // struct path_root* root_path = pathparser_parse("0:/bin/shell.bin", NULL);

    // if (root_path)
    // {

    // }

    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
    diskstreamer_read(stream, &c, 1);
    char buf[50];
    strcpy(buf, "Hola como estas?");

    while(1) {}
    
}