
MEMORY
{
  rom (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
  ram (rwx) : ORIGIN = 0x10000000, LENGTH =  32K
  
  ram1(rwx) : ORIGIN = 0x2007C000, LENGTH = 16k
  ram2(rwx) : ORIGIN = 0x20080000, LENGTH = 16k
}

EXTERN(vector_table)
ENTRY(reset_handler)

SECTIONS
{
    .text :
    {
        *(.vectors)
        *(.text*)
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
    } > rom
    . = ALIGN(4);
    _etext = .;

    .data :
    {
        _data = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > rom
    _data_lma = LOADADDR(.data);

    .bss :
    {
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram AT > rom

    end = .;

}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
