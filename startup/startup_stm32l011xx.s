.syntax unified
.cpu cortex-m0plus
.thumb

.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word _estack
    .word Reset_Handler

_estack .equ 0x20001000

.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    LDR R0, =_estack
    MOV SP, R0
    BL main
    B .

.size Reset_Handler, .-Reset_Handler
