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

	.cstring
	.align  3
lC4:
	.ascii "Chamando funcao\n\0"
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

	.globl _v
	.data
	.align 2
_v:
	.byte 97
	.word 0
	.byte 98
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

	.globl _matrix
	.data
	.align 2
_matrix:
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

	.globl _mf
	.data
	.align 2
_mf:

	.globl __TTemP2
	.data
	.align 2
__TTemP2:
	.word 0

	.globl __TTemP3
	.data
	.align 2
__TTemP3:
	.word 0

	.globl __TTemP4
	.data
	.align 2
__TTemP4:
	.word 0

	.globl __TTemP5
	.data
	.align 2
__TTemP5:
	.word 0

	.globl __TTemP6
	.data
	.align 2
__TTemP6:
	.word 0

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
	mov w0, 2

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

	adrp x0, _v@PAGE ; TAC_VECATTR
	add x0, x0, _v@PAGEOFF
	mov w1, 0
	str w1, [x0, 0]

	adrp x0, _v@PAGE ; TAC_VECATTR
	add x0, x0, _v@PAGEOFF
	mov w1, 2
	str w1, [x0, 4]

	adrp x0, _v@PAGE ; TAC_VECATTR
	add x0, x0, _v@PAGEOFF
	mov w1, 4
	str w1, [x0, 8]

_LLabeL2:

	adrp x0, _i@PAGE ; TAC_LESS
	add x0, x0, _i@PAGEOFF
	ldr w1, [x0]
	mov w0, 10

	cmp w1, w0
	cset w1, lt
	adrp x0, __TTemP1@PAGE
	add x0, x0, __TTemP1@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP1@PAGE
	add x0, x0, __TTemP1@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL3

	adrp x0, _i@PAGE ; TAC_PRINT INT
	add x0, x0, _i@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

	adrp x0, _i@PAGE ; TAC_ADD
	add x0, x0, _i@PAGEOFF
	ldr w1, [x0]
	mov w0, 1

	add w1, w1, w0
	adrp x0, __TTemP2@PAGE
	add x0, x0, __TTemP2@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP2@PAGE ; TAC_MOVE
	add x0, x0, __TTemP2@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]

	b _LLabeL2 ; TAC_JUMP

_LLabeL3:

	adrp x0, lC4@PAGE ; TAC_PRINT STRING
	add x0, x0, lC4@PAGEOFF
	bl _printf
	bl _function1
	mov w1, w0
	adrp x0, __TTemP3@PAGE
	add x0, x0, __TTemP3@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP3@PAGE ; TAC_MOVE
	add x0, x0, __TTemP3@PAGEOFF
	ldr w1, [x0]
	adrp x0, _a@PAGE
	add x0, x0, _a@PAGEOFF
	str w1, [x0]

	adrp x0, _a@PAGE ; TAC_PRINT INT
	add x0, x0, _a@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf
	bl _function1
	mov w1, w0
	adrp x0, __TTemP4@PAGE
	add x0, x0, __TTemP4@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP4@PAGE ; TAC_PRINT INT
	add x0, x0, __TTemP4@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

	adrp x0, _1a@PAGE ; TAC_MOVE
	add x0, x0, _1a@PAGEOFF
	mov w1, 2
	str w1, [x0]

	adrp x0, _1a@PAGE ; TAC_PRINT INT
	add x0, x0, _1a@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

 	adrp x0, __TTemP5@PAGE ; TAC_READ
	add x0, x0, __TTemP5@PAGEOFF
	str x0, [sp]
	adrp x0, lCReAD@PAGE
	add x0, x0, lCReAD@PAGEOFF
	bl _scanf

	adrp x0, __TTemP5@PAGE ; TAC_MOVE
	add x0, x0, __TTemP5@PAGEOFF
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

	.text ;TAC_BEGINFUN
	.align 2
	.globl _function1
_function1:
FBEGIN_function1:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp
	mov w0, 1

	add w1, w1, w0
	adrp x0, __TTemP6@PAGE
	add x0, x0, __TTemP6@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP6@PAGE ; TAC_RET
	add x0, x0, __TTemP6@PAGEOFF
	ldr w0, [x0]
	ldp x29, x30, [sp], 16 
	ret

	ldp x29, x30, [sp], 16 ; TAC_ENDFUN
	ret
FEND2_function1:
