; DATA
segment	.data
; ALIGN
align	4
; LABEL
$x:
; INTEGER
	dd	3
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
; IMM
	push	dword 0
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
	db	0x61
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
; COMM line 5
; COMM line 6
; JMP
	jmp	dword $.L3
; LABEL
$.L1:
; ADDR
	push	dword $x
; LOAD
	pop	eax
	push	dword [eax]
; IMM
	push	dword 1
; EQ
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L4
; DATA
segment	.data
; LABEL
$.L5:
; CHAR
	db	0x62
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
; ADDR
	push	dword $x
; LOAD
	pop	eax
	push	dword [eax]
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
	je	near $.L7
; DATA
segment	.data
; LABEL
$.L8:
; CHAR
	db	0x63
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L8
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 9
; COMM line 10
; JMP
	jmp	dword $.L9
; LABEL
$.L7:
; LABEL
$.L9:
; ADDR
	push	dword $x
; LOAD
	pop	eax
	push	dword [eax]
; IMM
	push	dword 3
; EQ
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L10
; DATA
segment	.data
; LABEL
$.L11:
; CHAR
	db	0x64
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L11
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 11
; COMM line 12
; JMP
	jmp	dword $.L12
; LABEL
$.L10:
; LABEL
$.L12:
; ADDR
	push	dword $x
; LOAD
	pop	eax
	push	dword [eax]
; IMM
	push	dword 4
; EQ
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
; JZ
	pop	eax
	cmp	eax, byte 0
	je	near $.L13
; DATA
segment	.data
; LABEL
$.L14:
; CHAR
	db	0x65
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L14
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; COMM line 13
; COMM line 14
; JMP
	jmp	dword $.L15
; LABEL
$.L13:
; LABEL
$.L15:
; LABEL
$.L3:
; COMM line 14
; DATA
segment	.data
; LABEL
$.L16:
; CHAR
	db	0x0A
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $.L16
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
