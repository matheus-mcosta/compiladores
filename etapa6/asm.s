.arch armv8-a
.text
	.cstring
	.align 3
lC0:
	.ascii "%d\12\0"
	.text
lC3:
	.ascii "Digite um numero: \n\0"
	.text
lC4:
	.ascii "Digite mais um numero: \n\0"
	.text
lC5:
	.ascii "Incrementado algumas vezes a fica \0"
	.text
lC7:
	.ascii "\n\0"
	.text
lC8:
	.ascii "Nao tem como isso...\n\0"
	.text
lC9:
	.ascii "OK!\n\0"
	.text
	.globl _a
	.data
	.align 2
_a:
	.word 15
	.globl _x
	.data
	.align 2
_x:
	.byte 120
	.globl _c
	.data
	.align 2
_c:
	.byte 120
	.globl _d
	.data
	.align 2
_d:
	.byte 49
	.globl _1a
	.data
	.align 2
_1a:
	.byte 65
	.globl _i
	.data
	.align 2
_i:
	.word 1
	.text
	.align 2
	.globl _main
_main:
FBEGIN_main:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp
	adrp x0, _a@PAGE
	add x0, x0, _a@PAGEOFF
	ldr w0, [x0]
	ldp x29, x30, [sp], 16
	ret
FEND2_main:
	.text
	.align 2
	.globl _incn
_incn:
FBEGIN_incn:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp
	ldp x29, x30, [sp], 16
	ret
FEND2_incn:
