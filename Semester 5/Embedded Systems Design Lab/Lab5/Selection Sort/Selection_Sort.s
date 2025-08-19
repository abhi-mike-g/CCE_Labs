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
	LDR R4,=ARR
	MOV R4, #0

Outer_Loop	CMP R0, #n
			BGE	Done
			
			MOV R1, R0
			ADD R2, R0, #1
			
Inner_Loop	
			CMP R2, #n
			BGE Swap_Elements
			
			LDR R3, [R4, R1, LSL #2]
			LDR R5, [R4, R2, LSL #2]
			CMP R5, R3
			BGE Skip_Update
			MOV R1, R2
			
Skip_Update	
			ADD R2, R2, #1
			B Inner_Loop
			
Swap_Elements
				CMP R0, R1
				BEQ Next_Outer
				
				LDR R3, [R4, R0, LSL #2]
				LDR R5, [R4, R0, LSL #2]
				STR R5, [R4, R0, LSL #2]
				STR R3, [R4, R1, LSL #2]
				
Next_Outer
			ADD R0, R0, #1
			B	Outer_Loop
			
Done B Done

	AREA	mydata, DATA, READWRITE
ARR	DCD	64, 25, 22, 12, 11
n	EQU	5
	END