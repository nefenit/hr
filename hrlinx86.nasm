; hrlinuxx86.nasm - writes horizontal bar to standard output
; (c) Copyright 2019 Bartosz Mierzynski
; Written in NASM Linux x86 32-bit Assembly
;
; nasm hrlinx86.nasm -f elf && ld -m elf_i386 -s -o hr hrlinx86.o
;

%define SYSCALL        0x80

%define SYS_EXIT       0x01
%define SYS_WRITE      0x04
%define SYS_IOCTL      0x36

%define TIOCGWINSZ     0x5413

%define STDIN_FILENO   0
%define STDOUT_FILENO  1 
%define STDERR_FILENO  2 

%define EXIT_SUCCESS   0
%define EXIT_FAILURE   1 

section .text
	global _start

; param[in] ebx status
exit:
	mov eax, SYS_EXIT
	int SYSCALL
	ret

; param[in] ecx address of byte to print
; return    eax from SYS_WRITE
putchar:
	mov eax, SYS_WRITE
	mov ebx, STDOUT_FILENO
	mov edx, 1
	int SYSCALL
	ret


; param[in] esi address of string
; return    ebx number of bytes till '\0'
strlen:
    mov ebx,0
    strlen_loop:
        cmp byte [esi+ebx], 0
        je  strlen_end
        inc ebx
        jmp strlen_loop
    strlen_end:
    inc ebx
    ret

; return ecx number of columns of output terminal
get_cols:
	mov eax, SYS_IOCTL
	mov ebx, STDOUT_FILENO
	mov ecx, TIOCGWINSZ
	mov edx, winsize
	int SYSCALL
	cmp eax, -1
	je get_cols_failed
		mov cx, word [winsize+2] 
		ret
	get_cols_failed:
		mov ecx, 80
		ret

_start:
	call get_cols
	pop eax; argc

	cmp  dword eax, 1
	push eax
	jg   _start_loop2_init

	_start_loop1:
		push ecx
		mov  ecx, hash
		call putchar
		pop  ecx
		loop _start_loop1
	mov  ecx, newline
	call putchar
	jmp  _start_end

	_start_loop2_init:
		pop  eax
		xchg eax, ecx
		dec  ecx
		pop esi
		; ecx = argc-1, eax = 80, esi = argv
	_start_loop2:
		pop  esi
		call strlen
		; ecx = argc-1, eax = 80, esi = argv, ebx = strlen(argv)
		_start_loop3_init:
			mov   edx, 0
		_start_loop3:
			cmp   edx, eax
			jge   _start_loop3_end
			pusha
				mov   eax, edx
				xor   edx, edx
				dec   ebx
				div   ebx
				add   esi, edx
				mov   ecx, esi; esi+edx%ebx
				call  putchar
			popa
			inc   edx
			jmp  _start_loop3
		_start_loop3_end:
		push eax
		push ecx
		mov  ecx, newline
		call putchar
		pop  ecx
		pop  eax
		loop _start_loop2
		_start_loop2_end:

	_start_end:
		mov  ebx, EXIT_SUCCESS
		call exit

section .data
hash    db '#'
newline db 10
section .bss
winsize resw 4

