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
	.ascii "Atribuicao com vetor [expr] v[1] = 20\n\0"
	.text

	.cstring
	.align  3
lC3:
	.ascii "Chamada de funcao add(1,2)\n\0"
	.text

	.cstring
	.align  3
lC4:
	.ascii "resultado 1 + 2 = \0"
	.text

	.cstring
	.align  3
lC6:
	.ascii "Operacao com vetor     v[1+4*0] = 10;  // v[1] = 10\n\0"
	.text

	.cstring
	.align  3
lC7:
	.ascii "b = \0"
	.text

	.cstring
	.align  3
lC9:
	.ascii "Teste if OK\n\0"
	.text

	.cstring
	.align  3
lC10:
	.ascii "Teste else NAO PODE ACONTECER\n\0"
	.text

	.cstring
	.align  3
lC11:
	.ascii "NAO pode\n\0"
	.text

	.cstring
	.align  3
lC12:
	.ascii "Not funcionando \n\0"
	.text

	.cstring
	.align  3
lC13:
	.ascii "AND funcionando\n\0"
	.text

	.cstring
	.align  3
lC14:
	.ascii "Teste else NAO PODE ACONTECER\\0"
	.text

	.cstring
	.align  3
lC15:
	.ascii "OR funcionando\n\0"
	.text

	.cstring
	.align  3
lC16:
	.ascii "Teste else NAO PODE ACONTECER\0"
	.text

	.cstring
	.align  3
lC17:
	.ascii "Teste while 0 a 9\n\0"
	.text

	.cstring
	.align  3
lC18:
	.ascii "i = \0"
	.text

	.cstring
	.align  3
lC20:
	.ascii "Fim do programa\n \0"
	.text

	.globl _a
	.data
	.align 2
_a:
	.word 0

	.globl _1a
	.data
	.align 2
_1a:
	.byte 65

	.globl _b
	.data
	.align 2
_b:
	.word 0

	.globl _i
	.data
	.align 2
_i:
	.word 1

	.globl _v
	.data
	.align 2
_v:
	.word 10
	.word 20
	.byte 98
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0

	.globl _n
	.data
	.align 2
_n:
	.word 0

	.globl _n2
	.data
	.align 2
_n2:
	.word 0

	.globl _n3
	.data
	.align 2
_n3:
	.word 0

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

	.globl __TTemP22
	.data
	.align 2
__TTemP22:
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

	.globl __TTemP23
	.data
	.align 2
__TTemP23:
	.word 0

	.globl __TTemP3
	.data
	.align 2
__TTemP3:
	.word 0

	.globl __TTemP24
	.data
	.align 2
__TTemP24:
	.word 0

	.globl __TTemP4
	.data
	.align 2
__TTemP4:
	.word 0

	.globl __TTemP25
	.data
	.align 2
__TTemP25:
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

	.globl __TTemP19
	.data
	.align 2
__TTemP19:
	.word 0

	.globl __TTemP20
	.data
	.align 2
__TTemP20:
	.word 0

	.globl __TTemP18
	.data
	.align 2
__TTemP18:
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

	.globl __TTemP21
	.data
	.align 2
__TTemP21:
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

	adrp x0, lC1@PAGE ; TAC_PRINT STRING
	add x0, x0, lC1@PAGEOFF
	bl _printf

	mov w1, 0 ; TAC_ADD
	mov w0, 2

	add w1, w1, w0
	adrp x0, __TTemP0@PAGE
	add x0, x0, __TTemP0@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP0@PAGE ; TAC_SUB
	add x0, x0, __TTemP0@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	ldr w0, [x0]

	sub w1, w1, w0
	adrp x0, __TTemP1@PAGE
	add x0, x0, __TTemP1@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP1@PAGE ; TAC_MOVE
	add x0, x0, __TTemP1@PAGEOFF
	ldr w1, [x0]
	adrp x0, _v@PAGE
	add x0, x0, _v@PAGEOFF
	sxtw x1, w1
	ldr w1, [x0, x1, lsl 2]
	adrp x0, __TTemP2@PAGE
	add x0, x0, __TTemP2@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP2@PAGE ; TAC_MOVE
	add x0, x0, __TTemP2@PAGEOFF
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

	adrp x0, lC3@PAGE ; TAC_PRINT STRING
	add x0, x0, lC3@PAGEOFF
	bl _printf
	mov w0, 1
	mov w1, 2
	mov w2, 1
	bl _add ; TAC_CALL
	mov w1, w0
	adrp x0, __TTemP3@PAGE
	add x0, x0, __TTemP3@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP3@PAGE ; TAC_MOVE
	add x0, x0, __TTemP3@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]

	adrp x0, lC4@PAGE ; TAC_PRINT STRING
	add x0, x0, lC4@PAGEOFF
	bl _printf

	adrp x0, _i@PAGE ; TAC_PRINT INT
	add x0, x0, _i@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

	adrp x0, lC6@PAGE ; TAC_PRINT STRING
	add x0, x0, lC6@PAGEOFF
	bl _printf

	mov w1, 4 ; TAC_MUL
	mov w0, 0

	mul w1, w1, w0
	adrp x0, __TTemP4@PAGE
	add x0, x0, __TTemP4@PAGEOFF
	str w1, [x0]

	mov w1, 1 ; TAC_ADD
	adrp x0, __TTemP4@PAGE
	add x0, x0, __TTemP4@PAGEOFF
	ldr w0, [x0]

	add w1, w1, w0
	adrp x0, __TTemP5@PAGE
	add x0, x0, __TTemP5@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP5@PAGE ; TAC_VECATTR
	add x0, x0, __TTemP5@PAGEOFF
	ldr w1, [x0]
	adrp x0, _v@PAGE
	add x0, x0, _v@PAGEOFF
	sxtw x1, w1
	mov w2, 10
	str w2, [x0, x1, lsl 2]

	mov w1, 4 ; TAC_DIV
	mov w0, 2

	sdiv w1, w1, w0
	adrp x0, __TTemP6@PAGE
	add x0, x0, __TTemP6@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP6@PAGE ; TAC_SUB
	add x0, x0, __TTemP6@PAGEOFF
	ldr w1, [x0]
	mov w0, 1

	sub w1, w1, w0
	adrp x0, __TTemP7@PAGE
	add x0, x0, __TTemP7@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP7@PAGE ; TAC_MOVE
	add x0, x0, __TTemP7@PAGEOFF
	ldr w1, [x0]
	adrp x0, _v@PAGE
	add x0, x0, _v@PAGEOFF
	sxtw x1, w1
	ldr w1, [x0, x1, lsl 2]
	adrp x0, __TTemP8@PAGE
	add x0, x0, __TTemP8@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP8@PAGE ; TAC_MOVE
	add x0, x0, __TTemP8@PAGEOFF
	ldr w1, [x0]
	adrp x0, _b@PAGE
	add x0, x0, _b@PAGEOFF
	str w1, [x0]

	adrp x0, lC7@PAGE ; TAC_PRINT STRING
	add x0, x0, lC7@PAGEOFF
	bl _printf

	adrp x0, _b@PAGE ; TAC_PRINT INT
	add x0, x0, _b@PAGEOFF
	ldr w0, [x0]
	str w0, [sp]
	adrp x0, lC0@PAGE
	add x0, x0, lC0@PAGEOFF
	bl _printf

	mov w1, 4 ; TAC_MUL
	mov w0, 0

	mul w1, w1, w0
	adrp x0, __TTemP9@PAGE
	add x0, x0, __TTemP9@PAGEOFF
	str w1, [x0]

	mov w1, 1 ; TAC_ADD
	adrp x0, __TTemP9@PAGE
	add x0, x0, __TTemP9@PAGEOFF
	ldr w0, [x0]

	add w1, w1, w0
	adrp x0, __TTemP10@PAGE
	add x0, x0, __TTemP10@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP10@PAGE ; TAC_MOVE
	add x0, x0, __TTemP10@PAGEOFF
	ldr w1, [x0]
	adrp x0, _v@PAGE
	add x0, x0, _v@PAGEOFF
	sxtw x1, w1
	ldr w1, [x0, x1, lsl 2]
	adrp x0, __TTemP11@PAGE
	add x0, x0, __TTemP11@PAGEOFF
	str w1, [x0]

	adrp x0, _b@PAGE ; TAC_EQ
	add x0, x0, _b@PAGEOFF
	ldr w1, [x0]
	adrp x0, __TTemP11@PAGE
	add x0, x0, __TTemP11@PAGEOFF
	ldr w0, [x0]

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP12@PAGE
	add x0, x0, __TTemP12@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP12@PAGE
	add x0, x0, __TTemP12@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL0

	adrp x0, lC9@PAGE ; TAC_PRINT STRING
	add x0, x0, lC9@PAGEOFF
	bl _printf

	b _LLabeL1 ; TAC_JUMP

_LLabeL0:

	adrp x0, lC10@PAGE ; TAC_PRINT STRING
	add x0, x0, lC10@PAGEOFF
	bl _printf

_LLabeL1:

	adrp x0, _b@PAGE ; TAC_EQ
	add x0, x0, _b@PAGEOFF
	ldr w1, [x0]
	mov w0, 10

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP13@PAGE
	add x0, x0, __TTemP13@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP13@PAGE
	add x0, x0, __TTemP13@PAGEOFF
	ldr w1, [x0]
	eor w1, w1, 1
	adrp x0, __TTemP14@PAGE
	add x0, x0, __TTemP14@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP14@PAGE
	add x0, x0, __TTemP14@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL2

	adrp x0, lC11@PAGE ; TAC_PRINT STRING
	add x0, x0, lC11@PAGEOFF
	bl _printf

	b _LLabeL3 ; TAC_JUMP

_LLabeL2:

	adrp x0, lC12@PAGE ; TAC_PRINT STRING
	add x0, x0, lC12@PAGEOFF
	bl _printf

_LLabeL3:

	adrp x0, _a@PAGE ; TAC_MOVE
	add x0, x0, _a@PAGEOFF
	mov w1, 0
	str w1, [x0]

	adrp x0, _b@PAGE ; TAC_MOVE
	add x0, x0, _b@PAGEOFF
	mov w1, 0
	str w1, [x0]

	adrp x0, _a@PAGE ; TAC_EQ
	add x0, x0, _a@PAGEOFF
	ldr w1, [x0]
	mov w0, 0

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP15@PAGE
	add x0, x0, __TTemP15@PAGEOFF
	str w1, [x0]

	adrp x0, _b@PAGE ; TAC_EQ
	add x0, x0, _b@PAGEOFF
	ldr w1, [x0]
	mov w0, 0

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP16@PAGE
	add x0, x0, __TTemP16@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP15@PAGE ; TAC_AND
	add x0, x0, __TTemP15@PAGEOFF
	ldr w1, [x0]
	adrp x0, __TTemP16@PAGE
	add x0, x0, __TTemP16@PAGEOFF
	ldr w0, [x0]

	and w1, w1, w0
	adrp x0, __TTemP17@PAGE
	add x0, x0, __TTemP17@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP17@PAGE
	add x0, x0, __TTemP17@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL4

	adrp x0, lC13@PAGE ; TAC_PRINT STRING
	add x0, x0, lC13@PAGEOFF
	bl _printf

	b _LLabeL5 ; TAC_JUMP

_LLabeL4:

	adrp x0, lC14@PAGE ; TAC_PRINT STRING
	add x0, x0, lC14@PAGEOFF
	bl _printf

_LLabeL5:

	adrp x0, _a@PAGE ; TAC_EQ
	add x0, x0, _a@PAGEOFF
	ldr w1, [x0]
	mov w0, 0

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP18@PAGE
	add x0, x0, __TTemP18@PAGEOFF
	str w1, [x0]

	adrp x0, _b@PAGE ; TAC_EQ
	add x0, x0, _b@PAGEOFF
	ldr w1, [x0]
	mov w0, 1

	cmp w1, w0
	cset w1, eq
	adrp x0, __TTemP19@PAGE
	add x0, x0, __TTemP19@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP18@PAGE ; TAC_OR
	add x0, x0, __TTemP18@PAGEOFF
	ldr w1, [x0]
	adrp x0, __TTemP19@PAGE
	add x0, x0, __TTemP19@PAGEOFF
	ldr w0, [x0]

	orr w1, w1, w0
	adrp x0, __TTemP20@PAGE
	add x0, x0, __TTemP20@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP20@PAGE
	add x0, x0, __TTemP20@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL6

	adrp x0, lC15@PAGE ; TAC_PRINT STRING
	add x0, x0, lC15@PAGEOFF
	bl _printf

	b _LLabeL7 ; TAC_JUMP

_LLabeL6:

	adrp x0, lC16@PAGE ; TAC_PRINT STRING
	add x0, x0, lC16@PAGEOFF
	bl _printf

_LLabeL7:

	adrp x0, lC17@PAGE ; TAC_PRINT STRING
	add x0, x0, lC17@PAGEOFF
	bl _printf

	adrp x0, _i@PAGE ; TAC_MOVE
	add x0, x0, _i@PAGEOFF
	mov w1, 0
	str w1, [x0]

_LLabeL8:

	adrp x0, _i@PAGE ; TAC_LESS
	add x0, x0, _i@PAGEOFF
	ldr w1, [x0]
	mov w0, 10

	cmp w1, w0
	cset w1, lt
	adrp x0, __TTemP21@PAGE
	add x0, x0, __TTemP21@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP21@PAGE
	add x0, x0, __TTemP21@PAGEOFF
	ldr w1, [x0]
	cmp w1, 0
	beq _LLabeL9

	adrp x0, lC18@PAGE ; TAC_PRINT STRING
	add x0, x0, lC18@PAGEOFF
	bl _printf

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
	adrp x0, __TTemP22@PAGE
	add x0, x0, __TTemP22@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP22@PAGE ; TAC_MOVE
	add x0, x0, __TTemP22@PAGEOFF
	ldr w1, [x0]
	adrp x0, _i@PAGE
	add x0, x0, _i@PAGEOFF
	str w1, [x0]

	b _LLabeL8 ; TAC_JUMP

_LLabeL9:

	adrp x0, lC20@PAGE ; TAC_PRINT STRING
	add x0, x0, lC20@PAGEOFF
	bl _printf

	mov w1, 20 ; TAC_MUL
	mov w0, 0

	mul w1, w1, w0
	adrp x0, __TTemP23@PAGE
	add x0, x0, __TTemP23@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP23@PAGE ; TAC_MOVE
	add x0, x0, __TTemP23@PAGEOFF
	ldr w1, [x0]
	adrp x0, _1a@PAGE
	add x0, x0, _1a@PAGEOFF
	str w1, [x0]

	adrp x0, _1a@PAGE ; TAC_RET
	add x0, x0, _1a@PAGEOFF
	ldr w0, [x0]
	ldp x29, x30, [sp], 16
	ret

	ldp x29, x30, [sp], 16 ; TAC_ENDFUN
	ret
FEND2_main:

	.text ;TAC_BEGINFUN
	.align 2
	.globl _add
_add:
FBEGIN_add:
	stp	x29, x30, [sp, -16]!
	mov	x29, sp

	add w1, w1, w0
	adrp x0, __TTemP24@PAGE
	add x0, x0, __TTemP24@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP24@PAGE ; TAC_ADD
	add x0, x0, __TTemP24@PAGEOFF
	ldr w1, [x0]

	add w1, w1, w0
	adrp x0, __TTemP25@PAGE
	add x0, x0, __TTemP25@PAGEOFF
	str w1, [x0]

	adrp x0, __TTemP25@PAGE ; TAC_RET
	add x0, x0, __TTemP25@PAGEOFF
	ldr w0, [x0]
	ldp x29, x30, [sp], 16
	ret

	ldp x29, x30, [sp], 16 ; TAC_ENDFUN
	ret
FEND2_add:
