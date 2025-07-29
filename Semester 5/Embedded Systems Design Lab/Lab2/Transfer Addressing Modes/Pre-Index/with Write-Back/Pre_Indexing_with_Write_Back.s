    AREA RESET, DATA, READONLY
    EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    ALIGN
    AREA mycode, CODE, READONLY
ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =SRC
    SUB R0, R0, #4
    LDR R1, =DST
    SUB R1, R1, #4

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

    LDR R2, [R0, #4]!
    STR R2, [R1, #4]!

STOP B STOP

SRC DCD 0x12345678, 0xABCDEF01, 0xA2BC4EF1, 0x32546710, 0x22222222, 0xCFDAB234, 0x89754321, 0x10001001, 0xABBCFD13, 0x00001000

    AREA DATASEG, DATA, READWRITE
DST SPACE 40

    END