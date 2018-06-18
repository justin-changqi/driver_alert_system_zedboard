/*
 * common.c
 *
 *  Created on: Jun 17, 2018
 *      Author: justin
 */

#include "common.h"

void initEvevents()
{
	ask_sensor_data_.duration = 1000;
	ask_sensor_data_.start_time = Timer_ms;
	flash_event_.duration = 500;
	flash_event_.start_time = Timer_ms;
}

void updateEvevents(struct Event *event)
{
	int current_time = Timer_ms;
	if (current_time - event->start_time > event->duration) {
		if (event == &ask_sensor_data_) {
			DetectHandler();
			event->start_time = current_time;
		}
		if (event == &flash_event_) {
			LightHandler();
			event->start_time = current_time;
		}
	}
}

void LightHandler()
{
	static int count = 0;
	switch(getBtnValue()) {
	case 0:
		SetGpioOut(0, GPIO_LED_L);
		SetGpioOut(0, GPIO_LED_R);
		break;
	case 1:
		SetGpioOut(0, GPIO_LED_R);
		SetGpioOut(count%2, GPIO_LED_L);
		I2CsendData(0x01);
		break;
	case 2:
		SetGpioOut(0, GPIO_LED_L);
		SetGpioOut(count%2, GPIO_LED_R);
		I2CsendData(0x08);
		break;
	default:
		break;

	}
	count++;
}

void DetectHandler()
{
	CANsendData(0x05);
	CANgetData();
}
