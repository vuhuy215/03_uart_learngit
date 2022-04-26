/*
 * uart.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Admin
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"

#define HUY_MAX_DELAY 0xFFFFFFFF
void USART1_Init(void);
uint8_t USART1_write (uint8_t ch);
uint8_t USART1_read (void);
bool uart_uart1_transmit(uint8_t *data, uint8_t len, uint32_t timeout);
void USART1_Init(void);




void USART1_Init(void)
{

// 1.enable clock access to uart(ABP2)
	RCC->APB2ENR |= 0x01<<4;

// 2.enable clock access for port (port A)
	RCC->AHB1ENR |= 0x01<<0;
// 3.0) enable mode for pin( alternate)
	GPIOA->MODER &= ~(0x0F<<18);
	GPIOA->MODER |= 0x0A<<18;
// 3.enable pins for alternate functions (PA9, PA10, AF7) chọn AF7
	GPIOA->AFR[1] &= ~(0xFF<<4);
	GPIOA->AFR[1] |= 0x77<<4;
// 4.config uart
	//do bài này đặt trong môi trường không quá nhiều nhiễu nên chọn
	//OVER SAMPLE =8
	//Fclk của uart là 16M (mặc định)
	//baudrate: 115200 => tính ra được uart div là 17.361 => uartx 0x113
	USART1->BRR =0x113;
	//over8=1
	USART1->CR1 |= USART_CR1_OVER8;
	//enable TE và RE
	USART1->CR1 |= 0xC;
	//chọn stop bit bằng 1, (cái này mặc định rồi nên không cần làm với CR2
	USART1->CR2 =0x0;
	//không chọn flow control
	USART1->CR3 =0x0;
	//enable uart
	USART1->CR1 |= 1<<13;

}

bool uart_uart1_transmit(uint8_t *data, uint8_t len, uint32_t timeout)
{
	uint8_t dataIdx =0;
	uint32_t startTick = rcc_get_ticks();
	while (dataIdx < len)
	{
		if(USART1->SR &= 1<<7)  //make sure transmit buffer is empty:
		{
			USART1->DR = data[dataIdx];
			dataIdx++;
		}
		else  //manage time out
		{
			if (rcc_get_ticks() - startTick >= timeout) return false;
		}
	}

	//wait for busy flag
	while (USART1->SR &	USART_SR_TC)
	{
		if (rcc_get_ticks() - startTick >= timeout) return false;
	}
	return true;
}

//hàm gửi dữ liệu lên uart:
uint8_t USART1_write (uint8_t ch)
{
	//make sure transmit buffer is empty:
	while((USART1->SR &= 1<<7)==0){}
	USART1->DR =(ch & 0xFF);
	return ch;

}

//hàm đọc dữ liệu từ uart
uint8_t USART1_read (void)
{
	//check xem recevie buffer đã bật lên một chưa
	while(0==(USART1->SR &= 1<<5)){}
	return (uint8_t ) USART1->DR;
}



#endif /* UART_H_ */
