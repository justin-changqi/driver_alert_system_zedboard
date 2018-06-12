/*
 * i2c.h
 *
 *  Created on: Jun 11, 2018
 *      Author: justin
 */

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include "xparameters.h"
#include "xiicps.h"
#include "xil_printf.h"

/************************** Constant Definitions ******************************/

#define IIC_DEVICE_ID		XPAR_XIICPS_0_DEVICE_ID

#define IIC_SLAVE_ADDR		0x08
#define IIC_SCLK_RATE		100000

#define TEST_BUFFER_SIZE	1

/**************************** Type Definitions ********************************/


/************************** Function Prototypes *******************************/
int initI2c();
int sendData();
int IicPsMasterPolledExample(u16 DeviceId);
/************************** Variable Definitions ******************************/

XIicPs Iic;		/**< Instance of the IIC Device */

/*
 * The following buffers are used in this example to send and receive data
 * with the IIC.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];    /**< Buffer for Transmitting Data */
u8 RecvBuffer[TEST_BUFFER_SIZE];    /**< Buffer for Receiving Data */

#endif /* SRC_I2C_H_ */
