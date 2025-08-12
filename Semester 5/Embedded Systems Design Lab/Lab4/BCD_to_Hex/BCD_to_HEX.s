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
        LDR     R0, =SRC
        LDR     R1, [R0]

        AND     R2, R1, #0x0F
        MOV     R3, R1
        LSRS    R3, R3, #4
        AND     R3, R3, #0x0F

        LSLS    R4, R3, #3
        LSLS    R5, R3, #1
        ADD     R4, R4, R5

        ADD     R6, R4, R2

        LDR     R7, =DST
        STR     R6, [R7]

STOP    B       STOP

        AREA    mydata, DATA, READONLY
SRC     DCD     0x0000001A

        AREA    resultdata, DATA, READWRITE
DST     DCD     0

        END
