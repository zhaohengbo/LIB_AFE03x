#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#include <sys_cfg.h>

/******************************************************************************
 * Definitions
 *****************************************************************************/
/* LSPCLK = SYSCLK/2/LSPCLK */
/* SPICLK = LSPCLK/(BRR+1) */
/* SYSCLK=100MHz, SPICLK=100/4/5=5MHz */
/* SYSCLK=150MHzz */
#define HAL_I2C_PSC_150MHZ      (14)
#define HAL_I2C_PSC_120MHZ      (11)
#define HAL_I2C_PSC_100MHZ      (9)
#define HAL_I2C_PSC_90MHZ       (8)
#define HAL_I2C_PSC_60MHZ       (5)

// suppotred ATMEL EEPROM parts
//
#define HAL_I2C_ATMEL_PART_AT24C1024B         0
#define HAL_I2C_ATMEL_PART_AT24C512B          1

// ATMEL AT24C1024B
// ATMEL AT24C512B

// I2C module Clock is 10 Mhz, down converted to 400KHz or 1MHz
// for 1.8V device, clock is 400KHz
// for 5v,2.5V, clock is 1 MHz
#define HAL_I2C_500_ICCH        (5)
#define HAL_I2C_500_ICCL        (5)

#ifdef F2806X
  #define HAL_I2C_TX_FIFO_SIZE        (4)
  #define HAL_I2C_RX_FIFO_SIZE        (4)
#else
  #define HAL_I2C_TX_FIFO_SIZE        (16)
  #define HAL_I2C_RX_FIFO_SIZE        (16)
#endif

// ATMEL address pattern
#define HAL_I2C_ATMEL_ADDRESS_PREFIX    (0x50)

#define HAL_I2C_ST_SUCCESS              0   
#define HAL_I2C_ST_TX_FIFO_NO_EMPTY     1
#define HAL_I2C_ST_TX_ERR_LEN           2
#define HAL_I2C_ST_RX_ERR_LEN           3
#define HAL_I2C_ST_ERR_BB               4
#define HAL_I2C_ST_ERR_RSFULL           5
#define HAL_I2C_ST_ERR_XSMT             6
#define HAL_I2C_ST_ERR_STOP             7
#define HAL_I2C_ST_TX_FIFO_FULL         8
#define HAL_I2C_ST_WRITE_READ_FAIL      9
#define HAL_I2C_ST_NACK                 10
#define HAL_I2C_ST_NO_EEPROM            11

#define HAL_I2C_FIFO_SIZE                   (16)

// I2C command
#define HAL_I2C_STT_STP_TRX_RM_MASK                         (0x2a80)
#define HAL_I2C_ATMEL_PAGE_WRITE_MODE_WITH_STOP             (0x6E20)
#define HAL_I2C_ATMEL_PAGE_WRITE_MODE_NO_STOP               (0x2620)
#define HAL_I2C_ATMEL_PAGE_READ_MODE_WITH_STOP              (0x2C20)


#define HAL_I2C_ATMEL_RM_ZERO_LEN_START                     (0x24A0)
#define HAL_I2C_ATMEL_RM_ZERO_LEN_STOP                      (0x0CA0)

// ATMEL EEPROM page size
#define HAL_I2C_AT24C1024B_PAGE_SIZE                        (256)
#define HAL_I2C_AT24C512B_PAGE_SIZE                         (128)

// ATMEL EEPROM capacity (128K)
#define HAL_I2C_AT24C1024B_CAPACITY                         (0x20000)
#define HAL_I2C_AT24C512B_CAPACITY                          (0x10000)

// A2A1 adderess
#define HAL_I2C_AT24C1024B_CHIP_1               (0x01)
#define HAL_I2C_AT24C1024B_CHIP_2               (0x02)

// A2A1A0 address
#define HAL_I2C_AT24C512B_CHIP_1                (0x01)
#define HAL_I2C_AT24C512B_CHIP_2                (0x02)

#define HAL_I2C_AT24C1024B_WRITE_CYCLE_TIME     (5000)
#define HAL_I2C_DELAY_CHECK_NACK                (100)

// Sys CFG start address
#define EEPROM_SYS_CFG_START_ADDRESS            (0)

#define EEPROM_FIRMWARE_START_ADDRESS           (1024)

typedef struct __hal_i2c_hnd
{
  BOARD_REV_t boardRev;
  Uint16 page_size;   //EEPROM page size
  Uint16 complete_probe;
  Uint16 dev_part;
  
  // debug cnts
  Uint16 err_pkt_len;
  Uint16 err_stop;
  Uint16 err_bb;
  Uint16 err_tx_fifo_full;
  Uint16 err_tx_fifo_not_empty;
  Uint16 err_xsmt;
  Uint16 err_nack;

  Uint16 max_wait;
  Uint32 test_addr;

} HAL_I2C_HND_s;

#define FLASH_MAX_SEGMENTS          8
typedef struct __flash_seg
{
  Uint32 start_address;
  Uint32 len;
} FLASH_SEG_s;

typedef struct __firmware_header
{
  Uint16 number_seg;
  FLASH_SEG_s seg[FLASH_MAX_SEGMENTS];

} FIRMWARE_HEADER_s;
/******************************************************************************
 * Externals
 *****************************************************************************/

/******************************************************************************
 * Prototypes
 *****************************************************************************/

void HAL_initI2CGpio(void);
void HAL_I2C_Reset_TX_FIFO(void);
void HAL_I2C_Reset_RX_FIFO(void);
void HAL_I2C_init(void);


void HAL_I2C_Set_Device_Addr(Uint16 devID,Uint32 addr);
Uint16 HAL_I2C_Write_Memory_Addr(Uint32 start_addr);
Uint16 HAL_I2C_Wait_TX_FIFO_Not_Full(void);
Uint16 HAL_I2C_Wait_TX_FIFO_Empty(void);
Uint16 HAL_I2C_Wait_RX_FIFO_Not_Empty(void);
void HAL_I2C_Wait_STOP_Complete(void);
Uint16 HAL_I2C_Check_TX_Status(void);
Uint16 HAL_I2C_Check_START_Status(void);

void HAL_I2C_ACK_POLLING(Uint16 devID);

void HAL_I2C_cfg();
Uint16 HAL_I2C_Write_DataBuf(Uint16 devID,Uint32 start_addr,Uint16 len,Uint16 *pbuf,Uint16 offset);
Uint16 HAL_I2C_Read_DataBuf(Uint16 devID,Uint32 start_addr,Uint16 len,Uint16 *pbuf,Uint16 offset);

Uint16 HAL_I2C_Self_Test(void);

void HAL_I2C_Probe_Board(void);
Uint16 HAL_I2C_Probe_Atmel1024(void);
BOARD_REV_t HAL_I2C_Get_BoardRev(void);

Uint16 HAL_I2C_Get_PageSize(void);
#endif

