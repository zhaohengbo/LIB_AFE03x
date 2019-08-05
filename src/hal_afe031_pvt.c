#include "hal_afe031.h"
#include "F28x_Project.h"

/* RX Gain LUT */
UINT16 HAL_afe031_rxGainLut[] = { 0, 1, 2, 3, 6, 7, 10, 11, 14, 15 };
/* TX Gain LUT */
UINT16 HAL_afe031_txGainLut[] = { 0, 1, 2, 3 };

HAL_afe031_reg_t HAL_afe031_reg_s;

void HAL_afe031Init(void)
{
	memset(&HAL_afe031_reg_s,0,sizeof(HAL_afe031_reg_t));
	
    HAL_afe031_cfgGpio();

    HAL_spi_cfg();

    HAL_afe031_softReset();
	DELAY_US(2);

	HAL_afe031_biasEnable();

    HAL_afe031_bandSelect(HAL_afe_handle_s.prf.band);
    DELAY_US(2);

    HAL_afe031_clrAllInt();
    DELAY_US(2);
	
	HAL_afe031_cfgInt();
	DELAY_US(2);

    HAL_afe031_writeRxGain(0);
	HAL_afe031_writeTxGain(2);
    DELAY_US(2);
}

void HAL_afe031_cfgGpio(void)
{
	//HAL_afe_handle_s.boardRev
    //FIX ME:gpio setting
}

void HAL_afe031_writeRxGain_noWait(UINT16 gain)
{
	UINT16 cmd, data16;
	
	HAL_afe031_reg_s.gain_sel.bits.RXG = gain;

    cmd = (HAL_AFE031_CMD_WR << HAL_AFE031_CMD_RW_SHIFT) | HAL_AFE031_GAINSEL_REG;
    data16 = (cmd << HAL_AFE031_CMD_SHIFT) | (HAL_afe031_reg_s.gain_sel.bits.RXG & HAL_AFE031_DATA_MASK);
    /* For F28035, use SPI; all others, use McBSPA */

    HAL_spi_xmt(data16);
}

void HAL_afe031_writeRxGain(UINT16 gain)
{
	UINT16 rxGainSetting;
	rxGainSetting = HAL_afe031_rxGainLut[rxgain];
    HAL_afe031_reg_s.gain_sel.bits.RXG = rxGainSetting;
	HAL_afe031_regWrite(HAL_AFE031_GAINSEL_REG, HAL_afe031_reg_s.gain_sel.all);
}

void HAL_afe031_writeTxGain(UINT16 gain)
{
	UINT16 txGainSetting;
	txGainSetting = HAL_afe031_txGainLut[txgain];
    HAL_afe031_reg_s.gain_sel.bits.TXG = txGainSetting;
    HAL_afe031_regWrite(HAL_AFE031_GAINSEL_REG, HAL_afe031_reg_s.gain_sel.all);
}

void HAL_afe031_regWrite(UINT16 addr, UINT16 data)
{
    UINT16 cmd, data16;

    cmd = (HAL_AFE031_CMD_WR << HAL_AFE031_CMD_RW_SHIFT) | addr;
    data16 = (cmd << HAL_AFE031_CMD_SHIFT) | (data & HAL_AFE031_DATA_MASK);
    /* For F28035, use SPI; all others, use McBSPA */

    HAL_spi_xmt(data16);

    DELAY_US(1);
}

UINT16 HAL_afe031_regRead(UINT16 addr)
{
    UINT16 cmd;

    cmd = (HAL_AFE031_CMD_RD << HAL_AFE031_CMD_RW_SHIFT) | addr;
    cmd = (cmd << HAL_AFE031_CMD_SHIFT);
    /* For F28035, use SPI; all others, use McBSPA */

    return HAL_spi_read(cmd);
}

void HAL_afe031_clrAllInt(void)
{
    HAL_afe031_reg_s.control2.all = 0;
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, 0);
}

void HAL_afe031_clrInt(UINT16 flag)
{
    HAL_afe031_reg_s.control2.all &= (~flag);
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, HAL_afe031_reg_s.control2.all);
}

UINT16 HAL_afe031_readIntFlag(void)
{
    return HAL_afe031_regRead(HAL_AFE031_RESET_REG);
}

void HAL_afe031_cfgInt(void)
{
    HAL_afe031_reg_s.control2.bits.TFLAG_EN = 1;
    HAL_afe031_regWrite(HAL_AFE031_CTRL2_REG, HAL_afe031_reg_s.control2.all);
}

void HAL_afe031_cfgWdLen(UINT16 len)
{
    HAL_spi_cfgWdLen(len);
}
