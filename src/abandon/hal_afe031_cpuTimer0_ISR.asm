
	.def _HAL_afe_cpuTimer0_isr
	.ref _HAL_afe_handle_s
	.ref _PHY_tx_data_s
	.ref _txSymbDone

	.section isrRamFuncs

_HAL_afe_cpuTimer0_isr:
	ASP          
	MOVL    *SP++, XAR4
	MOVL    *SP++, XAR3
	MOVL    *SP++, XAR1
	SETC    SXM
	MOV     ACC, #32767
	MOVL    XAR3, ACC
	NEG     ACC
	MOVL    XAR1, ACC
	MOVL    XAR4, #_HAL_afe_handle_s+0x12;18
	INC     *+XAR4[5]
	MOV     AL, *+XAR4[7]
	SBF     LPEND, NEQ
	MOVL    XAR3, *+XAR4[2]
	MOV     AL, *XAR3++
	MOVL    *+XAR4[2], XAR3
	MOV     DP, #_PHY_tx_data_s
	MOV     T, @_PHY_tx_data_s.upsScale
	MPY     ACC, T, AL
	SFR     ACC, 10
	MOVL    XAR3, #0x007fff
	MPY     P, AR3, #-1
	MINL    ACC, XAR3
	MAXL    ACC, P
	ADD     ACC, #32768
	MOV     DP, #0x1dd;Warning:This SPIB,not SPIA!!!!
	MOV     @0x8, AL;Warning:must be the same as that in hal_spi.c
	MOV     AL, *+XAR4[6]
	INC     *+XAR4[4]
	CMP     AL, *+XAR4[4]
	BF      LPEND1, GT
	MOV     *+XAR4[4], #0
	MOVL    ACC, *+XAR4[0]
	MOVL    *+XAR4[2], ACC
	MOVL    XAR3, #_HAL_afe_handle_s.txSize
	MOV     AL, *+XAR3[0]
	MOV     *+XAR4[6], AL
LPEND:
	MOV     DP, #_txSymbDone
	MOV     @_txSymbDone, #0x0001
	MOVL    XAR1, #0x000ceb
	MOV     *+XAR1[0], #0x0001
LPEND1:
	MOVW    DP, #0x33
	MOV     @0x21, #0x0001
	MOVL    XAR1, *--SP
	MOVL    XAR3, *--SP
	MOVL    XAR4, *--SP
	NASP    
	IRET    
