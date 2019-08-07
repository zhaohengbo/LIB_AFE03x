
	.def _HAL_afe_adc_isr
	.ref _HAL_afe_handle_s
	.ref _HAL_afe031_rxGainLut
	.ref _HAL_afe031_writeRxGain_noWait
	.ref _afeReadyFlag

	.section isrRamFuncs

_HAL_afe_adc_isr:
	ASP     
	MOVL    *SP++, XAR4
	MOVL    *SP++, XAR5
	MOVL    *SP++, XAR1
	MOVL    *SP++, XAR0
	SETC    SXM
	MOVW    DP, #0x33
	MOV     @0x21, #0x0001
	MOVW    DP, #0x1c4
	OR      @0x19, #0x0010
	MOVL    XAR4, #_HAL_afe_handle_s.updateGainFlag
	MOVL    XAR5, #0x000b00
	MOVL    XAR1, *+XAR4[6]
	MOVL    ACC, *XAR5++
	MOVL    *XAR1++, ACC
	MOVL    ACC, *XAR5++
	MOVL    *XAR1++, ACC
	MOVL    *+XAR4[6], XAR1
	MOVL    XAR5, #_HAL_afe_handle_s.rxBufSize
	MOV     AL, *+XAR5[3]
	ADDB    AL, #4
	MOV     *+XAR5[3], AL
	INC     *+XAR5[5]
	MOV     AL, *+XAR5[7]
	CMP     AL, *+XAR5[3]
	BF      LADC_END, HI
	MOV     *+XAR5[3], #0
	MOVW    DP, #0x30
	MOVB    XAR0, #0x1e
	MOVL    ACC, @0x8
	MOVL    *+XAR4[AR0], ACC
	MOV     AL, *+XAR5[2]
	MOV     *+XAR5[6], AL
	XORB    AL, #0x1
	MOV     *+XAR5[2], AL
	MOV     AL, *+XAR4[0]
	SBF     SKIP_UPDATE, EQ
	MOV     *+XAR4[0], #0
	MOV     AL, *+XAR4[1]
	MOV     AR0, AL
	MOVL    XAR1, #_HAL_afe031_rxGainLut
	MOV     AL, *+XAR1[AR0]
	LCR     _HAL_afe031_writeRxGain_noWait
SKIP_UPDATE:
	MOVL    ACC, XAR4
	ADD     ACC, *+XAR5[6] << 1
	ADDB    ACC, #2
	MOVL    XAR1, ACC
	MOVL    ACC, *+XAR1[0]
	MOVL    *+XAR4[6], ACC
	MOVZ    AR0, *+XAR5[6]
	MOV     AL, *+XAR5[AR0]
	MOV     *+XAR5[7], AL
	MOV     DP, #_afeReadyFlag
	INC     @_afeReadyFlag
	MOVL    XAR1, #0x000cf9
	MOV     *+XAR1[0], #0x0040
LADC_END:
	MOVL    XAR0, *--SP
	MOVL    XAR1, *--SP
	MOVL    XAR5, *--SP
	MOVL    XAR4, *--SP
	NASP    
	IRET    
