#include "F28x_Project.h"
#include "hal_afe_adc.h"

#pragma CODE_SECTION(HAL_afe_adcint_isr,"isrRamFuncs");
interrupt void HAL_afe_adcint_isr(void)
{
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;
#ifdef F2803X
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;//Clear ADCINT1 flag reinitialize for next SOC
#else//for F28335
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;// Reset SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;// Clear INT SEQ1 bit
#endif
	HAL_afe_handle_s.rxBufDat_p[0] = AdcResult.ADCRESULT0;
	HAL_afe_handle_s.rxBufDat_p[1] = AdcResult.ADCRESULT1;
	HAL_afe_handle_s.rxBufDat_p[2] = AdcResult.ADCRESULT2;
	HAL_afe_handle_s.rxBufDat_p[3] = AdcResult.ADCRESULT3;
	HAL_afe_handle_s.rxBufDat_p += 4;
	HAL_afe_handle_s.adcCnt += 4;
	HAL_afe_handle_s.adcIntCnt++;
	if(HAL_afe_handle_s.adcCnt >= HAL_afe_handle_s.activeBufSize)
	{
		HAL_afe_handle_s.adcCnt = 0;
		HAL_afe_handle_s.zcaTime = ReadCpuTimer0Counter();
		HAL_afe_handle_s.activeBufIdx = HAL_afe_handle_s.rxBufIdx;
		HAL_afe_handle_s.rxBufIdx ^= 0x1;
		if(HAL_afe_handle_s.updateGainFlag != 0)
		{
			HAL_afe_handle_s.updateGainFlag = 0;
			HAL_afe031_writeRxGain_noWait(HAL_afe031_rxGainLut[HAL_afe_handle_s.agcGainVal]);
		}
		HAL_afe_handle_s.rxBufDat_p[0] = HAL_afe_handle_s.rxBufPtr_p[HAL_afe_handle_s.activeBufIdx][0];
		HAL_afe_handle_s.rxBufDat_p[1] = HAL_afe_handle_s.rxBufPtr_p[HAL_afe_handle_s.activeBufIdx][1];
		HAL_afe_handle_s.activeBufSize = HAL_afe_handle_s.rxBufSize[HAL_afe_handle_s.activeBufIdx];
		afeReadyFlag++;
		PieCtrlRegs.PIEIER12.bit.INTx7 = 1;
	}
}