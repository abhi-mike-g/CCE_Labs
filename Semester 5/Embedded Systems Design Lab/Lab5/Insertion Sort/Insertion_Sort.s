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
        LDR R4, =ARR
        MOV R5, #10
        BL InsertionSort

DONE    B DONE

InsertionSort
        MOV R6, #1

Outer_Loop
        CMP R6, R5
        BGE FINISH

        LDR R7, [R4, R6, LSL #2]
        SUB R8, R6, #1

Inner_Loop
        CMP R8, #0
        BLT Insert_Key

        LDR R9, [R4, R8, LSL #2]
        CMP R9, R7
        BLE Insert_Key

        ADD R11, R8, #1
        STR R9, [R4, R11, LSL #2]

        SUB R8, R8, #1
        B Inner_Loop

Insert_Key
        ADD R10, R8, #1
        STR R7, [R4, R10, LSL #2]

        ADD R6, R6, #1
        B Outer_Loop

FINISH  BX LR

        AREA mydata, DATA, READWRITE

ARR     DCD 64, 25, 12, 22, 11, 5, 78, 90, 43, 2

        END
