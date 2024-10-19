.data 99, 456, 9998 
.text
lui x3, 0x10000
ld t3, 0(x3)
ld t4, 0(x3)
ld x31, 0(x3)
ld t5, 0(x3)
ld t6, 8(x3)
ld x1, 8(x3)
ld ra, 0(x3)
ld x2, 8(x3)
beq t3, t4, L1 
bne x31, t5, L2 
L4: blt t6, x0, L3
L1: bge x1, zero, L3
bltu ra, x2, L5 
L2: bgeu sp, x3, L1
L3: jal gp, L6
L6: lui t0, 524287
L5: lui x6, -524288
