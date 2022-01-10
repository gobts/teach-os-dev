#/bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
make clean
make  all

# qemu-system-x86_64 -hda ./bin/os.bin 