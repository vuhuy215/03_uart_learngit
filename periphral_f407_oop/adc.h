/*
 * adc.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Admin
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"
uint32_t analogValue;
void single_conversion_adc1_channel10_pin_C0 (void);

void single_conversion_adc1_channel10_pin_C0 (void)
{

		//bài này sử dụng ADC1 (APB2), dùng chân PC0, channel 10.


		//enable clock for portc
		RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN_Msk;
		//set PC0 to analog:
		GPIOC->MODER |=0x03;
		//enable clock for ADC:
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN_Msk;
		//disable to ADC:
		ADC1->CR2 =0;
		//chọn kênh.
		ADC1->SQR3 |= 0xA;
		//enable ADC:
		ADC1->CR2 |=1;

		while(1)
		{
			//start conversion: (do mặc định là single conversion nên phải start liên tục)
			ADC1->CR2 |= 1<<30;
			//wait for the conversion to be complete:
			while (!(ADC1->SR&2)){}
			analogValue = ADC1->DR;
		}
}

#endif /* ADC_H_ */
