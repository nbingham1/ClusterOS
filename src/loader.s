global loader
extern _main

MODULEALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text
align 4
MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
STACKSIZE equ 0x4000

extern start_ctors, end_ctors, start_dtors, end_dtors

loader:
	mov esp, stack+STACKSIZE
	push eax
	push ebx
	
static_ctors_loop:
	mov ebx, start_ctors
	jmp .test
.body:
	call [ebx]
	add ebx,4
.test:
	cmp ebx, end_ctors
	jb .body
	
	call _main

static_dtors_loop:
	mov ebx, start_dtors
	jmp .test
.body:
	call [ebx]
	add ebx,4
.test:
	cmp ebx, end_dtors
	jb .body
	
	hlt

section .bss
align 32
stack:
	resb STACKSIZE
