.arch armv8-a
.text
	.cstring
	.align 3
lC0:
	.ascii "%d\12\0"
	.text
	.globl _a
	.data
	.align 2
_a: .word 15
	.globl _x
	.data
	.align 2
_x: .byte 120
	.globl _c
	.data
	.align 2
_c: .byte 120
	.globl _d
	.data
	.align 2
_d: .byte 49
	.globl _1a
	.data
	.align 2
_1a: .byte 65
	.globl _i
	.data
	.align 2
_i: .word 1
	.globl _f
	.data
	.align 2
_f:	.globl _b
	.data
	.align 2
_b: