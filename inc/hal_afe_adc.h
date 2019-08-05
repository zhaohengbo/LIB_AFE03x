#ifndef _HAL_AFE_ADC_H
#define _HAL_AFE_ADC_H

/******************************************************************************
 * Definitions
 *****************************************************************************/
#if defined F2806X || F28M35X
/* For Octave (Piccolo-like), ADC S/H is much simpler.
 * ADC_SH Window = t_SYSCLK * (ACQ_PS + 1) */
#define HAL_AFE_ADC_ACQ_PS   8 // 9 cycles or 100ns 
#else
/* HISPCLK */
#define HAL_AFE_ADC_MODCLK 0x5 // HISPCLK = SYSCLKOUT/2*ADC_MODCLK
                               // 100/(2*5) = 10.0MHz (for 100MHz); 
                               // 120/(2*5) = 12.0MHz (for 120MHz); 
                               // 150/(2*5) = 15MHz (for 150MHz)

/* ADC clock */
/* ADC_SHCLK = HISPCLK/2/ADC_CLKPS/(ADCPS+1)/(ADC_ACQ_PS+1)
 *           = 12MHz/2/3/1/(3+1+1) = 400kHz
 */

#if CPU_FRQ_100MHZ==1
/* ADCTRL1 */
#define HAL_AFE_ADC_ACQ_PS   1  // ADC_SH=ADCCLK/(1+1), MSPS=ADCCLK/(1+1+1)=3.3MHz
#define HAL_AFE_ADC_CPS      0  // ADCCLK=f_CLK/1=10MHz
/* ADCTRL3 */
#define HAL_AFE_ADC_CLKPS    0  // f_CLK=HISPCLK/1/ADC_CLKPS=10MHz
#endif

#if CPU_FRQ_120MHZ==1
/* ADCTRL1 */
#define HAL_AFE_ADC_ACQ_PS   1  // ADC_SH=ADCCLK/(1+1), MSPS=ADCCLK/(1+1+1)=4MHz
#define HAL_AFE_ADC_CPS      0  // ADCCLK=f_CLK/1=12MHz
/* ADCTRL3 */
#define HAL_AFE_ADC_CLKPS    0  // f_CLK=HISPCLK/1/ADC_CLKPS=12MHz
#endif

#if CPU_FRQ_150MHZ==1
/* ADCTRL1 */
#define HAL_AFE_ADC_ACQ_PS   2  // ADC_SH=ADCCLK/(2+1), MSPS=ADCCLK/(2+1+1)=5MSPS=3.75MHz
#define HAL_AFE_ADC_CPS      0  // ADCCLK=f_CLK/1=15MHz
/* ADCTRL3 */
#define HAL_AFE_ADC_CLKPS    0  // f_CLK=HISPCLK/1/ADC_CLKPS=15MHz
#endif
#endif //!ifdef F2806X

/* ADC input 0->3V mapped to 12-bits (0->4096) */
#define HAL_AFE_ADC_OFFSET   -2048

/******************************************************************************
 * Externals
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_adcCfg();
void HAL_afe_adcStart();
void HAL_afe_adcStop();
interrupt void HAL_afe_adcint_isr(void);     // ADC

#endif
