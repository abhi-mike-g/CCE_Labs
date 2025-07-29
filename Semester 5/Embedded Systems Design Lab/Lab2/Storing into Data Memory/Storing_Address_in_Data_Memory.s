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
    LDR R1, =DST

    LDR R3, [R0, #16]
    STR R3, [R1], #4

    ADD R4, R0, #(7 * 4)
    LDR R3, [R4]
    STR R3, [R1], #4

    ADD R5, R0, #(2 * 4)
    LDR R3, [R5]
    STR R3, [R1], #4

    ADD R6, R0, #(9 * 4)
    LDR R3, [R6]
    STR R3, [R1], #4

    LDR R3, [R0, #0]
    STR R3, [R1], #4

    LDR R3, [R0, #12]
    STR R3, [R1], #4

    LDR R3, [R0, #24]
    STR R3, [R1], #4

    LDR R3, [R0, #4]
    STR R3, [R1], #4

STOP B STOP

SRC DCD 0x12345678, 0xABCDEF01, 0xA2BC4EF1, 0x32546710, 0x22222222, 0xCFDAB234, 0x89754321, 0x10001001, 0xABBCFD13, 0x00001000

    AREA DATASEG, DATA, READWRITE
DST SPACE 40

    END