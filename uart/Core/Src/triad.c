//#ifdef TRIAD_ENABLE

#include "triad.h"

uint8_t buf_triad[30];
SMBus *i2cBus;
Device *triad[3];

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

uint8_t virtual_read(uint8_t v_reg) {
	uint8_t status;
	uint8_t d;

	// status = nucleo_byte_read(I2C_AS72XX_SLAVE_STATUS_REG);
	status = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_STATUS_REG);

	if ((status & I2C_AS72XX_SLAVE_RX_VALID) != 0) {
		// d = nucleo_byte_read(I2C_AS72XX_SLAVE_READ_REG);
		d = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_READ_REG);
	}

	while(1) {
		// status = nucleo_byte_read(I2C_AS72XX_SLAVE_STATUS_REG);
		status = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_STATUS_REG);

		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0) {
			break;
		}
		HAL_Delay(5); //delay for 5 ms
	}

	// nucleo_byte_write(I2C_AS72XX_SLAVE_WRITE_REG, v_reg);
	write_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_WRITE_REG, v_reg);

	while(1) {
		// status = nucleo_byte_read(I2C_AS72XX_SLAVE_STATUS_REG);
		status = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_STATUS_REG);

		if ((status & I2C_AS72XX_SLAVE_RX_VALID) != 0) {
			break;
		}
		HAL_Delay(5); //delay for 5 ms
	}

	// d = nucleo_byte_read( I2C_AS72XX_SLAVE_READ_REG);

	d = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_READ_REG);

	return d;
}


void virtual_write(uint8_t v_reg, uint8_t data) {
	uint8_t status;

	while(1) {
		// status = nucleo_byte_read(I2C_AS72XX_SLAVE_STATUS_REG);
		status = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_STATUS_REG);
		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0) {
			break;
		}
		HAL_Delay(5);
	}

	// nucleo_byte_write(I2C_AS72XX_SLAVE_WRITE_REG, (v_reg | 1 << 7));
	write_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_WRITE_REG, (v_reg | 1 << 7));

	while(1) {
//		status = nucleo_byte_read(I2C_AS72XX_SLAVE_STATUS_REG);
		status = read_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_STATUS_REG);
		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0) {
			break;
		}
		HAL_Delay(5);
	}

	// nucleo_byte_write(I2C_AS72XX_SLAVE_WRITE_REG, data);
	write_byte_data(i2cBus, DEVICE_SLAVE_ADDRESS, I2C_AS72XX_SLAVE_WRITE_REG, data);
}

Channel* new_channel(uint8_t lsb_r, uint8_t msb_r) {
	Channel* ch = malloc(sizeof(Channel));
	ch->color_data = 0;
	ch->lsb_register = lsb_r;
	ch->msb_register = msb_r;
	return ch;
}

//not the most readable code..
//dev channels start at 0x08 and increase by 8 up until 0x13

//#endif
