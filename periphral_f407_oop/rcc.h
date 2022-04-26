/*
 * rcc.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Admin
 */

#ifndef RCC_H_
#define RCC_H_
#include "main.h"

//GLOBAL
uint32_t msTicks =0;
//prototype
void rcc_inc_ticks();
uint32_t rcc_get_ticks ();
void rcc_ms_delay(uint32_t ms);
void rcc_Systick_config (uint32_t arr);



//increment milisecond Tick
void rcc_inc_ticks()
{
	msTicks++;
}


//get milisecond Tick
uint32_t rcc_get_ticks(void)
{

	return msTicks;
}




//ms DElay
void rcc_ms_delay(uint32_t ms)
{
	uint32_t start_ticks =rcc_get_ticks();
	while((rcc_get_ticks() - start_ticks) < ms){}


}


//systick handler
void SysTick_Handler (void)
{
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	rcc_inc_ticks();
}




//trong hàm này với clock của AHB là 16 M thì nạp giá trị 16000 sẽ tạo ra ngắt 1ms
void rcc_Systick_config (uint32_t arr)
{
	//reset control register
	SysTick->CTRL =0;
	//set the reload value
	SysTick->LOAD = arr-1;
	//enable systick interrupt from NVIC
	NVIC_SetPriority(SysTick_IRQn,0);
	//reset systick current value to 0
	SysTick->VAL =0;
	//enable systick from control register
	//1.chon nguồn là processor clock (AHB)
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	//2.enable interrupt khi đếm đến 0
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	//3.enable systick (cho nó bắt đầu đếm)
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

#endif /* RCC_H_ */
