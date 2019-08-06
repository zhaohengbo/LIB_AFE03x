#include "F28x_Project.h"
#include "hal_spi.h"

void HAL_spi_cfg(void)
{
	InitAFESpiGpio();
	HAL_spi_fifoInit();
	HAL_spi_init();
}

void InitAFESpiGpio(void)
{
	EALLOW;

	//FIX ME:gpio setting here

	EDIS;
}

void HAL_spi_init(void)
{
	EALLOW;
	ClkCfgRegs.LOSPCP.all = HAL_SPI_LSPCLK;
	EDIS;

	SpiaRegs.SPICCR.bit.SPISWRESET = 0;
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
	SpiaRegs.SPICCR.bit.SPILBK = 0;
	SpiaRegs.SPICCR.bit.SPICHAR = 15; //16-bit character
	SpiaRegs.SPICCR.bit.HS_MODE = 0x1;
	SpiaRegs.SPICTL.bit.SPIINTENA = 0; // Interrupt disable
	SpiaRegs.SPICTL.bit.TALK = 1; // Transmit enable
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1; //Master
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0; //Normal phase, depending on SPICCR.6 (CLOCK_POLARITY)
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0; //Overrun interrupt disable

	SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = HAL_SPI_BRR;

	SpiaRegs.SPIPRI.bit.FREE = 1;  // Set so breakpoints don't disturb xmission

	SpiaRegs.SPICCR.bit.SPISWRESET = 1; // Ready to transmit
}

void HAL_spi_xmt(Uint16 a)
{
	SpiaRegs.SPITXBUF = a;
	/* Need to check out */
	DELAY_US(1);
}

void HAL_spi_fifoInit(void)
{
	SpiaRegs.SPIFFTX.all = HAL_SPI_FFTX;
	SpiaRegs.SPIFFRX.all = HAL_SPI_FFRX;
	SpiaRegs.SPIFFCT.all = 0x0;
}

void HAL_spi_writeGain(Uint16 val)
{
	Uint16 regVal;

	regVal = (HAL_SPI_PGA_WRITE << HAL_SPI_PGA_RWSHIFT)
			| ((val & 0xF) << HAL_SPI_PGA_GAINSHIFT) |
			HAL_SPI_PGA_CH1;
	HAL_spi_xmt(regVal);
}

void HAL_spi_cfgWdLen(Uint16 val)
{
	SpiaRegs.SPICCR.bit.SPICHAR = val - 1;
}

Uint16 HAL_spi_read(Uint16 a)
{
	SpiaRegs.SPITXBUF = a;
	/* Need to check out */
	DELAY_US(2);
	/* Write a dummy */
	SpiaRegs.SPITXBUF = 0xFFFF;
	DELAY_US(2);

	return SpiaRegs.SPIDAT;
}
