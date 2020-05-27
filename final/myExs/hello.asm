; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$x:
; ID
	dd	$_L1
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L1:
; CHAR
	db	0x68
; CHAR
	db	0x65
; CHAR
	db	0x6C
; CHAR
	db	0x6C
; CHAR
	db	0x6F
; CHAR
	db	0x00
; RODATA
segment	.rodata
; ID
	dd	$_L1
; GLOBL
global	$_main:function
; TEXT
segment	.text
; ALIGN
align	4
; LABEL
$_main:
; ENTER
	push	ebp
	mov	ebp, esp
	sub	esp, 0
; ADDR
	push	dword $x
; LOAD
	pop	eax
	push	dword [eax]
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
