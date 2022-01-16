//#ifdef TRIAD_ENABLE

#include "triad.h"

uint16_t get_decimal(uint8_t virtual_reg_l, uint8_t virtual_reg_h) {
	uint16_t high = virtual_read(virtual_reg_h) << 8;
	return high | (virtual_read(virtual_reg_l) & 0xFF);
}

Device* new_device(uint8_t dev_register) {
	Device* dev = malloc(sizeof(Device));
	dev->dev_register = dev_register;

	uint8_t START_REG = 0x08; //RAW_VALUE_RGA_LOW;

	for (uint8_t i = 0; i < CHANNELS; ++i) {
		dev->channels[i] = new_channel(START_REG + (2 * i), START_REG + (2 * i) + 1);
	}
	return dev;
}

//#endif
