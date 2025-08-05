        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x10010000
        DCD     Reset_Handler
        ALIGN

        AREA    mycode, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler

Reset_Handler
        LDR     R0, =N1
        LDR     R1, =N2
        LDR     R6, =Result
        MOV     R2, #4

        MOVS    R7, #0
        SUBS    R7, R7, #0

Up
        LDR     R3, [R0], #4
        LDR     R4, [R1], #4
        SBCS    R5, R3, R4
        STR     R5, [R6], #4

        SUBS    R2, R2, #1
        BNE     Up

Stop	B       Stop


        AREA    mydata, DATA, READONLY
N1      DCD     0x44444444,0x33333333,0x22222222,0x11111111
N2      DCD     0xDDDDDDDD

        AREA    resultdata, DATA, READWRITE
Result  DCD     0, 0, 0, 0

        END
