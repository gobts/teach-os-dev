ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_date - gdt_start

_start: 
    jmp short start
    nop

times 33 db 0

start:
; to boot in real hardware nee to jump to 0x7c0 memory address
    jmp 0:step2

step2:
    cli ;clear intewrrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax 
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enable interrupts
    ; exceptions    

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32

; GDT
gdt_start:
gdt_null: 
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:     ; CS SHOULD POINT TO THIS  
    dw 0xffff ; segment limir ffirst 0-15 bits
    dw 0      ; base first 0-15 bits
    db 0      ; Base 16-23 bits
    db 0x9a   ; access byte
    db 11001111b ; High 4 bits flags and the low 4 bits flahs
    db 0      ; base 24-31

; offset 0x10
gdt_date:     ; DS, SS, ES, FS, GS 
    dw 0xffff ; segment limir ffirst 0-15 bits
    dw 0      ; base first 0-15 bits
    db 0      ; Base 16-23 bits
    db 0x92   ; access byte
    db 11001111b ; High 4 bits flags and the low 4 bits flahs
    db 0      ; base 24-31

gdt_end:
gdt_descriptor: 
    dw gdt_end - gdt_start-1
    dd gdt_start

[BITS 32]
 load32: 
    mov ax, DATA_SEG,
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    
    jmp $


times 510-($ - $$) db 0
dw 0xAA55

