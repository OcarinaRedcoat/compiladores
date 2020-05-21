; TEXT
segment	.text
; ALIGN
align	4
; LABEL
$test:
; ENTER
	push	ebp
	mov	ebp, esp
	sub	esp, 0
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
; GLOBL
global	$_L1:object
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L1:
; CHAR
	db	0x74
; CHAR
	db	0x65
; CHAR
	db	0x73
; CHAR
	db	0x74
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L1
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
; ADDR
	push	dword $test
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
