/*
 * main_loop.c
 *
 *  Created on: Oct 31, 2021
 *      Author: aweso
 */

//Include for every Sensor
#include "main.h"
#include "main_loop.h"

// Extern Vars
extern char* mosfetcopy;
extern char* servocopy;
extern uint8_t buf_triad[30];
extern SMBus *i2cBus;
extern Device *triad[3];

#define JETSON_UART &huart2

int main_loop(){

#ifdef THERMISTOR_ENABLE
	// Read and send all thermistor data over Jetson UART
	send_thermistor_data(thermistors, JETSON_UART);
#endif

	//Disable interrupts
	    HAL_NVIC_DisableIRQ(USART1_IRQn);
	   	uint8_t message[20];
	   	for(int i = 0; i< 20; ++i){
	   		message[i] = 0;
	   	}
	   	if(cmd_received == 1){
	   		cmd_received = 0;
	   		memcpy(message,cmd_data,20);
	   	}
	   	HAL_NVIC_EnableIRQ(USART1_IRQn);
	   	//Enable interrupts

#ifdef MOSFET_ENABLE
	int device = -1;
	int enable = -1;
	if(message[1] == 'M')
	{
		receive_mosfet_cmd(message,&device,&enable,mosfetcopy);
	}

	int d_m = device;


	if(d_m>=0 && d_m<=MOSFET_DEVICE_NUM)
	{
	  enablePin(enable, port_array[d_m], pin_array[d_m]);
	}

	clear_flags();
#endif

#ifdef SERVO_ENABLE
	int angle0 = -1;
	int angle1 = -1;
	int angle2 = -1;
	if(message[1] == 'S')
	{
		receive_servo_cmd(message,&angle0,&angle1,&angle2,servocopy);
	}


	write_angle(angle0, 0);
	write_angle(angle1, 1);
	write_angle(angle2, 2);

	clear_flags();
#endif



#ifdef SPECTRAL_ENABLE

	for (int i = 0; i < SPECTRAL_DEVICES; ++i) {
		  channel_select(mux, mux->channel_list[spectral_channels[i]]);
		  get_spectral_data(spectral, spectral_data + (i * CHANNELS));
		}

		send_spectral_data(spectral_data, &huart2);
		//send_spectral_data(spectral_data, USB_UART);
#endif

#ifdef HBRIDGE_MOTOR_ENABLE
	if(message[1] == 'A'){
		receive_hbridge_cmd(message, &speed);
	}
	set_speed(hbridge_motor, speed);
#endif

#ifdef TRIAD_ENABLE
	// strcpy((char*)buf, "Hello!\r\n");
	// HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
	// HAL_Delay(500);
	Channel *channel = new_channel(0, 0);

	// TODO: Don't hardcode the 0 here
	channel_select(mux, mux->channel_list[0]);

	for (uint8_t i = 0; i < 3; ++i) {
	  virtual_write(DEV_SEL, triad[i]->dev_register);
	  for (uint8_t j = 0; j < CHANNELS; ++j) {
		  channel = triad[i]->channels[j];
		  channel->color_data = get_decimal(channel->lsb_register, channel->msb_register);
		  // less complicated way
		  triad_data[(i*CHANNELS) + j] = channel->color_data;

		  HAL_Delay(10);
	  }
	}
	send_triad_data(triad_data, &huart2);

	HAL_Delay(10);
#endif

	return 0;
}
