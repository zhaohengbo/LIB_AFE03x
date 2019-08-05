#ifndef _HAL_AFE031_MCBSP_H
#define _HAL_AFE031_MCBSP_H

#include <typedefs.h>
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

#if CPU_FRQ_150MHZ == 1                                          // For 150 MHz SYSCLKOUT(default)
  #define CPU_SPD              150E6
#elif CPU_FRQ_120MHZ == 1	                                       // For 100 MHz SYSCLKOUT
  #define CPU_SPD              120E6
#else	                                       // For 100 MHz SYSCLKOUT
  #define CPU_SPD              100E6
#endif

#define MCBSP_SRG_FREQ       CPU_SPD/4                    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
/* For 120MHz CPU, CLKG=120/4/(1+1)=15MHz */
#define HAL_MCBSP_CLKGDV     0                                 // change to no divide: 22.5MHz 
#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)                  // # of CPU cycles in 2 SRG cycles-init delay
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+HAL_MCBSP_CLKGDV))) // # of CPU cycles in 2 CLKG cycles-init delay

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
void HAL_mcbsp_initGpio(void);
void HAL_mcbsp_init();
void HAL_mcbsp_cfg();
void HAL_mcbsp_xmt(Uint16 a);
Uint16 HAL_mcbsp_read(Uint16 reg);

void HAL_mcbsp_writeGain(Uint16 val);
Uint16 HAL_mcbsp_readGain(void);
void HAL_mcbsp_cfgWdLen(Uint16 len);
#endif
