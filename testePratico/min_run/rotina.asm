; GLOBL
global	$_rotina:function
; TEXT
segment	.text
; ALIGN
align	4
; LABEL
$_rotina:
; ENTER
	push	ebp
	mov	ebp, esp
	sub	esp, 0
; DATA
segment	.data
; LABEL
$.L1:
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
	db	0x77
; CHAR
	db	0x6F
; CHAR
	db	0x72
; CHAR
	db	0x6C
; CHAR
	db	0x64
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L1
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
; COMM line 4
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
