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

        MOV     R2, #0
H_LOOP
        CMP     R1, #100
        BLT     H_DONE
        SUB     R1, R1, #100
        ADD     R2, R2, #1
        B       H_LOOP
H_DONE

        MOV     R3, #0
T_LOOP
        CMP     R1, #10
        BLT     T_DONE
        SUB     R1, R1, #10
        ADD     R3, R3, #1
        B       T_LOOP
T_DONE

        LSL     R4, R2, #8
        LSL     R5, R3, #4
        ORR     R6, R4, R5
        ORR     R6, R6, R1

        LDR     R7, =DST
        STR     R6, [R7]

Stop	B	Stop

        AREA    mydata, DATA, READONLY
SRC     DCD     0x0000001A

        AREA    resultdata, DATA, READWRITE
DST     DCD     0

        END
