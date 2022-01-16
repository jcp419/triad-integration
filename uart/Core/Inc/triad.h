//#ifdef TRIAD_ENABLE

#ifndef TRIAD_H_
#define TRIAD_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "spectral.h"
#include "smbus.h"
#include "stm32g0xx_hal.h"
#include "mux.h"


static HAL_StatusTypeDef ret;
uint8_t buf[30];

Bus *i2cBus;

typedef struct {
	uint8_t dev_register;
	Channel *channels[CHANNELS];
} Device;


Device *triad_dev_1 = NULL;

Device *triad_dev_2 = NULL;

Device *triad_dev_3 = NULL;

Device *triad[3] = NULL;

// Function prototypes

uint16_t get_decimal(uint8_t virtual_reg_l, uint8_t virtual_reg_h);
Device* new_device(uint8_t dev_register);

#endif

//#endif
