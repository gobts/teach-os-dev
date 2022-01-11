# Memory Video Address:

### Color Video address 0xB8000
### Monocrome Video address 0xB0000

# To Debug OS  

```bash
gdb
add-symbol-file ./build/kernelfull.o 0x100000
target remote | qemu-system-i386 -hda ./bin/os.bin -gdb stdio -S
break kerne.c:99
c
bt
layout asm
```