#ifndef _HAL_AFE_EPWM_H
#define _HAL_AFE_EPWM_H

/******************************************************************************
 * Definitions
 *****************************************************************************/

/******************************************************************************
 * Data Structures
 *****************************************************************************/
/* AFE EPWM handle */
typedef struct
{
  Uint16          mepx2;                 // MEP scale factor (2x due to symmetric PWM)
  Uint16          prd;                   // EPWM period
  Uint16          socPrd;                // SOC period
}HAL_afe_epwm_handle_t;

/******************************************************************************
 * Externals
 *****************************************************************************/
extern HAL_afe_epwm_handle_t HAL_afe_epwm_handle_s;
//extern volatile Uint16 TXBuf1[HAL_AFE_TX_NUMBUF][HAL_AFE_TX_BUFSIZE];

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_epwmCfg();
void HAL_afe_epwm_setCmpAll(int16 val, int16 qval);
#endif
