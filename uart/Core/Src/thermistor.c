//////////////////////////////////////
//
//      Thermistor Nucleo Hardware Interface
//      Written By:
//      Nathan Richards
//      nricha@umich.edu
//
//////////////////////////////////////
//#define THERMISTOR_ENABLE

#include "thermistor.h"



Thermistors* thermistors;
float currTemps[3];

///////////////////
//
// Public Functions
//
///////////////////


Thermistors* newThermistors(uint32_t channel0, uint32_t channel1, uint32_t channel2){
    Thermistors* therms = (Thermistors*) malloc(sizeof(Thermistors));

    float tempConstArray[4][4] = {{3.3570420E-03, 2.5214848E-04, 3.3743283E-06, -6.4957311E-08},
                                  {3.3540170E-03, 2.5617244E-04, 2.1400943E-06, -7.2405219E-08},
                                  {3.3530481E-03, 2.5420230E-04, 1.1431163E-06, -6.9383563E-08},
                                  {3.3536166E-03, 2.5377200E-04, 8.5433271E-07, -8.7912262E-08}};

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            therms->constantArray[i][j] = tempConstArray[i][j];
        }
    }

    // NOTE make sure you set these to whatever your resistor values are
    therms->R1vals[0] = 9820; therms->R1vals[1] = 10020; therms->R1vals[2] = 9830;

    therms->V1 = 3.3;

    therms->R25 = 10000;

    therms->adcPins[0] = channel0; therms->adcPins[1] = channel1; therms->adcPins[2] = channel2;

    // Disable all channels, restart when you want to read
    ADC_Enable_CH(channel0, 0);
    ADC_Enable_CH(channel1, 0);
    ADC_Enable_CH(channel2, 0);
    return therms;
}




float getTemp(const uint8_t whichTherm, const Thermistors* therms){
    
    //Before reading voltage, enable only the selected channel

	uint32_t rawData = _readVoltage(therms->adcPins[whichTherm]);


    // Logic to get actual Voltage from 12 bit string
    // NOTE pretty sure it is 12 bit that's what HAL says in documentation, but could be wrong
    float currVolt = (rawData * therms->V1) / (float)4095; // 2^12 - 1= 4095 (12 bit string  )

    // Circuit math to get temperature from voltage
    float Rt = (((float)therms->R1vals[whichTherm] * therms->V1) / currVolt) - therms->R1vals[whichTherm];

    uint8_t constSet;
    if(Rt < 69200 && Rt >= 32770){
        constSet = 0;
    } else if (Rt < 32770 && Rt >= 3599){
        constSet = 1;
    } else if (Rt < 3599 && Rt >= 681.6){
        constSet = 2;
    } else if (Rt < 681.6 && Rt >= 187){
        constSet = 3;
    } else {
        // TODO error out cause OOB temp
    }

    float lnRtoverR25 = log(Rt/therms->R25);

    float oneOverT = therms->constantArray[constSet][0] + (therms->constantArray[constSet][1] * lnRtoverR25)
                     + (therms->constantArray[constSet][2] * lnRtoverR25 * lnRtoverR25)
                     + (therms->constantArray[constSet][3] * lnRtoverR25 * lnRtoverR25 * lnRtoverR25);

    return (1 / oneOverT) - 272.15;
}


void deleteThermistors(Thermistors* thermistors){
    free(thermistors);
}

void send_thermistor_data(Thermistors* therms, UART_HandleTypeDef* huart){
  for(int t = 0; t < 3; t++){
    currTemps[t] = getTemp(t, therms);
  }

  char string[50] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

  sprintf((char *)string, "$THERMISTOR,%f,%f,%f,\n", currTemps[0], currTemps[2], currTemps[1]);
  //HAL_UART_Transmit(huart, (uint8_t *)string, sizeof(string), 15);

  HAL_UART_Transmit_IT(huart, (uint8_t *)string, sizeof(string));
  HAL_Delay(15);
  // Delay before Clearing flags so beaglebone can successfully read the
//  HAL_Delay(100);


}

///////////////////
//
// Private Functions
//
///////////////////
//Selects and Disables all other
void ADC_Enable_CH (uint32_t adcChannel, int enable)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	if (enable){
		sConfig.Channel = adcChannel;
			  sConfig.Rank = 1;
			  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
			  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
			  {
				Error_Handler();
			  }
	}
	else{
		sConfig.Channel = adcChannel;
		sConfig.Rank = ADC_RANK_NONE;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		  {
			Error_Handler();
		  }
	}

}

uint32_t _readVoltage(uint32_t adcChannel){
	ADC_Enable_CH(adcChannel, 1);
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t raw = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    ADC_Enable_CH(adcChannel, 0);
    return raw;
}
