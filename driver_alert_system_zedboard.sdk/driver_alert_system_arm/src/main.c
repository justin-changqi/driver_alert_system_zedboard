#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "gpio.h"

int main()
{
    init_platform();

    printf("Hello World\n\r");
    Gpio_init();
    printf("int\n\r");
    cleanup_platform();
    return 0;
}

