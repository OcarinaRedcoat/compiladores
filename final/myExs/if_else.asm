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
; IMM
	push	dword 2
; EQ
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
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
; DATA
segment	.data
; LABEL
$.L4:
; CHAR
	db	0x6E
; CHAR
	db	0x6F
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L4
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 6
; COMM line 7
; LABEL
$.L3:
; COMM line 7
; DATA
segment	.data
; LABEL
$.L5:
; CHAR
	db	0x0A
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
; COMM line 8
; IMM
	push	dword 0
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L6
; DATA
segment	.data
; LABEL
$.L7:
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
	push	dword $.L7
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 11
; COMM line 12
; JMP
	jmp	dword $.L8
; LABEL
$.L6:
; DATA
segment	.data
; LABEL
$.L9:
; CHAR
	db	0x6E
; CHAR
	db	0x6F
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L9
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 13
; COMM line 14
; LABEL
$.L8:
; COMM line 14
; DATA
segment	.data
; LABEL
$.L10:
; CHAR
	db	0x0A
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L10
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 15
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
