/*
 * servo.h
 *
 *  Created on: Dec 2, 2021
 *      Author: Sashreek
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"
#include "stdlib.h"
#include "string.h"

extern char*servocopy;
void write_angle(int angle, int servo_num);
void receive_servo_cmd(uint8_t *buffer, int *servo_device, int*angle, char*servocopy);

#endif /* INC_SERVO_H_ */
