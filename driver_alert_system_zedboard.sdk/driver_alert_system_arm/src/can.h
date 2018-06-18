/*
 * can.h
 *
 *  Created on: Jun 18, 2018
 *      Author: justin
 */

#ifndef SRC_CAN_H_
#define SRC_CAN_H_

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

//CAN Include
#include "xcanps.h"


//parameters for CAN BUS
#define TEST_BTR_SYNCJUMPWIDTH	3
#define TEST_BTR_SECOND_TIMESEGMENT	2
#define TEST_BTR_FIRST_TIMESEGMENT	15
#define TEST_BRPR_BAUD_PRESCALAR	29
#define CAN_DEVICE_ID_0	XPAR_XCANPS_0_DEVICE_ID

#define XCANPS_MAX_FRAME_SIZE_IN_WORDS (XCANPS_MAX_FRAME_SIZE / sizeof(u32))


//CAN Functions
int CanInit();
void CANsendData(u8 data);
void CANgetData();
static int SendFrame(XCanPs *InstancePtr, u32 *TxFrame);
static int RecvFrame(XCanPs *InstancePtr, u32 *RxFrame);

//Buffer
static u32 TxFrame_0[XCANPS_MAX_FRAME_SIZE_IN_WORDS];
static u32 RxFrame_0[XCANPS_MAX_FRAME_SIZE_IN_WORDS];

/* Driver instance */
static XCanPs Can_0;

u32 can_id_;
u32 can_dlc_tx_;
u32 can_dlc_rx_;

#endif /* SRC_CAN_H_ */
