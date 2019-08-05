#ifndef _HAL_SPI_H
#define _HAL_SPI_H

/******************************************************************************
 * Definitions
 *****************************************************************************/
/* LSPCLK = SYSCLK/2/LSPCLK */
/* SPICLK = LSPCLK/(BRR+1) */
/* SYSCLK=100MHz, SPICLK=100/4/5=5MHz */
#ifdef F2803X
#define HAL_SPI_LSPCLK    0  //LSPCLK=SYSCLK
#else
#define HAL_SPI_LSPCLK    2  //LSPCLK=SYSCLK/4=100/4=25MHz for 100MHz
                             //120/4=30MHz for 120MHz, 150/4=37.5MHz for 150MHz
#endif

#if CPU_FRQ_100MHZ==1 || CPU_FRQ_90MHZ ==1
#define HAL_SPI_BRR       4  //SPICLK=LSPCLK/(BRR+1)=25/(4+1)=5MHz
#endif
#if CPU_FRQ_60MHZ==1
#define HAL_SPI_BRR       2  //SPICLK=60/4=15MHz
#endif
#if CPU_FRQ_120MHZ==1
#define HAL_SPI_BRR       5  //SPICLK=LSPCLK/(BRR+1)=30/(5+1)=5MHz
#endif
#if CPU_FRQ_150MHZ==1
#define HAL_SPI_BRR       5  //SPICLK=LSPCLK/(BRR+1)=37.5/(5+1)=6.25MHz
#endif
#define HAL_SPI_CCR_RST0  0x0F
#define HAL_SPI_CCR_RST1  0x8F
#define HAL_SPI_CTL_MSTR  0x06
#define HAL_SPI_FFTX      0xE040
#define HAL_SPI_FFRX      0x204F

/* PGA112 */
#define HAL_SPI_PGA_READ  0x6A
#define HAL_SPI_PGA_WRITE 0x2A
#define HAL_SPI_PGA_RWSHIFT   8
#define HAL_SPI_PGA_GAINSHIFT 4
#define HAL_SPI_PGA_CH0   0x0
#define HAL_SPI_PGA_CH1   0x1

/******************************************************************************
 * Externals
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/
void HAL_spi_cfg();
void HAL_spi_init();
void HAL_spi_xmt(Uint16 a);
void HAL_spi_fifoInit();
void HAL_spi_writeGain(Uint16 val); //->move to AFE

#if defined(F2803X) && defined(AFE031)
void HAL_spi_cfgWdLen(Uint16 val);
Uint16 HAL_spi_read(Uint16 a);
#endif

#endif
