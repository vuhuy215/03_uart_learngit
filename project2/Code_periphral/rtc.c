#include "main.h"


extern RTC_HandleTypeDef hrtc;
extern char* getDayofweek(uint8_t number);

extern void RTC_GetTime_GetDate(uint16_t GPIO_Pin)
{
	 RTC_TimeTypeDef RTC_TimeRead;
	 RTC_DateTypeDef RTC_DateRead;

	 HAL_RTC_GetTime(&hrtc,&RTC_TimeRead,RTC_FORMAT_BIN);

	 HAL_RTC_GetDate(&hrtc,&RTC_DateRead,RTC_FORMAT_BIN);

	 printmsg("Current Time is : %02d:%02d:%02d ",RTC_TimeRead.Hours,\
			 RTC_TimeRead.Minutes,RTC_TimeRead.Seconds);
	 printmsg("Current Date is : %02d-%2d-%2d  <%s> \r\n",RTC_DateRead.Month,RTC_DateRead.Date,\
			 RTC_DateRead.Year,getDayofweek(RTC_DateRead.WeekDay));
}

extern void RTC_Init(void)
{
   hrtc.Instance = RTC;
   hrtc.Init.HourFormat =RTC_HOURFORMAT_12;
   hrtc.Init.AsynchPrediv = 0x7F;
   hrtc.Init.SynchPrediv = 0xFF;
   hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
   hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_LOW;
   hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

   if( HAL_RTC_Init(&hrtc) != HAL_OK)
   {
	   Error_Handler();
   }
}

extern void  RTC_CalendarConfig(void)
{
	RTC_TimeTypeDef RTC_TimeInit;
	RTC_DateTypeDef RTC_DateInit;
	//this function does RTC Calendar Config
	//Lets configure the calendar for Time : 12:11:10 PM Date : 12 june 2018 TUESDAY

	RTC_TimeInit.Hours = 10;
	RTC_TimeInit.Minutes = 0;
	RTC_TimeInit.Seconds = 0;
	RTC_TimeInit.TimeFormat = RTC_HOURFORMAT12_PM;
	HAL_RTC_SetTime(&hrtc, &RTC_TimeInit,RTC_FORMAT_BIN);


	RTC_DateInit.Date = 2;
	RTC_DateInit.Month = RTC_MONTH_NOVEMBER;
	RTC_DateInit.Year = 21;
	RTC_DateInit.WeekDay = RTC_WEEKDAY_WEDNESDAY;

	HAL_RTC_SetDate(&hrtc,&RTC_DateInit,RTC_FORMAT_BIN);

}

extern void  RTC_ReConfig(void)
{
	 RTC_TimeTypeDef RTC_TimeRead1;
	 RTC_DateTypeDef RTC_DateRead1;
	 HAL_RTC_GetTime(&hrtc,&RTC_TimeRead1,RTC_FORMAT_BIN);

	 HAL_RTC_GetDate(&hrtc,&RTC_DateRead1,RTC_FORMAT_BIN);
	 uint8_t minutes =0;
	 HAL_RTC_DeInit(&hrtc);
	 if ((RTC_TimeRead1.Minutes+5) >=60)
	 {
		 minutes =0;
	 }else{
		 minutes=RTC_TimeRead1.Minutes+5;
	 }




	RTC_TimeTypeDef RTC_TimeInit;
	RTC_DateTypeDef RTC_DateInit;
	//this function does RTC Calendar Config
	//Lets configure the calendar for Time : 12:11:10 PM Date : 12 june 2018 TUESDAY

	RTC_TimeInit.Hours = (uint8_t)(RTC_TimeRead1.Hours);
	RTC_TimeInit.Minutes = (minutes);
	RTC_TimeInit.Seconds = (uint8_t)RTC_TimeRead1.Seconds;
	RTC_TimeInit.TimeFormat = RTC_HOURFORMAT12_PM;
	HAL_RTC_SetTime(&hrtc, &RTC_TimeInit,RTC_FORMAT_BIN);


	RTC_DateInit.Date = RTC_DateRead1.Date;
	RTC_DateInit.Month = RTC_DateRead1.Month;
	RTC_DateInit.Year = RTC_DateRead1.Year;
	RTC_DateInit.WeekDay = RTC_DateRead1.WeekDay;

	HAL_RTC_SetDate(&hrtc,&RTC_DateRead1,RTC_FORMAT_BIN);

}

extern char* getDayofweek(uint8_t number)
{
	char *weekday[] = { "Monday", "TuesDay", "Wednesday","Thursday","Friday","Saturday","Sunday"};

	return weekday[number-1];
}

extern void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
 {
	  RCC_OscInitTypeDef        RCC_OscInitStruct;
	  RCC_PeriphCLKInitTypeDef RCC_RTCPeriClkInit;
	  //1. Turn on the LSE
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
		  Error_Handler();
	  }

	  //2. select LSE as RTCCLK
	  RCC_RTCPeriClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	  RCC_RTCPeriClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	  if( HAL_RCCEx_PeriphCLKConfig(&RCC_RTCPeriClkInit)!= HAL_OK)
	  {
		  Error_Handler();
	  }

	  //3. Enable the RTC Clock
	  __HAL_RCC_RTC_ENABLE();
 }














