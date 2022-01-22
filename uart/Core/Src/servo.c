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

void receive_servo_cmd(uint8_t *buffer, int *angle0, int *angle1, int *angle2, char*servocopy){

  //Change to string
  char delim[] = ",";

  strcpy(servocopy, buffer);

  if (servocopy == NULL) {
  	return;
  }

  //Expected $Servo,<angle0>,<angle1>,<angle2>
  char *identifier = strtok(servocopy,delim);
  if (!strcmp(identifier,"$Servo")){
	  *angle0 = atoi(strtok(NULL,delim));
	  *angle1 = atoi(strtok(NULL,delim));
	  *angle2 = atoi(strtok(NULL,delim));
  }
}
