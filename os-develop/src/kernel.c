#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"


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

size_t strlen( const char* str)
{
    size_t len = 0;
    while (str[len])
    {
        len++; 
    }

    return len;
    
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

void kernel_main() 
{
    terminal_initialize();
    print("Hello World ... \n COmo hacemos aquello \n");

    kheap_init();

    // initialize interruptions table
    idt_init();

    // problem();
    //outb(0x60, 0xff);
    void* ptr = kmalloc(50);
    void* ptr2 = kmalloc(5000);
    void* ptr3 = kmalloc(5600);
    kfree(ptr);
    void* ptr4 = kmalloc(50);

    if(ptr || ptr2 || ptr3 || ptr4)
    {

    }
}