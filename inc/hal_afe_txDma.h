#ifndef _HAL_AFE_TXDMA_H
#define _HAL_AFE_TXDMA_H

#include "hal_afe.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define HAL_AFE_TXDMA_NUMBUF   2     // # of TX DMA buffers (ping-pong)
#define HAL_AFE_TXDMA_BUFSIZE  1120  // TX DMA buffer size 

/******************************************************************************
 * Structures
 *****************************************************************************/
typedef struct
{
  volatile Uint32 *srcPtr_p;      // DMA source address (TX buffer)
#ifdef AFE031
  volatile Uint16 *dstPtr_p;      // DMA destination address (McBSPB DXR1 register)
#else
  volatile Uint32 *dstPtr_p[2];   // DMA destination address (EPWM1, EPWM2 registers)
#endif
  Uint16 burstSize;               // DMA burst size (Number of words in a burst - 1)
  Uint16 srcBurstStep;            // DMA source burst step
  Uint16 dstBurstStep;            // DMA destination burst step
  Uint16 xfrSize;                 // DMA transfer size (Number of bursts in a transfer - 1)
  Uint16 srcXfrStep;              // DMA source transfer step
  Uint16 dstXfrStep;              // DMA destination transfer step
  Uint16 srcWrapSize;             // DMA source wrap size
  Uint16 srcWrapStep;             // DMA source wrap step
  Uint16 dstWrapSize;             // DMA destination wrap size
  Uint16 dstWrapStep;             // DMA destination wrap step
  Uint16 dstBufIdx;               // DMA destination buffer index (Active buffer being filled)
  Uint16 dmaCnt;                  // DMA count
}HAL_afe_txDma_handle_t;

/******************************************************************************
 * Externals
 *****************************************************************************/
extern HAL_afe_txDma_handle_t HAL_afe_txDma_handle_s;
//extern volatile Uint16 DMABuf1[HAL_AFE_DMA_NUMBUF][HAL_AFE_DMA_BUFSIZE];

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_txDmaCfg(Uint16 size, Uint32 *dstBufAddr);
void HAL_afe_txDmaSetSrcAddr(volatile Uint32 *dstAddr);
void HAL_afe_txDmaSetXfrSize(Uint16 size);
void HAL_afe_txDmaStart(void);
void HAL_afe_txDmaStop();
void HAL_afe_txDmaReCfg(Uint16 size[2], Uint16 *dstBufAddr[2], Uint16 dstBufIdx);
void HAL_afe_txDmaClrFlag(void);

#endif
