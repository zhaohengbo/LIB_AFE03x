#include "F28x_Project.h"
#include "hal_afe_pvt.h"

HAL_status_t HAL_afe_rxCfg(void *setParms);
HAL_status_t HAL_afe_rxStart(void *setParms);
HAL_status_t HAL_afe_rxStop(void *setParms);
HAL_status_t HAL_afe_rxReCfg(void *setParms);
HAL_status_t HAL_afe_setGain(void *setParms);
HAL_status_t HAL_afe_updateGain(void *setParms);
HAL_status_t HAL_afe_cancelGain(void *setParms);
HAL_status_t HAL_afe_adcOffsetAdj(void *setParms);
HAL_status_t HAL_afe_txDmaSize(void *setParms);
HAL_status_t HAL_afe_txDmaAddr(void *setParms);
HAL_status_t HAL_cpuTimer1CfgStart(void);
Uint32 HAL_cpuTimer1GetCount(void);
HAL_status_t HAL_cpuTimer0TimeoutCfg(void *setParms);
HAL_status_t HAL_cpuTimer0Start();
HAL_status_t HAL_cpuTimer0Stop();

HAL_status_t HAL_cpuTimerCfg();

HAL_status_t HAL_afe_txCfg(void *setParms);
HAL_status_t HAL_afe_txStart(void *setParms);
HAL_status_t HAL_afe_txStop(void *setParms);
HAL_status_t HAL_afe_txReCfg(void *setParms);

HAL_status_t HAL_afe_rxDmaTime(void *getParms);
HAL_status_t HAL_afe_zcTime(void *getParms);
HAL_status_t HAL_afe_rxDmaIdx(void *getParms);
HAL_status_t HAL_afe_rndNum(void *getParms);

HAL_status_t HAL_afe_prfCfg(void *setParms)
{
	UINT16 old_tss; 
	HAL_afe_prfParms_t para = (HAL_afe_prfParms_t *)setParms;
	HAL_afe_handle_s.prf.rx_fs_kHz = para.rx_fs_kHz;
	HAL_afe_handle_s.prf.tx_fs_kHz = para.tx_fs_kHz;
	HAL_afe_handle_s.prf.tx_pwm_kHz = para.tx_pwm_kHz;
	HAL_afe_handle_s.prf.band = para.band;
	
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
	CpuTimer0Regs.SOFT.bit.TRB = 0;
	CpuTimer0Regs.FREE.bit.TRB = 0;
	CpuTimer0Regs.TIE.bit.TSS = 1;
}
