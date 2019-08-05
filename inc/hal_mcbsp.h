#ifndef _HAL_MCBSP_H
#define _HAL_MCBSP_H

#ifndef AFE031
/******************************************************************************
 * Definitions
 *****************************************************************************/

//---------------------------------------------------------------------------
// MCBSP_INIT_DELAY determines the amount of CPU cycles in the 2 sample rate
// generator (SRG) cycles required for the Mcbsp initialization routine.
// MCBSP_CLKG_DELAY determines the amount of CPU cycles in the 2 clock
// generator (CLKG) cycles required for the Mcbsp initialization routine.
// For the functions defined in Mcbsp.c, MCBSP_INIT_DELAY and MCBSP_CLKG_DELAY
// are based off of either a 150 MHz SYSCLKOUT (default) or a 100 MHz SYSCLKOUT.
//
// CPU_FRQ_100MHZ and CPU_FRQ_150MHZ are defined in DSP2833x_Examples.h
//---------------------------------------------------------------------------

#if CPU_CLOCK_150                                          // For 150 MHz SYSCLKOUT(default)
  #define CPU_SPD              150E6
  #define MCBSP_SRG_FREQ       CPU_SPD/4                    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
#else	                                       // For 100 MHz SYSCLKOUT
  #define CPU_SPD              100E6
  #define MCBSP_SRG_FREQ       CPU_SPD/4                    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
#endif

#define CLKGDV_VAL           1
#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)                  // # of CPU cycles in 2 SRG cycles-init delay
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+CLKGDV_VAL))) // # of CPU cycles in 2 CLKG cycles-init delay

/* LSPCLK = SYSCLK/2/LSPCLK */
/* SPICLK = LSPCLK/(BRR+1) */
/* SYSCLK=100MHz, SPICLK=100/4/5=5MHz */
//#define HAL_SPI_LSPCLK    2  //LSPCLK=SYSCLK/4=100/4=25MHz
#define HAL_MCBSP_BRR       4  //SPICLK=LSPCLK/(BRR+1)=25/(4+1)=5MHz

/* PGA112 */
#define HAL_MCBSP_PGA_READ  			0x6A
#define HAL_MCBSP_PGA_WRITE 			0x2A
#define HAL_MCBSP_PGA_RWSHIFT   		8
#define HAL_MCBSP_PGA_GAINSHIFT	 		4
#define HAL_MCBSP_PGA_CH0   			0x0
#define HAL_MCBSP_PGA_CH1   			0x1

/******************************************************************************
 * Externals
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void InitMcbspbGpio(void);
void HAL_mcbsp_init();
void HAL_mcbsp_cfg();
void HAL_MCBSP_B_xmt(Uint16 a);
void HAL_mcbsp_writeGain(Uint16 val);
Uint16 HAL_mcbsp_readGain(void);

#endif //AFE031

#endif
