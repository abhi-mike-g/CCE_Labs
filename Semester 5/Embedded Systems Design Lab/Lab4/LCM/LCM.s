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
        LDR     R4, =N1
        LDR     R8, [R4]
        LDR     R4, =N2
        LDR     R9, [R4]

        CMP     R8, #0
        BEQ     StoreZero
        CMP     R9, #0
        BEQ     StoreZero

        MOV     R0, R8
        MOV     R1, R9

GCD_Loop
        CMP     R1, #0
        BEQ     GCD_Done
        UDIV    R6, R0, R1
        MUL     R7, R6, R1
        SUB     R2, R0, R7
        MOV     R0, R1
        MOV     R1, R2
        B       GCD_Loop

GCD_Done
        UDIV    R10, R8, R0
        UMULL   R2, R3, R10, R9

        LDR     R4, =Result
        STR     R2, [R4]
        STR     R3, [R4, #4]
        B       Done

StoreZero
        LDR     R4, =Result
        MOV     R2, #0
        MOV     R3, #0
        STR     R2, [R4]
        STR     R3, [R4, #4]

Done
        B       Done

        AREA    mydata, DATA, READONLY
N1      DCD     0x00000018
N2      DCD     0x00000020

        AREA    resultdata, DATA, READWRITE
Result  DCD     0, 0

        END
