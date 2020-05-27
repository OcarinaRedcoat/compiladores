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
	sub	esp, 4
;------- -x--4-; IMM
	push	dword 45
; LOCAL
	lea	eax, [ebp+-4]
	push	eax
; STORE
	pop	ecx
	pop	eax
	mov	[ecx], eax
; LOCAL
	lea	eax, [ebp+-4]
	push	eax
; LOAD
	pop	eax
	push	dword [eax]
; EXTRN
extern	$_printi
; CALL
	call	$_printi
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
