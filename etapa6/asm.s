.arch armv8-a
.text
	.cstring
	.align 3
lC0:
	.ascii "%d\12\0"
	.text
	.cstring
	.align  3
lC3:
	.ascii "Digite um numero: \n\0"
	.text
	.cstring
	.align  3
lC4:
	.ascii "Digite mais um numero: \n\0"
	.text
	.cstring
	.align  3
lC5:
	.ascii "Incrementado algumas vezes a fica \0"
	.text
	.cstring
	.align  3
lC7:
	.ascii "\n\0"
	.text
	.cstring
	.align  3
lC8:
	.ascii "Nao tem como isso...\n\0"
	.text
	.cstring
	.align  3
lC9:
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
	.globl __TTemP11
	.data
	.align 2
__TTemP11:
	.word 0
	.globl __TTemP10
	.data
	.align 2
__TTemP10:
	.word 0
	.globl __TTemP9
	.data
	.align 2
__TTemP9:
	.word 0
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
	.globl __TTemP7
	.data
	.align 2
__TTemP7:
	.word 0
	.globl __TTemP0
	.data
	.align 2
__TTemP0:
	.word 0
	.globl __TTemP17
	.data
	.align 2
__TTemP17:
	.word 0
	.globl __TTemP16
	.data
	.align 2
__TTemP16:
	.word 0
	.globl __TTemP15
	.data
	.align 2
__TTemP15:
	.word 0
	.globl __TTemP14
	.data
	.align 2
__TTemP14:
	.word 0
	.globl __TTemP8
	.data
	.align 2
__TTemP8:
	.word 0
	.globl __TTemP13
	.data
	.align 2
__TTemP13:
	.word 0
	.globl __TTemP1
	.data
	.align 2
__TTemP1:
	.word 0
	.globl __TTemP12
	.data
	.align 2
__TTemP12:
	.word 0
	.text ;TAC_BEGINFUN
	.align 2
	.globl _main
_main:
FBEGIN_main:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp
	adrp x0, _d@PAGE ; TAC_MOVE
	add x0, x0, _d@PAGEOFF
	mov w1, 0
	str w1, [x0]
	adrp x0, _d@PAGE ; TAC_PRINT INT
	add x0, x0, _d@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf
	adrp x0, _1a@PAGE ; TAC_MOVE
	add x0, x0, _1a@PAGEOFF
	mov w1, 0
	str w1, [x0]
	adrp x0, __TTemP1@PAGE ; TAC_MOVE
	add x0, x0, __TTemP1@PAGEOFF
	ldr w1, [x0]
	adrp x0, _d@PAGE
	add x0, x0, _d@PAGEOFF
	str w1, [x0]
	adrp x0, _d@PAGE ; TAC_MOVE
	add x0, x0, _d@PAGEOFF
	mov w1, 5
	str w1, [x0]
	adrp x0, _d@PAGE ; TAC_PRINT INT
	add x0, x0, _d@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf
	adrp x0, _i@PAGE ; TAC_MOVE
	add x0, x0, _i@PAGEOFF
	mov w1, 2
	str w1, [x0]
	adrp x0, lC3@PAGE ; TAC_PRINT STRING
	add x0, x0, lC3@PAGEOFF
	bl _printf
	adrp x0, lC4@PAGE ; TAC_PRINT STRING
	add x0, x0, lC4@PAGEOFF
	bl _printf
	adrp x0, lC5@PAGE ; TAC_PRINT STRING
	add x0, x0, lC5@PAGEOFF
	bl _printf
	adrp x0, _d@PAGE ; TAC_PRINT INT
	add x0, x0, _d@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf
	adrp x0, lC7@PAGE ; TAC_PRINT STRING
	add x0, x0, lC7@PAGEOFF
	bl _printf
	adrp x0, __TTemP3@PAGE ; TAC_MOVE
	add x0, x0, __TTemP3@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]
	adrp x0, __TTemP4@PAGE ; TAC_MOVE
	add x0, x0, __TTemP4@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]
	adrp x0, __TTemP15@PAGE ; TAC_MOVE
	add x0, x0, __TTemP15@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]
	adrp x0, lC8@PAGE ; TAC_PRINT STRING
	add x0, x0, lC8@PAGEOFF
	bl _printf
	adrp x0, lC9@PAGE ; TAC_PRINT STRING
	add x0, x0, lC9@PAGEOFF
	bl _printf
	 mov w0, 0 ; TAC_RET
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
