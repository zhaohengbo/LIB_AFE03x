#include "F28x_Project.h"
#include "hal_afe_pvt.h"

#pragma CODE_SECTION(HAL_afe_cpuTimer0_isr,"isrRamFuncs");
interrupt void HAL_afe_cpuTimer0_isr(void)
{
	INT32 tx_value;
	HAL_afe_handle_s.txIntCnt++;
	if(HAL_afe_handle_s.timer01ShotFlag == 0)
	{
		tx_value = ((INT32)(INT16)HAL_afe_handle_s.bufDat_p[0] * PHY_tx_data_s.upsScale) >> 10;
		HAL_afe_handle_s.bufDat_p++;
		if(tx_value > 32767)
		{
			tx_value = 32767;
		}
		if(tx_value < -32767)
		{
			tx_value = -32767;
		}
		//Warning:must be the same as that in hal_spi.c
		SpiaRegs.SPITXBUF = (tx_value + 32767);
		HAL_afe_handle_s.txBufIdx++;
		if(HAL_afe_handle_s.txBufIdx < HAL_afe_handle_s.txBufSize)
		{
			PieCtrlRegs.PIEACK.bit.ACK1 = 1;
			return;
		}
		else
		{
			HAL_afe_handle_s.txBufIdx = 0;
			HAL_afe_handle_s.bufDat_p = HAL_afe_handle_s.txBufReady_p;
			HAL_afe_handle_s.txBufSize = HAL_afe_handle_s.txSize;
		}
	}
	txSymbDone = 1;
	PieCtrlRegs.PIEIFR5.bit.INTx1 = 1;
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}