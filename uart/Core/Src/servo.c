/*
 * servo.c
 *
 *  Created on: Dec 2, 2021
 *      Author: Sashreek
 */

#include "servo.h"

void write_angle(int angle, int servo_num){

	if (servo_num == 1){
		TIM1->CCR1 = (angle/18)+15;
	}
	else if (servo_num == 2){
		TIM1->CCR2 = (angle/18)+15;
	}
	else if (servo_num == 3){
		TIM1->CCR3 = (angle/18)+15;
	}
}

char*servocopy;

void receive_servo_cmd(uint8_t *buffer, int *servo_device, int*angle, char*servocopy){

  //Change to string
  char delim[] = ",";

  strcpy(servocopy, buffer);

  if (servocopy == NULL) {
  	return;
  }

  //Expected $Servo,<devicenum>,<angle>
  char *identifier = strtok(servocopy,delim);
  if (!strcmp(identifier,"$Servo")){
	  *servo_device = atoi(strtok(NULL,delim));
	  *angle = atoi(strtok(NULL,delim));
  }
}
