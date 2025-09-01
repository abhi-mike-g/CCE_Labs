    AREA RESET, CODE, READONLY
    EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R4, =ARR        ; base address
    MOV R0, #0          ; outer loop index

Outer_Loop
    CMP R0, #5          ; n = 5
    BGE Done

    MOV R1, R0          ; min_index = i
    ADD R2, R0, #1      ; j = i+1

Inner_Loop
    CMP R2, #5
    BGE Swap_Elements

    LDR R3, [R4, R1, LSL #2]
    LDR R5, [R4, R2, LSL #2]
    CMP R5, R3
    BGE Skip_Update
    MOV R1, R2          ; min_index = j

Skip_Update
    ADD R2, R2, #1
    B Inner_Loop

Swap_Elements
    CMP R0, R1
    BEQ Next_Outer

    LDR R3, [R4, R0, LSL #2]
    LDR R5, [R4, R1, LSL #2]
    STR R5, [R4, R0, LSL #2]
    STR R3, [R4, R1, LSL #2]

Next_Outer
    ADD R0, R0, #1
    B Outer_Loop

Done B Done

    AREA mydata, DATA, READWRITE
ARR DCD 64, 25, 22, 12, 11
    END
