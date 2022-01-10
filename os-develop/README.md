# Memory Video Address:

### Color Video address 0xB8000
### Monocrome Video address 0xB0000

# To Debug OS  

```bash
gdb
add-symbol-file ../build/kernelfull.o 0x100000
target remote | qemu-system-x86_64 -hda ./os.bin -gdb stdio -S
break kernel_start
c
bt
layout asm
```