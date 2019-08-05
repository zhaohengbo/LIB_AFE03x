#ifndef _HAL_AFE_DMA_H
#define _HAL_AFE_DMA_H

#include "hal_afe.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define HAL_AFE_DMA_NUMBUF   2    // # of RX DMA buffers
#define HAL_AFE_DMA_BUFSIZE  560  // RX DMA buffer size

/******************************************************************************
 * Data Structures
 *****************************************************************************/
/* AFE RX DMA */
typedef struct
{
  volatile Uint16 *srcPtr_p;      // DMA source address (ADC)
  volatile Uint16 *dstPtr_p[2];   // DMA destination address (ping-pong buffer)
  Uint16 burstSize;               // DMA burst size (Number of words in a burst - 1)
  Uint16 srcBurstStep;            // DMA source burst step
  Uint16 dstBurstStep;            // DMA destination burst step
  Uint16 xfrSize[2];              // DMA transfer size (Number of bursts in a transfer - 1)
  Uint16 srcXfrStep;              // DMA source transfer step
  Uint16 dstXfrStep;              // DMA destination transfer step
  Uint16 srcWrapSize;             // DMA source wrap size
  Uint16 srcWrapStep;             // DMA source wrap step
  Uint16 dstWrapSize;             // DMA destination wrap size
  Uint16 dstWrapStep;             // DMA destination wrap step
  Uint16 dstBufIdx;               // DMA destination buffer index (Active buffer being filled)
  Uint16 dmaCnt;                  // DMA count
}HAL_afe_dma_handle_t;

/******************************************************************************
 * Externals
 *****************************************************************************/
extern HAL_afe_dma_handle_t HAL_afe_dma_handle_s;
extern volatile Uint16 DMABuf1[HAL_AFE_DMA_NUMBUF][HAL_AFE_DMA_BUFSIZE];

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_afe_dmaCfg(Uint16 size[2], Uint16 *dstBufAddr[2]);
void HAL_afe_dmaSetDstAddr(volatile Uint16 *dstAddr);
void HAL_afe_dmaStart(Uint16 size[2], Uint16 *dstBufAddr[2], Uint16 dstBufIdx);
void HAL_afe_dmaStop();
void HAL_afe_dmaReCfg(Uint16 size[2], Uint16 *dstBufAddr[2], Uint16 dstBufIdx);

#endif
