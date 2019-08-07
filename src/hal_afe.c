#include "F28x_Project.h"
#include "hal_afe_pvt.h"

typedef HAL_status_t (*HAL_cfgFunc_t)(void *);

HAL_cfgFunc_t HAL_afe_get[NUM_AFE_GETPARMS] = 
{
	HAL_afe_rxDmaTime,
	HAL_afe_zcTime,
	HAL_afe_rxDmaIdx,
	HAL_afe_rndNum
};

HAL_cfgFunc_t HAL_afe_set[NUM_AFE_SETPARMS] = 
{
	HAL_afe_txCfg,
	HAL_afe_txStart,
	HAL_afe_txStop,
	HAL_afe_txReCfg,
	HAL_afe_txDmaSize,
	HAL_afe_txDmaAddr,
	HAL_cpuTimer0TimeoutCfg,
	HAL_cpuTimer0Start,
	HAL_cpuTimer0Stop,
	HAL_afe_rxStart,
	HAL_afe_rxStop,
	HAL_afe_rxReCfg,
	HAL_afe_setGain,
	HAL_afe_updateGain,
	HAL_afe_cancelGain
#ifndef F2803X
	,
	//FIX ME:remain three funcs
#endif
};

HAL_status_t HAL_afeInit(HAL_afe_prfParms_t *setParms_p)
{
	memset(&HAL_afe_handle_s,0,sizeof(HAL_afe_handle_t));
	HAL_afe_prfCfg(setParms_p);
	HAL_afe031Init();
	HAL_afeRxInit();
	HAL_afeTxInit();
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afeSet(HAL_afe_setCode_t setCode, void *setParms_s)
{
	return HAL_afe_set[setCode](setParms_s);
}

HAL_status_t HAL_afeGet(HAL_afe_getCode_t getCode, void *getParms_p)
{
	return HAL_afe_get[getCode](getParms_p);
}

HAL_status_t HAL_afeTxInit(void)
{
	HAL_afe_epwmCfg();
	HAL_I2C_cfg();
	HAL_afe_handle_s.boardRev = HAL_I2C_Get_BoardRev();
	HAL_cpuTimerCfg();
	EALLOW;
	if(HAL_afe_handle_s.boardRev == 0)
	{
		//FIX ME:configure gpio here
	}
	else
	{
		//FIX ME:configure gpio here
	}
	EDIS;
	IER |= 0x1;
	return HAL_STAT_SUCCESS;
}

HAL_status_t HAL_afeRxInit(void)
{
	HAL_afe_handle_s.updateGainFlag = 0;
	HAL_afe_handle_s.agcGainVal = 0;
	HAL_afe_adcCfg();
	HAL_I2C_cfg();
	HAL_afe_handle_s.boardRev = HAL_I2C_Get_BoardRev();
	IER |= 0x1;
	return HAL_STAT_SUCCESS;
}
