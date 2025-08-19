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

	LDR R0, =5
	BL FACT
	LDR R1, =result
	STR R0, [R1]

DONE B DONE

FACT	
		CMP R0, #1
		BLE Base_Case
		PUSH {R0, LR}
		SUB R0, R0, #1
		BL FACT
		POP {R1, LR}
		MUL R0, R0, R1
		POP {PC}
		
Base_Case
			MOV R0, #1
			POP {PC}
			
	AREA mydata, DATA, READWRITE
result DCD 0
	END