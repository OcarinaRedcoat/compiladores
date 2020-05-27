; DATA
segment	.data
; ALIGN
align	4
; LABEL
$x:
; INTEGER
	dd	0
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
	je	near $_L1
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L2:
; CHAR
	db	0x61
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L2
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; JMP
	jmp	dword $_L3
; LABEL
$_L1:
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
	je	near $_L4
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L5:
; CHAR
	db	0x62
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L5
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; JMP
	jmp	dword $_L6
; LABEL
$_L4:
; LABEL
$_L6:
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
	je	near $_L7
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L8:
; CHAR
	db	0x63
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L8
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; JMP
	jmp	dword $_L9
; LABEL
$_L7:
; LABEL
$_L9:
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
	je	near $_L10
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L11:
; CHAR
	db	0x64
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L11
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; JMP
	jmp	dword $_L12
; LABEL
$_L10:
; LABEL
$_L12:
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
	je	near $_L13
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L14:
; CHAR
	db	0x65
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L14
; EXTRN
extern	$_prints
; CALL
	call	$_prints
; TRASH
	add	esp, 4
; JMP
	jmp	dword $_L15
; LABEL
$_L13:
; LABEL
$_L15:
; LABEL
$_L3:
; RODATA
segment	.rodata
; ALIGN
align	4
; LABEL
$_L16:
; CHAR
	db	0x0A
; CHAR
	db	0x00
; TEXT
segment	.text
; ADDR
	push	dword $_L16
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
