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
<<<<<<< HEAD
	db	0x65D00260
=======
	db	0xC6BDFF0
>>>>>>> 400c45adba8eba189c0c07ef93d8b7a99a24b2b3
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
