//#ifdef TRIAD_ENABLE

#include "triad.h"

uint8_t buf_triad[30];
SMBus *i2cBus;
Device *triad[3];

uint16_t triad_data[18];

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

//transmits the triad data as a sentence
//$TRIAD,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,
void send_triad_data(uint16_t *data, UART_HandleTypeDef * huart){
	int channels = 6;
	int devices = 3;

	// 150 - total length of output string $TRIAD,x,y,z...
	char string[150] = "";

	// 36 - 18 channels w/ msb & lsb for each
	int separated_data[36] = {0};

	for (uint8_t i = 0; i < devices; ++i) {

		for (uint8_t j = 0; j < channels; ++j) {

			unsigned int msb = (data[i*channels + j] >> 8) & 0xff;
			unsigned int lsb = (data[i*channels + j]) & 0xff;

			separated_data[(2*i*channels) + (2*j)] =  msb;
			separated_data[(2*i*channels) + (2*j) + 1] =  lsb;

		}

	}

	sprintf((char *)string, "$TRIAD,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u \r\n",\
		  separated_data[0], separated_data[1], separated_data[2], separated_data[3], separated_data[4], separated_data[5], \
		  separated_data[6], separated_data[7], separated_data[8], separated_data[9], separated_data[10], separated_data[11], \
		  separated_data[12], separated_data[13], separated_data[14], separated_data[15], separated_data[16], separated_data[17], \
		  separated_data[18], separated_data[19], separated_data[20], separated_data[21], separated_data[22], separated_data[23], \
		  separated_data[24], separated_data[25], separated_data[26], separated_data[27], separated_data[28], separated_data[29], \
		  separated_data[30], separated_data[31], separated_data[32], separated_data[33], separated_data[34], separated_data[35]);


	HAL_UART_Transmit_IT(huart, (uint8_t *)string, sizeof(string));
	HAL_Delay(40);
}

//not the most readable code..
//dev channels start at 0x08 and increase by 8 up until 0x13

//#endif
