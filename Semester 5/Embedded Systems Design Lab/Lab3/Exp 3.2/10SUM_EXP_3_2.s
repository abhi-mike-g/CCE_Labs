        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x10000000
        DCD     Reset_Handler
        ALIGN
        AREA    mycode, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler
Reset_Handler
        LDR     R0, =SRC
        MOV     R2, #0
        MOV     R5, #0
        MOV     R3, #10

UP      
        LDR     R1, [R0], #4
        ADDS    R2, R2, R1
        ADC     R5, R5, #0
        SUBS    R3, R3, #1
        BNE     UP

        LDR     R4, =Result
        STR     R2, [R4], #4
        STR     R5, [R4]

STOP    B       STOP

        AREA    mydata, DATA, READWRITE
SRC     DCD     0x15644621,0x15649653,0x15648643,0x15649531,0x15646879,0x15660837,0x15647153,0x15646180,0x15649753,0x15646984

Result  DCD     0, 0

        END
