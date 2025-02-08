target extended-remote localhost:3333
source /home/mehdi/extra/gits/svd-tools/gdb-svd.py
svd LPC176x5x.svd
monitor reset halt
monitor flash write_image erase build/fw.elf
start
lay src
