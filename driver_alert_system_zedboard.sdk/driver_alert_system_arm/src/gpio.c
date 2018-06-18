#include "gpio.h"



int Gpio_init()
{
	INTC *IntcInstancePtr = &Intc;
	XGpio *InstancePtr = &Gpio;
	u16 DeviceId = GPIO_DEVICE_ID;
	u16 IntrId = INTC_GPIO_INTERRUPT_ID;
	u16 IntrMask = BUTTON_CHANNEL;
	gpio_count = 0;
	int Status;

	Status = XGpio_Initialize(InstancePtr, DeviceId);
	if (Status != XST_SUCCESS) {
			return XST_FAILURE;
	}
	Status = GpioSetupIntrSystem(IntcInstancePtr,
								 InstancePtr,
								 DeviceId,
								 IntrId,
								 IntrMask);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return Status;
}

int GpioSetupIntrSystem( INTC *IntcInstancePtr,
						 XGpio *InstancePtr,
						 u16 DeviceId,
						 u16 IntrId, u16
						 IntrMask)
{
	int Result;

	GlobalIntrMask = IntrMask;

	XScuGic_Config *IntcConfig;

	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);

	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Result = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
						IntcConfig->CpuBaseAddress);
	if (Result != XST_SUCCESS) {
		return XST_FAILURE;
	}


	XScuGic_SetPriorityTriggerType(IntcInstancePtr, IntrId,
					0xA0, 0x3);
	/*
	 * Connect the interrupt handler that will be called when an
	 * interrupt occurs for the device.
	 */
	Result = XScuGic_Connect(IntcInstancePtr, IntrId,
				 (Xil_ExceptionHandler)GpioHandler, InstancePtr);
	if (Result != XST_SUCCESS) {
		return Result;
	}

	/* Enable the interrupt for the GPIO device.*/
	XScuGic_Enable(IntcInstancePtr, IntrId);

	/*
	 * Enable the GPIO channel interrupts so that push button can be
	 * detected and enable interrupts for the GPIO device
	 */
	XGpio_InterruptEnable(InstancePtr, IntrMask);
	XGpio_InterruptGlobalEnable(InstancePtr);

	/*
	 * Initialize the exception table and register the interrupt
	 * controller handler with the exception table
	 */
	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 (Xil_ExceptionHandler)INTC_HANDLER, IntcInstancePtr);

	/* Enable non-critical exceptions */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}


void GpioHandler(void *CallbackRef)
{
	XGpio *GpioPtr = (XGpio *)CallbackRef;
	XGpio_InterruptDisable(GpioPtr, GlobalIntrMask);
	if ((XGpio_InterruptGetStatus(GpioPtr) & GlobalIntrMask) != GlobalIntrMask) {
		return;
	}
	// Debounce delay
	int delay = 0;
	while(delay < INTR_DELAY) {
		delay++;
	}
	btn_value_ = XGpio_DiscreteRead(GpioPtr, BUTTON_CHANNEL);
	if (btn_value_ == 0) {
		(void) XGpio_InterruptClear(GpioPtr, GlobalIntrMask);
		XGpio_InterruptEnable(GpioPtr, GlobalIntrMask);
		return;
	}
	while (XGpio_DiscreteRead(GpioPtr, BUTTON_CHANNEL) > 0)
	{ }
	btn_value_ = 0;
	/* Clear the Interrupt */
	(void) XGpio_InterruptClear(GpioPtr, GlobalIntrMask);
	XGpio_InterruptEnable(GpioPtr, GlobalIntrMask);

}


void GpioDisableIntr(INTC *IntcInstancePtr, XGpio *InstancePtr,
			u16 IntrId, u16 IntrMask)
{
	XGpio_InterruptDisable(InstancePtr, IntrMask);
	/* Disconnect the interrupt */
	XScuGic_Disable(IntcInstancePtr, IntrId);
	XScuGic_Disconnect(IntcInstancePtr, IntrId);
	return;
}
