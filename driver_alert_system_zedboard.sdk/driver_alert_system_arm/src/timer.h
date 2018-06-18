/*
 * timer.h
 *
 *  Created on: Jun 18, 2018
 *      Author: justin
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "xparameters.h"
#include "xtmrctr.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xil_printf.h"

#define TMRCTR_DEVICE_ID	XPAR_TMRCTR_0_DEVICE_ID
#define TMRCTR_INTERRUPT_ID	XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR

#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID

#define TIMER_CNTR_0	 0

#define INTC		XScuGic
#define INTC_HANDLER	XScuGic_InterruptHandler

//#define RESET_VALUE	 0x02FAF080
#define RESET_VALUE	 	0x0000C350

extern void SetGpioOut(u16 value, u8 mask);

/************************** Function Prototypes ******************************/
int TimerInit();
int TmrCtrIntrExample(INTC* IntcInstancePtr,
			XTmrCtr* InstancePtr,
			u16 DeviceId,
			u16 IntrId,
			u8 TmrCtrNumber);

static int TmrCtrSetupIntrSystem(INTC* IntcInstancePtr,
				XTmrCtr* InstancePtr,
				u16 DeviceId,
				u16 IntrId,
				u8 TmrCtrNumber);

void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber);

void TmrCtrDisableIntr(INTC* IntcInstancePtr, u16 IntrId);

/************************** Variable Definitions *****************************/
INTC InterruptController;  /* The instance of the Interrupt Controller */
XTmrCtr TimerCounterInst;   /* The instance of the Timer Counter */
/*
 * The following variables are shared between non-interrupt processing and
 * interrupt processing such that they must be global.
 */
int Timer_ms;

#endif /* SRC_TIMER_H_ */
