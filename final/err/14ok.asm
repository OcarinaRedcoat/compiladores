; DATA
segment	.data
; ALIGN
align	4
; LABEL
$x:
; INTEGER
	dd	12
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
	push	dword 21
; COPY
	push	dword [esp]
; ADDR
	push	dword $x
; STORE
	pop	ecx
	pop	eax
	mov	[ecx], eax
; IMM
	push	dword 0
; POP
	pop	eax
; LEAVE
	leave
; RET
	ret
