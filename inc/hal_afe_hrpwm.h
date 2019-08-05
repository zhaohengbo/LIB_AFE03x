#ifndef _HAL_AFE_HRPWM_H
#define _HAL_AFE_HRPWM_H

#if defined F2806X || F2803X || F28M35X
#include "SFO_V6.h"
#else
#include "SFO_V5.h"
#endif
/******************************************************************************
 * Definitions
 *****************************************************************************/

/******************************************************************************
 * Structures
 *****************************************************************************/

/******************************************************************************
 * Externals
 *****************************************************************************/
#if defined F2806X || F2803X || F28M35X
extern Uint16 MEP_ScaleFactor;
#else
extern Uint16 MEP_ScaleFactor[PWM_CH]; // Global array used by the SFO library
#endif
/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_hrPwmInit();
void HAL_afe_hrPwmCfg();
#if defined F2806X || F28M35X
#else
Uint16 HAL_afe_hrPwmEnMepUpdate(Uint16 nMepChannel);
Uint16 HAL_afe_hrPwmDisMepUpdate(Uint16 nMepChannel);
void HAL_afe_hrPwm_setCmpAll(int16 val/*, int16 qval*/);
void HAL_afe_setHrPwmCmpa( int32 val, Uint16 MEP_2);
#endif

#endif
