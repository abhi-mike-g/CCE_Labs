        AREA RESET, DATA, READONLY
        EXPORT __Vectors
__Vectors
		DCD 0X10001000
        DCD Reset_Handler
        ALIGN

        AREA mycide, CODE, READONLY
        ENTRY
        EXPORT Reset_Handler

Reset_Handler
        LDR     R0, =SRC
        ADD     R1, R0, #36
        MOV     R4, #5

UP
        LDR     R2, [R0]
        LDR     R3, [R1]
        STR     R3, [R0]
        STR     R2, [R1]

        ADD     R0, R0, #4
        SUB     R1, R1, #4

        SUBS    R4, R4, #1
        BNE     UP

STOP	B       STOP

        AREA READDATA, DATA, READWRITE
SRC     DCD 0x15644621,0x15649653,0x15648643,0x15649531,0x15646879, 0x15660837,0x15647153,0x15646180,0x15649753,0x15646984
