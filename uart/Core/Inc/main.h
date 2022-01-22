/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//Global buffer for receiving UART commands
extern volatile uint8_t Rx_data[20];

// Flag for command received
extern volatile int cmd_received;

//Global buffer of the last received command.
extern volatile uint8_t cmd_data[20];


extern UART_HandleTypeDef huart1;
// Debugging UART through usb connection
extern UART_HandleTypeDef huart2;

//TODO DURING HBRIDGE DEV
//extern HBRIDGE_TIMER;

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c2;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HBRIDGE_BWD_Pin GPIO_PIN_14
#define HBRIDGE_BWD_GPIO_Port GPIOC
#define LIMIT_SWITCH_0_Pin GPIO_PIN_15
#define LIMIT_SWITCH_0_GPIO_Port GPIOC
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define LIMIT_SWITCH_1_Pin GPIO_PIN_1
#define LIMIT_SWITCH_1_GPIO_Port GPIOF
#define LIMIT_SWITCH_2_Pin GPIO_PIN_0
#define LIMIT_SWITCH_2_GPIO_Port GPIOA
#define THERMISTOR_1_Pin GPIO_PIN_3
#define THERMISTOR_1_GPIO_Port GPIOA
#define THERMISTOR_2_Pin GPIO_PIN_4
#define THERMISTOR_2_GPIO_Port GPIOA
#define THERMISTOR_0_Pin GPIO_PIN_5
#define THERMISTOR_0_GPIO_Port GPIOA
#define HBRIDGE_PWM_Pin GPIO_PIN_6
#define HBRIDGE_PWM_GPIO_Port GPIOA
#define MUX_SCL_Pin GPIO_PIN_7
#define MUX_SCL_GPIO_Port GPIOA
#define WHITE_LED_Pin GPIO_PIN_10
#define WHITE_LED_GPIO_Port GPIOB
#define UV_BULB_Pin GPIO_PIN_11
#define UV_BULB_GPIO_Port GPIOB
#define RAMAN_LASER_Pin GPIO_PIN_12
#define RAMAN_LASER_GPIO_Port GPIOB
#define NICHROME_WIRE_0_Pin GPIO_PIN_13
#define NICHROME_WIRE_0_GPIO_Port GPIOB
#define MUX_SDA_Pin GPIO_PIN_14
#define MUX_SDA_GPIO_Port GPIOB
#define SERVO_PWM_0_Pin GPIO_PIN_8
#define SERVO_PWM_0_GPIO_Port GPIOA
#define JETSON_UART_TX_Pin GPIO_PIN_9
#define JETSON_UART_TX_GPIO_Port GPIOA
#define HBRIDGE_FWD_Pin GPIO_PIN_7
#define HBRIDGE_FWD_GPIO_Port GPIOC
#define JETSON_UART_RX_Pin GPIO_PIN_10
#define JETSON_UART_RX_GPIO_Port GPIOA
#define JETSON_UART_CTS_Pin GPIO_PIN_11
#define JETSON_UART_CTS_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define NICHROME_WIRE_1_Pin GPIO_PIN_1
#define NICHROME_WIRE_1_GPIO_Port GPIOD
#define NICHROME_WIRE_2_Pin GPIO_PIN_3
#define NICHROME_WIRE_2_GPIO_Port GPIOD
#define SERVO_PWM_1_Pin GPIO_PIN_3
#define SERVO_PWM_1_GPIO_Port GPIOB
#define AUTON_LED_1_AND_LASER_Pin GPIO_PIN_4
#define AUTON_LED_1_AND_LASER_GPIO_Port GPIOB
#define AUTON_LED_0_Pin GPIO_PIN_5
#define AUTON_LED_0_GPIO_Port GPIOB
#define SERVO_PWM_2_Pin GPIO_PIN_6
#define SERVO_PWM_2_GPIO_Port GPIOB
#define AUTON_LED_2_AND_UV_LED_Pin GPIO_PIN_9
#define AUTON_LED_2_AND_UV_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
