/*
 * main_preloop.c
 *
 *  Created on: Oct 31, 2021
 *      Author: aweso
 */

//Include for every Sensor
#include "main.h"
#include "main_loop.h"

#define JETSON_UART &huart2


// Extern Vars



int main_preloop(){
	HAL_UART_Receive_DMA(JETSON_UART,Rx_data,20);
#ifdef THERMISTOR_ENABLE
	thermistors = new_thermistors(&hadc2, &hadc3, &hadc4);
#endif

#ifdef MOSFET_ENABLE
  // Enable pin

  // sci UV
  // enablePin(0, UV_BULB_GPIO_Port, UV_BULB_Pin);
  // sa UV
  // enablePin(0, AUTON_LEDS_2_UV_LEDS_GPIO_Port, AUTON_LEDS_2_UV_LEDS_Pin);
  // white LED
  // enablePin(0, AUTON_LEDS_1_WHITE_LED_GPIO_Port, AUTON_LEDS_1_WHITE_LED_Pin);

  mosfetcopy = (char *)malloc(21);
#endif

#ifdef SPECTRAL_ENABLE
   	i2cBus = new_smbus(&hi2c1, USB_UART);
	i2cBus->DMA = 0;
	mux = new_mux(i2cBus);
	spectral = new_spectral(i2cBus);

	// adds all the spectral channels
	for (int i = 0; i < SPECTRAL_DEVICES; ++i) {
		add_channel(mux, spectral_channels[i]);
	}

	// opens all channels on the mux to listen

	for (int i = 0; i < SPECTRAL_DEVICES; ++i) {
		channel_select(mux, mux->channel_list[i]);
		enable_spectral(spectral);
	}

#endif

#ifdef HBRIDGE_MOTOR_ENABLE
	hbridge_motor = new_motor(HBRIDGE_FWD_GPIO_Port, HBRIDGE_FWD_Pin, HBRIDGE_BWD_GPIO_Port, HBRIDGE_BWD_Pin, HBRIDGE_TIMER);
	start(hbridge_motor, TIM_CHANNEL_1);

#endif

#ifdef TRIAD_ENABLE

	i2cBus = new_bus(&hi2c2, &huart2);

	uint8_t buf[30];

	triad_dev_1 = new_device(0x00);

	triad_dev_2 = new_device(0x01);

	triad_dev_3 = new_device(0x02);

	triad[0] = triad_dev_1;
	triad[1] = triad_dev_2;
	triad[2] = triad_dev_3;

	virtual_write(0x04, 0x28);
	virtual_write(0x04, 0x28);
	virtual_write(0x05, 0xFF);

#endif
	return 0;
}
