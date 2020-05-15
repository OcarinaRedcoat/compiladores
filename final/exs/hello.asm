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
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L1:
; CHAR
	db	0x65D00260
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 3
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
