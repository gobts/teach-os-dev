ORG 0
BITS 16

_start: 
    jmp short start
    nop

times 33 db 0

start:
; to boot in real hardware nee to jump to 0x7c0 memory address
    jmp 0x7c0:step2

handler_zero:
    mov ah, 0eh
    mov al, 'A',
    mov bx, 0x00,
    int 0x10
    iret

handler_one:
    mov ah, 0eh,
    mov al, 'V'
    mov bx, 0x00,
    int 0x10
    iret
step2:
    cli ;clear intewrrupts
    mov ax, 0x7c0
    mov ds, ax
    mov es,ax 
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enable interrupts
    ; exceptions    

    mov ah, 2 ; READ SECTOR COMMAND
    mov al, 1 ; ONE SECTOR TO READ
    mov ch, 0 ; Cylinder low eight bit 
    mov cl, 2 ; read sector thw
    mov dh, 0 ; head number
    mov bx, buffer
    int 0x13

    mov si, buffer
    call print
    jmp $

error: 
    mov si, error_message
    call print

    jmp $

print:
    mov bx, 0
.loop: 
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'Hello World', 0

error_message: db 'Failed to load sector', 0

times 510-($ - $$) db 0
dw 0xAA55

buffer: 
