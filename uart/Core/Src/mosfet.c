//#ifdef MOSFET_ENABLE
#include "mosfet.h"
#include "main.h"

// Array of all pins and ports for each device
// Put a better formatted list here to make it easier

uint16_t pin_array[MOSFET_DEVICE_NUM] = {
		AUTON_LED_0_Pin,            	// 0
		AUTON_LED_1_AND_LASER_Pin,      // 1
		AUTON_LED_2_AND_UV_LED_Pin,     // 2
		WHITE_LED_Pin,               	// 3
		UV_BULB_Pin,               		// 4
        NICHROME_WIRE_0_Pin,            // 5
        NICHROME_WIRE_1_Pin,            // 6
        NICHROME_WIRE_2_Pin,            // 7
		RAMAN_LASER_Pin                 // 8
};

GPIO_TypeDef* port_array[MOSFET_DEVICE_NUM] = {
		AUTON_LED_0_GPIO_Port,            	// 0
		AUTON_LED_1_AND_LASER_GPIO_Port,    // 1
		AUTON_LED_2_AND_UV_LED_GPIO_Port,   // 2
		WHITE_LED_GPIO_Port,              	// 3
		UV_BULB_GPIO_Port,               	// 4
		NICHROME_WIRE_0_GPIO_Port,          // 5
		NICHROME_WIRE_1_GPIO_Port,          // 6
		NICHROME_WIRE_2_GPIO_Port,          // 7
		RAMAN_LASER_GPIO_Port               // 8
};

char *mosfetcopy;
void enablePin(int enable, GPIO_TypeDef *port, uint16_t pin){
    if (enable){
         HAL_GPIO_WritePin(port,pin, GPIO_PIN_SET);
    }
    else{
        HAL_GPIO_WritePin(port,pin,GPIO_PIN_RESET);
    }
}

void receive_mosfet_cmd(uint8_t *buffer, int *device,int*enable, char*mosfetcopy){

  //Change to string
  char delim[] = ",";

  strcpy(mosfetcopy, buffer);

  if (mosfetcopy == NULL) {
  	return;
  }

  //Expected $Mosfet,<devicenum>,<enablenum>
  char *identifier = strtok(mosfetcopy,delim);
  if (!strcmp(identifier,"$Mosfet")){
	  *device = atoi(strtok(NULL,delim));
	  *enable = atoi(strtok(NULL,delim));
  }
}


void send_rr_drop(UART_HandleTypeDef* huart){
	char string[11];
	sprintf((char *)string, "$REPEATER\n");
	HAL_UART_Transmit(huart, (uint8_t *)string, sizeof(string), 11);
}
//#endif

