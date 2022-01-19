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
	int angle = -1;
	int servo_device = -1;
	if(message[1] == 'S')
	{
		receive_servo_cmd(message,&servo_device,&angle,servocopy);
	}

	int d_s = servo_device;

	write_angle(angle, d_s);

	clear_flags();
#endif



#ifdef SPECTRAL_ENABLE
	i2cBus = new_smbus(&hi2c1, USB_UART);
	i2cBus->DMA = 0;
	mux = new_mux(i2cBus);
	spectral = new_spectral(i2cBus);

	for (int i = 0; i < SPECTRAL_DEVICES; ++i) {
		  channel_select(mux, mux->channel_list[spectral_channels[i]]);
		  get_spectral_data(spectral, spectral_data + (i * CHANNELS));
		}

		send_spectral_data(spectral_data, JETSON_UART);
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

	for (uint8_t i = 0; i < 3; ++i) {
	  virtual_write(DEV_SEL, triad[i]->dev_register);
	  for (uint8_t j = 0; j < CHANNELS; ++j) {
		  channel = triad[i]->channels[j];
		  channel->color_data = get_decimal(channel->lsb_register, channel->msb_register);

		  //complicated way to print "channel {x} : {data}"
		  sprintf((char*)buf_triad , "channel %u : %f \r\n", (unsigned int)((i*CHANNELS) + j), (float)channel->color_data);

		  HAL_UART_Transmit(&huart1, buf_triad, strlen((char*)buf_triad), HAL_MAX_DELAY);
		  HAL_Delay(10);
	  }
	}
	HAL_Delay(1000);
#endif
	return 0;
}
