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

	MOV R10, #8
	LDR R3, =DST
	LDR R0, = SRC
	LDR R1, [R0]
	
UP	
	AND R2, R1, 0X0F
	CMP R1, 0X09
	BCC DW
	ADD R2, #0X07
	
DW	
	ADD R2, 0x30
	STR R2, [R3], #4
	LSRS R1, R1, #4
	SUBS R10, #1
	
	BNE UP
	
STOP	B	STOP

SRC DCD 0X1A2B3C4D

	AREA mydata, DATA, READWRITE
DST DCD 0