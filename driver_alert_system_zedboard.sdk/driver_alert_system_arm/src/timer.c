/*
 * timer.c
 *
 *  Created on: Jun 18, 2018
 *      Author: justin
 */

#include "timer.h"

int TimerInit()
{

	int Status;
	Status = TmrCtrIntrExample(&InterruptController,
				  	  	  	   &TimerCounterInst,
							   TMRCTR_DEVICE_ID,
							   TMRCTR_INTERRUPT_ID,
							   TIMER_CNTR_0);
	return Status;

}

int TmrCtrIntrExample(INTC* IntcInstancePtr,
			XTmrCtr* TmrCtrInstancePtr,
			u16 DeviceId,
			u16 IntrId,
			u8 TmrCtrNumber)
{
	int Status;
	int LastTimerExpired = 0;

	Status = XTmrCtr_Initialize(TmrCtrInstancePtr, DeviceId);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XTmrCtr_SelfTest(TmrCtrInstancePtr, TmrCtrNumber);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = TmrCtrSetupIntrSystem(IntcInstancePtr,
					TmrCtrInstancePtr,
					DeviceId,
					IntrId,
					TmrCtrNumber);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XTmrCtr_SetHandler(TmrCtrInstancePtr, TimerCounterHandler,
					   TmrCtrInstancePtr);

	XTmrCtr_SetOptions(TmrCtrInstancePtr, TmrCtrNumber,
				XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);

	XTmrCtr_SetResetValue(TmrCtrInstancePtr, TmrCtrNumber, ~RESET_VALUE);

	XTmrCtr_Start(TmrCtrInstancePtr, TmrCtrNumber);

	return XST_SUCCESS;
}

void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber)
{
	Timer_ms++;
}

static int TmrCtrSetupIntrSystem(INTC* IntcInstancePtr,
				 XTmrCtr* TmrCtrInstancePtr,
				 u16 DeviceId,
				 u16 IntrId,
				 u8 TmrCtrNumber)
{
	 int Status;
	XScuGic_Config *IntcConfig;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XScuGic_SetPriorityTriggerType(IntcInstancePtr, IntrId,
					0xA0, 0x3);

	/*
	 * Connect the interrupt handler that will be called when an
	 * interrupt occurs for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr, IntrId,
				 (Xil_ExceptionHandler)XTmrCtr_InterruptHandler,
				 TmrCtrInstancePtr);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Enable the interrupt for the Timer device.
	 */
	XScuGic_Enable(IntcInstancePtr, IntrId);

	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
					(Xil_ExceptionHandler)
					INTC_HANDLER,
					IntcInstancePtr);

	/*
	 * Enable non-critical exceptions.
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}


/******************************************************************************/
/**
*
* This function disables the interrupts for the Timer.
*
* @param	IntcInstancePtr is a reference to the Interrupt Controller
*		driver Instance.
* @param	IntrId is XPAR_<INTC_instance>_<Timer_instance>_VEC_ID
*		value from xparameters.h.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void TmrCtrDisableIntr(INTC* IntcInstancePtr, u16 IntrId)
{

	XScuGic_Disable(IntcInstancePtr, IntrId);
	XScuGic_Disconnect(IntcInstancePtr, IntrId);
	return;
}

