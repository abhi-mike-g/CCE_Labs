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
	LDR R1, = KEY
	LDR R1, [R1]
	MOV R0, #0
	
Search_Loop	
			CMP R0, #10
			BGE Not_Found
			
			LDR R2, [R4, R0, LSL #2]
			CMP R2, R1
			BEQ Found
			
			ADD R0, R0, #1
			B Search_Loop
			
Found	B Store

Not_Found	MOV R0, #-1

Store	LDR R5, =result
		STR R0, [R5]

Done B Done

	AREA	mydata, DATA, READWRITE

ARR DCD 12, 45, 7, 89, 23, 56, 34, 90, 11, 5
KEY DCD 56
result DCD 0