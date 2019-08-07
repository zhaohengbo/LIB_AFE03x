#ifndef _HAL_AFE_H
#define _HAL_AFE_H

#include <typedefs.h>

/******************************************************************************
 * Definitions
 *****************************************************************************/
/* Sampling and PWM frequencies */
#define HAL_AFE_KHZ_250    250
#define HAL_AFE_KHZ_400    400
#define HAL_AFE_KHZ_500    500
#define HAL_AFE_KHZ_800    800
#define HAL_AFE_KHZ_1000   1000
#define HAL_AFE_KHZ_1200   1200
#define HAL_AFE_KHZ_1500   1500
#define HAL_AFE_KHZ_2000   2000

/* Timer cfg */
#define HAL_AFE_TIMER_INT_ENABLE     0x1
#define HAL_AFE_TIMER_INT_DISABLE    0x0
#define HAL_AFE_TIMER_1_SHOT         0x2
#define HAL_AFE_TIMER_1_SHOT_SHIFT     1

/* HAL status */
typedef enum
{
  HAL_STAT_SUCCESS = 0,     // HAL success
  HAL_STAT_FAILURE = 1      // HAL failure
}HAL_status_t;

/* HAL_AFE set code */
typedef enum
{
  AFE_TX_CFG     = 0,        // TX configure
  AFE_TX_START   = 1,        // TX start
  AFE_TX_STOP    = 2,        // TX stop
  AFE_TX_RECFG   = 3,        // Reconfigure TX
  AFE_TX_DMASIZE = 4,        // Set TX DMA size
  AFE_TX_DMAADDR = 5,        // Set TX DMA address
  AFE_TX_T0CFG   = 6,        // Configure CPU timer 0
  AFE_TX_T0START = 7,        // Start CPU timer 0
  AFE_TX_T0STOP  = 8,        // Stop CPU timer 0

  AFE_RX_START   = 9,        // RX start
  AFE_RX_STOP    = 10,       // RX stop
  AFE_RX_RECFG   = 11,       // RX reconfigure
  AFE_RX_SETGAIN = 12,       // Set AGC gain
  AFE_RX_UPDATEGAIN = 13,    // Update AGC gain
  AFE_RX_CANCEL_GAIN = 14,   // Cancel gain update

#ifndef F2803X
  AFE_SEL_ECAP    = 15,
  AFE_SEL_XINT1   = 16,
  AFE_SEL_XINT2   = 17,

  NUM_AFE_SETPARMS = 18
#else
  NUM_AFE_SETPARMS = 15
#endif
}HAL_afe_setCode_t;

typedef enum
{
   HAL_AFE_ECAP1 = 1,
   HAL_AFE_ECAP2 = 2,
   HAL_AFE_ECAP3 = 3,
   HAL_AFE_ECAP4 = 4,
   HAL_AFE_ECAP5 = 5,
   HAL_AFE_ECAP6 = 6
}HAL_afe_ecapSel_t;

/* Callback functions */
typedef void (*HAL_cbFunc_t)(UINT32);

/* HAL_AFE get code */
typedef enum
{
  AFE_RX_DMATIME   = 0,        // RX DMA time
  AFE_ZCTIME       = 1,        // ZC time
  AFE_RX_DMAIDX    = 2,        // RX DMA index
  AFE_RND_NUM       = 3,        // random number generator
  NUM_AFE_GETPARMS = 4
}HAL_afe_getCode_t;

/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/
/* AFE RX set parameters */
typedef struct
{
  UINT16 size[2];            // 0 1 Sizes of RX ping-pong buffers
  UINT16 *dstBufAddr[2];     // 2 3 4 5 DMA desination ping-pong buffer addresses
  UINT16 dstBufIdx;          // 6 7 Destination buffer index. Always point to the readable buffer
}HAL_afe_rxSetParms_t;

/* AFE ADC offset adjust parameters */
typedef struct
{
  UINT16 size;               // Size of data buffer needs offset adjustment
  SINT16 *data_p;             // Pointer to the data buffer
}HAL_afe_adcAdjParms_t;

/* AFE TX set parameters */
typedef struct
{
  SINT16 *txBuf_p;            // 0 1 Pointer to the TX buffer
  UINT16 txSize;             // 2 3 Size of TX buffer
  UINT32 t0PrdInUs;          // 4 5 CPU timer 0 period (in us)
  UINT16 t0Flags;            // 6 7 bit 0: CPU timer 0 interrupt enabled (1) or disabled (0)
                             // bit 1: 1 shot = 1, 0 = continuous
                             // This is enabled for txTime timeout, but disabled for TX DMA
  HAL_cbFunc_t cb_p;
  UINT32 cb_param;
}HAL_afe_txSetParms_t;

typedef struct
{
  UINT32 zcaTime;
  UINT32 zcbTime;
}HAL_afe_zcTime_t;

/* AFE Profile */
typedef struct
{
  UINT16 rx_fs_kHz;
  UINT16 tx_fs_kHz;
  UINT16 tx_pwm_kHz;
  UINT16 band;         //0-A; 1-BCD
}HAL_afe_prfParms_t;
/******************************************************************************
 * Externals
 *****************************************************************************/
extern HAL_afe_txSetParms_t HAL_afe_txSetParms_s;
/******************************************************************************
 * Prototypes
 *****************************************************************************/
HAL_status_t HAL_afeInit(HAL_afe_prfParms_t *setParms_p);
HAL_status_t HAL_afeSet(HAL_afe_setCode_t setCode, void *setParms_s);
HAL_status_t HAL_afeGet(HAL_afe_getCode_t getCode, void *getParms_p);
HAL_status_t HAL_afeTxInit(void);
HAL_status_t HAL_afeRxInit(void);
HAL_status_t HAL_afeRxDmaCh1IntFunc(void);
HAL_status_t HAL_afeTxDmaCh2IntFunc(void);
HAL_status_t HAL_cpuTint0Func(void);
HAL_status_t HAL_afeEcap1IntFunc(void);
HAL_status_t HAL_afeEcap3IntFunc(void);
HAL_status_t HAL_afeEcap4IntFunc(void);
HAL_status_t HAL_haltLPM(void);
HAL_status_t HAL_xint1Func(void);
HAL_status_t HAL_xint2Func(void);

//HAL_status_t HAL_afe031Init(void);
HAL_status_t HAL_afeDacCnv(int16 *in_p, UINT16 len, int16 lev, UINT16 clip, int16 *out_p);
HAL_status_t HAL_afeDacCnvInP(int16 *data_p, Uint16 len);

const char  *HAL_getLibVersion(void);

#endif

