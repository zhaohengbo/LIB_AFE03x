#include "F28x_Project.h"
#include "hal_afe_pvt.h"

HAL_status_t HAL_afe_rxStart(void *setParms)
{
	HAL_afe_rxSetParms_t *para = (HAL_afe_rxSetParms_t *)setParms;
	UINT16 dstBufIdx0,dstBufIdx1;
	HAL_afe031_rxEnable();
	dstBufIdx0 = para->dstBufIdx;
	dstBufIdx1 = (dstBufIdx0 + 1) & 0x1;
	HAL_afe_handle_s.rxBufIdx = dstBufIdx0;
	HAL_afe_handle_s.rxBufPtr_p[dstBufIdx0] = para->dstBufAddr[dstBufIdx0];
	HAL_afe_handle_s.rxBufPtr_p[dstBufIdx1] = para->dstBufAddr[dstBufIdx1];
	HAL_afe_handle_s.rxBufSize[dstBufIdx0] = para->size[dstBufIdx0];
	HAL_afe_handle_s.rxBufSize[dstBufIdx1] = para->size[dstBufIdx1];
	HAL_afe_handle_s.rxBufDat_p = HAL_afe_handle_s.rxBufPtr_p[dstBufIdx0];
	HAL_afe_handle_s.activeBufIdx = dstBufIdx0;
	HAL_afe_handle_s.activeBufSize = para->size[dstBufIdx0];
	HAL_afe_handle_s.adcCnt = 0;
	HAL_afe_adcStart();
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_rxStop(void *setParms)
{
	HAL_afe_adcStop();
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_rxReCfg(void *setParms)
{
	HAL_afe_rxSetParms_t *para = (HAL_afe_rxSetParms_t *)setParms;
	UINT16 dstBufIdx0,dstBufIdx1;
	dstBufIdx0 = para->dstBufIdx;
	dstBufIdx1 = (dstBufIdx0 + 1) & 0x1;
	HAL_afe_handle_s.rxBufIdx = dstBufIdx0;
	HAL_afe_handle_s.rxBufPtr_p[dstBufIdx0] = para->dstBufAddr[dstBufIdx0];
	HAL_afe_handle_s.rxBufPtr_p[dstBufIdx1] = para->dstBufAddr[dstBufIdx1];
	HAL_afe_handle_s.rxBufSize[dstBufIdx0] = para->size[dstBufIdx0];
	HAL_afe_handle_s.rxBufSize[dstBufIdx1] = para->size[dstBufIdx1];
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_setGain(void *setParms)
{
	int16 *para = (int16 *)setParms;
	HAL_afe_handle_s.agcGainVal = (*para);
	HAL_afe031_writeRxGain(HAL_afe_handle_s.agcGainVal);
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_updateGain(void *setParms)
{
	int16 *para = (int16 *)setParms;
	HAL_afe_handle_s.agcGainVal = (*para);
	HAL_afe_handle_s.updateGainFlag = 1;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_cancelGain(void *setParms)
{
	HAL_afe_handle_s.updateGainFlag = 0;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txDmaSize(void *setParms)
{
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txDmaAddr(void *setParms)
{
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_cpuTimer1CfgStart(void)
{
	CpuTimer1Regs.TPR.all = 0x57;
	CpuTimer1Regs.TPRH.all = 0x2;
	CpuTimer1Regs.PRD.all = 0xfffff;
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
	CpuTimer0Regs.TCR.bit.SOFT = 0;
	CpuTimer0Regs.TCR.bit.FREE = 0;
	CpuTimer0Regs.TCR.bit.TIE = 0;
	CpuTimer0Regs.TCR.bit.TSS = 0;
	return HAL_STAT_SUCCESS;
}

Uint32 HAL_cpuTimer1GetCount(void)
{
	return CpuTimer1Regs.TIM.all;
}

HAL_status_t HAL_cpuTimer0TimeoutCfg(void *setParms)
{
	HAL_afe_txSetParms_t *para = (HAL_afe_txSetParms_t *)setParms;
	ConfigCpuTimer(&CpuTimer0,0x41F00000,para->t0PrdInUs);
	HAL_afe_handle_s.timer01ShotFlag = ((para->t0Flags & 0x2) >> 1);
	if(para->t0Flags & 0x1)
	{
		PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	}
	else
	{
		INTM_DISABLE;
		PieCtrlRegs.PIEIER1.bit.INTx7 = 0;
		asm("	NOP");
		asm("	NOP");
		asm("	NOP");
		asm("	NOP");
		asm("	NOP");
		IFR &= 0xfffe;
		INTM_RESTORE;
	}
	HAL_afe_handle_s.cb_p = para->cb_p;
	HAL_afe_handle_s.cb_param = para->cb_param;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_cpuTimer0Start()
{
	CpuTimer0Regs.TCR.bit.TSS = 0;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_cpuTimer0Stop()
{
	CpuTimer0Regs.TCR.bit.TSS = 1;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_cpuTimerCfg()
{
	ConfigCpuTimer(&CpuTimer0,0x42700000,0x40000000);
	HAL_cpuTimer1CfgStart();
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txCfg(void *setParms)
{
	HAL_afe_txSetParms_t *para = (HAL_afe_txSetParms_t *)setParms;
	HAL_afe_handle_s.txBufReady_p = para->txBuf_p;
	HAL_afe_handle_s.bufDat_p = para->txBuf_p;
	HAL_afe_handle_s.txSize = para->txSize;
	HAL_afe_handle_s.txBufSize = para->txSize;
	HAL_afe_handle_s.txBufIdx = 0;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txStart(void *setParms)
{
	HAL_afe031_txEnable();
	HAL_afe031_dacEnable();
	DELAY_US(20);
	HAL_afe_handle_s.bufDat_p = HAL_afe_handle_s.txBufReady_p;
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
	EALLOW;
	EDIS;
	HAL_afe_handle_s.txActive = 1;
	CpuTimer0Regs.TCR.bit.TSS = 0;
	CpuTimer0Regs.TCR.bit.TIE = 1;
	CpuTimer0Regs.TCR.bit.TIF = 1;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txStop(void *setParms)
{
	EALLOW;
	EDIS;
	HAL_afe_handle_s.txActive = 0;
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TIE = 0;
	CpuTimer0Regs.TCR.bit.TIF = 1;
	INTM_DISABLE;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 0;
	asm("	NOP");
	asm("	NOP");
	asm("	NOP");
	asm("	NOP");
	asm("	NOP");
	IFR &= 0xfffe;
	PieCtrlRegs.PIEIFR1.bit.INTx7 = 0;
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;
	INTM_RESTORE;
	DELAY_US(40);
	HAL_afe031_dacDisable();
	HAL_afe031_txDisable();
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_txReCfg(void *setParms)
{
	HAL_afe_txSetParms_t *para = (HAL_afe_txSetParms_t *)setParms;
	HAL_afe_handle_s.txSize = para->txSize;
	HAL_afe_handle_s.txBufReady_p = para->txBuf_p;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_rxDmaTime(void *getParms)
{
	UINT32 *para = (UINT32 *)getParms;
	*para = HAL_afe_handle_s.rxDmaTime;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_zcTime(void *getParms)
{
	HAL_afe_zcTime_t *para = (HAL_afe_zcTime_t *)getParms;
	para->zcaTime = HAL_afe_handle_s.zcaTime;
	para->zcbTime = HAL_afe_handle_s.zcbTime;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_rxDmaIdx(void *getParms)
{
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_rndNum(void *getParms)
{
	UINT16 rnd_num = 0,i;
	UINT16 *para = (UINT16 *)getParms;
	for(i=0;i<16;i++)
	{
		rnd_num |= (AdcResult.ADCRESULT0 & 0x1) << i;
	}
	*para = rnd_num;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afe_prfCfg(void *setParms)
{
	UINT16 old_tss; 
	HAL_afe_prfParms_t *para = (HAL_afe_prfParms_t *)setParms;
	HAL_afe_handle_s.prf.rx_fs_kHz = para->rx_fs_kHz;
	HAL_afe_handle_s.prf.tx_fs_kHz = para->tx_fs_kHz;
	HAL_afe_handle_s.prf.tx_pwm_kHz = para->tx_pwm_kHz;
	HAL_afe_handle_s.prf.band = para->band;
	
	//FIX ME:these values are different between DSPs
	HAL_afe_epwm_handle_s.socPrd = (60000UL / HAL_afe_handle_s.prf.rx_fs_kHz) << 1;
	HAL_afe_handle_s.t0Prd = 2000 / HAL_afe_handle_s.prf.tx_fs_kHz;
	
	old_tss = CpuTimer0Regs.TCR.bit.TSS;
	HAL_cfgCpuTimer0(60,HAL_afe_handle_s.prf.tx_fs_kHz);//28035:60MHz
	CpuTimer0Regs.TCR.bit.TSS = old_tss;
	
	HAL_afe_epwm_handle_s.prd = (60000UL / HAL_afe_handle_s.prf.tx_pwm_kHz) >> 1;
	
	return HAL_STAT_SUCCESS;
}

void HAL_cfgCpuTimer0(UINT16 CPUFreqInMHz,UINT16 tx_fs_kHz)
{
	UINT32 prd = ((CPUFreqInMHz * 1000) / tx_fs_kHz) - 1;
	CpuTimer0Regs.PRD.all = prd;
	CpuTimer0Regs.TPR.all = 0;
	CpuTimer0Regs.TPRH.all = 0;
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
	CpuTimer0Regs.TCR.bit.SOFT = 0;
	CpuTimer0Regs.TCR.bit.FREE = 0;
	CpuTimer0Regs.TIE.bit.TSS = 1;
}
