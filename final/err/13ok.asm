; DATA
segment	.data
; ALIGN
align	4
; LABEL
$s:
; ID
	dd	$_L1
; DATA
segment	.data
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
	db	0x0A
; CHAR
	db	0x00
; DATA
segment	.data
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
; IMM
	push	dword 1
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
