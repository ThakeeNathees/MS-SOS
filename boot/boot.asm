global loader
extern kernel_main

MAGIC equ 0x1badb002
FLAGS equ 0x3
CHACKSUM equ -(MAGIC+FLAGS)

section .text
align 4
dd MAGIC
dd FLAGS
dd CHACKSUM

loader:
  call kernel_main
  cli

quit:
  hlt
  jmp quit
