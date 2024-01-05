MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 32K
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 8K
}

SECTIONS
{
    .text :
    {
        *(.text*)
        *(.isr_vector)
    } >FLASH

    .data : 
    {
        *(.data*)
    } >RAM AT>FLASH

    .bss :
    {
        *(.bss*)
    } >RAM
}
