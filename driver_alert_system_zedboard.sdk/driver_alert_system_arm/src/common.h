/*
 * common.h
 *
 *  Created on: Jun 17, 2018
 *      Author: justin
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <stdio.h>
#include "xparameters.h"
#include "xil_types.h"

#define PRINT_SENSOR_

#define GPIO_LED_L				0x02
#define GPIO_LED_R				0x01
#define GPIO_SP					0x04

#define DISTANCE_TH 			40		// cm

#define CHECK_NONE				0x0
#define CHECK_L					0x1
#define CHECK_R					0x2

#define SEND_DELAY				5
#define SP_COUNT				6

struct Event {
	int duration;
	int start_time;
};


extern int Timer_ms;
extern int btn_value_;
int btn_value;
u8 sp_flag_;

struct Event ask_sensor_data_;
struct Event flash_event_;
u8 detect_enable;
u8 can_bus_data_[8];

extern void SetGpioOut(u16 value, u8 mask);
extern int getBtnValue();

//can bus
extern void CANsendData(u8 data);
extern void CANgetData(u8 *data);

//i2c
extern int I2CsendData(u8 data);

void initEvevents();
void updateEvevents(struct Event *event);
void LightHandler();
void DetectHandler();
void decodeData(u8 *input, int *len, double *output);
void HandleAlert(u8 status, double *data);
void SpFlash();



#endif /* SRC_COMMON_H_ */
