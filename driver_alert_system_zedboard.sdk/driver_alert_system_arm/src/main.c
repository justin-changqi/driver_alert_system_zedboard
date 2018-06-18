#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "gpio.h"
#include "timer.h"
#include "common.h"
#include "can.h"
#include "i2c.h"

#define FLASH_TIME		100

int main()
{
	int status;
    init_platform();
    printf("Initialing ...\n\r");
    status = GpioInit();
    if (status != XST_SUCCESS) {
    	printf("Failed initial GPIO\n\r");
    }
    CanInit();
    initI2c();
    TimerInit();
    if (status != XST_SUCCESS) {
        printf("Failed initial Timer\n\r");
    }
    initEvevents();
    printf("Device initialed\n\r");
    while(1)
    {
    	updateEvevents(&ask_sensor_data_);
    	updateEvevents(&flash_event_);
    }
    cleanup_platform();
    return 0;
}

