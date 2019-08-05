#ifndef _HAL_AFE_PVT_H
#define _HAL_AFE_PVT_H

//#include <project.h>
#include <hal_afe_adc.h>
#include <hal_afe_dma.h>
#include <hal_afe_txDma.h>
#include <hal_afe_epwm.h>
#include <hal_afe_hrpwm.h>
#include <hal_spi.h>
#include <DSP28x_Project.h>
#if defined F2806X || F2803X || F28M35X
#include <SFO_V6.h>
#else
#include <SFO_V5.h>                 // SFO V5 library headerfile - required to use SFO library functions
#endif
#include <hal_afe.h>
#include <hal_afe_ecap.h>
#include <hal_afe_pwmCnv.h>
#include <hal_afe_dacCnv.h>
#include <hal_i2c.h>
#include <hal_xint.h>

#include <hal_afe031.h>
#include <hal_mcbsp.h>
/******************************************************************************
 * Definitions
 *****************************************************************************/
#if CPU_FRQ_150MHZ==1
#define CPU_RATE_MHZ     150
#endif
#if CPU_FRQ_120MHZ==1
#define CPU_RATE_MHZ     120
#endif
#if CPU_FRQ_105MHZ==1
#define CPU_RATE_MHZ     105
#endif
#if CPU_FRQ_100MHZ==1
#define CPU_RATE_MHZ     100
#endif
#if CPU_FRQ_90MHZ==1
#define CPU_RATE_MHZ     90
#endif

#if CPU_FRQ_60MHZ==1
#define CPU_RATE_MHZ     60
#endif

#define CPU_T1_10US      (CPU_RATE_MHZ * 10 - 1)

#define HAL_AFE_OPA_ON_DELAY  20L
#define HAL_AFE_OPA_OFF_DELAY 40L
//#define MEP_TEST
//#define HAL_AFE_USEADCINT

#define INTM_DISABLE      asm(" push ST1"); DINT;
#define INTM_RESTORE      asm(" pop ST1")


/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/
/* AFE handle */
typedef struct
{
#if defined(TEST_TX_VECTOR) || defined(TEST_LOOP_RXTX) || defined(TEST_TX) || defined(TEST_RX)
  volatile Uint16 *testBuf_p;            // Test buffer
  Uint16          bufIdx;                // Buffer index
  Uint16          rdIdx;                 // Buffer read index (for test)
  Uint16          wrIdx;                 // Buffer write index (for test)
  Uint16          testBufIdx;            // Test buffer index (for test)
  Uint32          txCnt;                 // TX count
#endif
  Uint16          txSize;                // 0 TX size
  Uint16          txActive;              // 1 TX active flag

  Uint16 updateGainFlag;     // 2 AGC gain update flag
  int16  agcGainVal;         // 3 AGC gain value

#ifdef F2803X
  /* Added for ADC int */
  volatile Uint16 *rxBufPtr_p[2];   // 4 5 6 7 RX buffer address (ping-pong buffer)
  volatile Uint16 *rxBufDat_p;      // 8 9
  Uint16 rxBufSize[2];              // 10 11 RX buffer size (Number of bursts in a transfer - 1)
  Uint16 rxBufIdx;                  // 12 RX buffer buffer index (next active buffer being filled)
  Uint16 adcCnt;                    // 13
  Uint16 rxBufCnt;                  // 14
  Uint16 adcIntCnt;                 // 15
  Uint16 activeBufIdx;           // 16 Active buffer index. Reload rxBufIdx @symbol done
  Uint16 activeBufSize;          // 17 Active buffer size. Reload rxBufSize[activeBufIdx] @symbol done
  
  /* For TX Buffers */
  volatile Uint16 *txBufReady_p;     // 18 19 TX buffer ready to be read
  volatile Uint16 *bufDat_p;         // 20 21 TX active buffer pointer
  Uint16 txBufIdx;                   // 22
  Uint16 txIntCnt;                   // 23
  Uint16 txBufSize;                  // 24
#endif  

  UINT16 timer01ShotFlag;    //  25 Timer 0 cfg flags
  HAL_cbFunc_t cb_p;		 // 26 27
  UINT32 cb_param;			 // 28 29
  Uint32 rxDmaTime;          // 30 31 RX DMA time (in 10us)
  Uint32 zcaTime;             // 32 33 Zero-crossing time (in 10us)
  Uint32 zcaLatency;          // 34 35 Zero-crossing latency (in CPU ticks)
  Uint32 zcaCap1;             // 36 37 Zero-crossing captured (in CPU ticks)
  Uint32 zcbTime;             // 38 39 Zero-crossing time (in 10us)
  Uint32 zcbLatency;          // 40 41 Zero-crossing latency (in CPU ticks)
  Uint32 zcbCap1;             // 42 43 Zero-crossing captured (in CPU ticks)

  BOARD_REV_t boardRev;		// 44 board revision ID

  HAL_afe_prfParms_t prf;   // 45 46 47 48

  Uint32 t0Prd;               // 50 51 T0 period in us (Q1)
}HAL_afe_handle_t;

/******************************************************************************
 * Externals
 *****************************************************************************/
extern HAL_afe_handle_t HAL_afe_handle_s;

/******************************************************************************
 * Prototypes
 *****************************************************************************/
HAL_status_t HAL_afe_init(void);
HAL_status_t HAL_afe_cfg(void *setParms);

HAL_status_t HAL_afe_rxCfg(void *setParms);
HAL_status_t HAL_afe_rxStart(void *setParms);
HAL_status_t HAL_afe_rxStop(void *setParms);
HAL_status_t HAL_afe_rxReCfg(void *setParms);
HAL_status_t HAL_afe_setGain(void *setParms);
HAL_status_t HAL_afe_updateGain(void *setParms);
HAL_status_t HAL_afe_cancelGain(void *setParms);
HAL_status_t HAL_afe_adcOffsetAdj(void *setParms);
HAL_status_t HAL_afe_txDmaSize(void *setParms);
HAL_status_t HAL_afe_txDmaAddr(void *setParms);
HAL_status_t HAL_cpuTimer1CfgStart(void);
Uint32 HAL_cpuTimer1GetCount(void);
HAL_status_t HAL_cpuTimer0TimeoutCfg(void *setParms);
HAL_status_t HAL_cpuTimer0Start();
HAL_status_t HAL_cpuTimer0Stop();

HAL_status_t HAL_cpuTimerCfg();

HAL_status_t HAL_afe_txCfg(void *setParms);
HAL_status_t HAL_afe_txStart(void *setParms);
HAL_status_t HAL_afe_txStop(void *setParms);
HAL_status_t HAL_afe_txReCfg(void *setParms);

HAL_status_t HAL_afe_rxDmaTime(void *getParms);
HAL_status_t HAL_afe_zcTime(void *getParms);
HAL_status_t HAL_afe_rxDmaIdx(void *getParms);
HAL_status_t HAL_afe_rndNum(void *getParms);

HAL_status_t HAL_afe_prfCfg(void *setParms);

#endif

