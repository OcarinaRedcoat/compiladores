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
	push	dword 2
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L1
; DATA
segment	.data
; LABEL
$.L2:
; CHAR
	db	0x79
; CHAR
	db	0x65
; CHAR
	db	0x73
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L2
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 4
; COMM line 5
; JMP
	jmp	dword $.L3
; LABEL
$.L1:
; LABEL
$.L3:
; COMM line 5
; IMM
	push	dword 0
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L4
; DATA
segment	.data
; LABEL
$.L5:
; CHAR
	db	0x6E
; CHAR
	db	0x6F
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L5
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 7
; COMM line 8
; JMP
	jmp	dword $.L6
; LABEL
$.L4:
; LABEL
$.L6:
; COMM line 8
; DATA
segment	.data
; LABEL
$.L7:
; CHAR
	db	0x0A
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L7
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 9
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
