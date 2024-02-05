.arch armv8-a
.text

	.cstring
	.align 3
lCReAD:
	.ascii "%d\0"
	.align 3
lC0:
	.ascii "%d\12\0"
	.text

	.cstring
	.align  3
lC1:
	.ascii "Nao tem como isso...\n\0"
	.text

	.cstring
	.align  3
lC2:
	.ascii "OK!\n\0"
	.text

	.globl _a
	.data
	.align 2
_a:
	.word 0

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

	.globl __TTemP0
	.data
	.align 2
__TTemP0:
	.word 0

	.globl __TTemP1
	.data
	.align 2
__TTemP1:
	.word 0

	.text ;TAC_BEGINFUN
	.align 2
	.globl _main
_main:
FBEGIN_main:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp

	adrp x0, _i@PAGE ; TAC_EQ
	add x0, x0, _i@PAGEOFF
	ldr w1, [x0]
	mov w0, 1

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP0@PAGE
	add x0, x0, __TTemP0@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP0@PAGE
	add x0, x0, __TTemP0@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL0

	adrp x0, lC1@PAGE ; TAC_PRINT STRING
	add x0, x0, lC1@PAGEOFF
	bl _printf

	b _LLabeL1 ; TAC_JUMP

_LLabeL0:

	adrp x0, lC2@PAGE ; TAC_PRINT STRING
	add x0, x0, lC2@PAGEOFF
	bl _printf

_LLabeL1:

	adrp x0, _1a@PAGE ; TAC_MOVE
	add x0, x0, _1a@PAGEOFF
	mov w1, 0
	str w1, [x0]

	adrp x0, _1a@PAGE ; TAC_PRINT INT
	add x0, x0, _1a@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

 	adrp x0, __TTemP1@PAGE ; TAC_READ
	add x0, x0, __TTemP1@PAGEOFF
	str x0, [sp]
	adrp x0, lCReAD@PAGE
	add x0, x0, lCReAD@PAGEOFF
	bl _scanf

	adrp x0, __TTemP1@PAGE ; TAC_MOVE
	add x0, x0, __TTemP1@PAGEOFF
	ldr w1, [x0]
	adrp x0, _1a@PAGE
	add x0, x0, _1a@PAGEOFF
	str w1, [x0]

	adrp x0, _1a@PAGE ; TAC_PRINT INT
	add x0, x0, _1a@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

	 mov w0, 2 ; TAC_RET
	ldp x29, x30, [sp], 16 
	ret

	 mov w0, 0 ; TAC_RET
	ldp x29, x30, [sp], 16 
	ret

	ldp x29, x30, [sp], 16 ; TAC_ENDFUN
	ret
FEND2_main:

	.text ;TAC_BEGINFUN
	.align 2
	.globl _incn
_incn:
FBEGIN_incn:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp

	ldp x29, x30, [sp], 16 ; TAC_ENDFUN
	ret
FEND2_incn:
