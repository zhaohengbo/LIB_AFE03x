#include "F28x_Project.h"
#include "hal_i2c.h"

/*
 * I have to say that hal_i2c doesn't have any use.
 * It just provide an back-up storge.
 * And the only thing related to PLC SW is the BoardRev number.
 * In some verson of PLC SW, this even doesn't exist.
 */

void HAL_I2C_init(void)
{
	
}

BOARD_REV_t HAL_I2C_Get_BoardRev(void)
{
	return 0;
}