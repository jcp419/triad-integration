#ifndef MOSFET_H_
#define MOSFET_H_

#include "stm32g0xx_hal.h"

// define number of devices for the MOSFET
#define MOSFET_DEVICE_NUM 9

#include "main.h"
#include "stdlib.h"
#include "string.h"

// Private Interface
// Enable or disable a certain pin
void enablePin(int enable, GPIO_TypeDef *port, uint16_t pin);
void receive_mosfet_cmd(uint8_t *buffer, int *device,int*enable, char*mosfetcopy);
void send_rr_drop(UART_HandleTypeDef* huart);


// Array of all pins and ports for each device
// Put a better formatted list here to make it easier
// 1.
// 2.
// 3. etc
extern uint16_t pin_array[MOSFET_DEVICE_NUM];
extern GPIO_TypeDef* port_array[MOSFET_DEVICE_NUM];

extern char* mosfetcopy;

//GPIO_TypeDef *device_ports[6] = {
//		GPIOC,
//		GPIOC,
//		GPIOC,
//		GPIOC,
//		GPIOC,
//		GPIOC
//};
//
//int device_pins[6] = {
//		0,
//		0,
//		0,
//		GPIO_PIN_10,
//		GPIO_PIN_11,
//		GPIO_PIN_15
//};
//void setPin(int set, int device);



#endif

