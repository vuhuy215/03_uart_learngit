/*
 * timer3_16bit.c
 *
 *  Created on: Nov 5, 2021
 *      Author: Admin
 */
#include "main.h"

/*
 * __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1); //xóa cờ ngắt trước khi start timer
 * HAL_TIM_Base_Start_IT(&htimer3);      //start timer
 * void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //call back của timer
 */
extern TIM_HandleTypeDef htimer3;

void TIMER3_Init(void)
{
	htimer3.Instance = TIM3;
	htimer3.Init.Prescaler = 8399; // create timer 1s
	htimer3.Init.Period = 10000-1; //create timer 1s
	if( HAL_TIM_Base_Init(&htimer3) != HAL_OK )
	{
		Error_Handler();
	}

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
 {

 //1. enable the clock for the TIM3 peripheral
 __HAL_RCC_TIM3_CLK_ENABLE();

 //2. Enable the IRQ of TIM6
 HAL_NVIC_EnableIRQ(TIM3_IRQn);

 //3. setup the priority for TIM6_DAC_IRQn
 HAL_NVIC_SetPriority(TIM3_IRQn,15,0);

 }

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer3);

}


