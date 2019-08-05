#ifndef _HAL_AFE_PWMCNV_H
#define _HAL_AFE_PWMCNV_H

#include <typedefs.h>

/******************************************************************************
 * Definitions
 *****************************************************************************/
#ifdef F2806X
#define HAL_afe_pwmCnv(in_p, mep, prd, len, txLev, clip, out_p) \
        HAL_afe_pwmCnvac(in_p, mep, prd, len, txLev, clip, out_p)
#else
#define HAL_afe_pwmCnv(in_p, mep, prd, len, txLev, clip, out_p) \
        HAL_afe_pwmCnva(in_p, mep, prd, len, txLev, clip, out_p)
#endif
/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/

/******************************************************************************
 * Externals
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_pwmCnvc(int16 *in_p, Uint16 mep, Uint16 prd, Uint16 len, int16 txLev, Uint16 clip, int16 *out_p);
void HAL_afe_pwmCnva(int16 *in_p, Uint16 mep, Uint16 prd, Uint16 len, int16 txLev, Uint16 clip, int16 *out_p);
void HAL_afe_pwmCnvac(int16 *in_p, Uint16 mep, Uint16 prd, Uint16 len, int16 txLev, Uint16 clip, int16 *out_p);

#endif

