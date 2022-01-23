#ifndef TRIAD_H_
#define TRIAD_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "spectral.h"
#include "smbus.h"
#include "stm32g0xx_hal.h"
#include "mux.h"

typedef struct {
	uint8_t dev_register;
	Channel *channels[CHANNELS];
} Device;

extern uint8_t buf_triad[30];
extern SMBus *i2cBus;
extern Device *triad[3];

// Function prototypes

uint16_t get_decimal(uint8_t virtual_reg_l, uint8_t virtual_reg_h);
Device* new_device(uint8_t dev_register);
uint8_t virtual_read(uint8_t v_reg);
void virtual_write(uint8_t v_reg, uint8_t data);
Channel* new_channel(uint8_t lsb_r, uint8_t msb_r);

extern uint16_t triad_data[18];

#endif

//#endif
