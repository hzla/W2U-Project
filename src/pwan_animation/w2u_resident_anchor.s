	.thumb
	.syntax unified

	.extern SVC_WaitByLoop
	.global W2U_PwanResidentAnchor
	.thumb_func
W2U_PwanResidentAnchor:
	ldr r0, =SVC_WaitByLoop
	bx lr
