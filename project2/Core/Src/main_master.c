/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdarg.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "cs101_slave.h"
#include "iec60870_master.h"
#include "iec60870_common.h"
#include "cs101_master.h"
#include "lib_memory.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

//rtc



#define D_UART &huart2
#define C_UART &uart2
#define BL_DEBUG_MSG_EN
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CRC_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

uint8_t asdu[] ={0x0B, 0x03, 0x14, 0x00, 0x01, 0x00, 0x64, 0x00, 0x00, 0xFF, 0xFF, 0x00,0x05, 0x00, 0x00, 0x15, 0x00, 0x00,0x66, 0x00, 0x00, 0x84, 0x03, 0x01};
char menu[] = {"*************************************\
\r\nINTERROGATION COMMAND (QOI =20)     ---->1 \
\r\nSINGLE COMMAND	                    ---->2 \
\r\nType your option here : "};

char menu_single_command[]= {"----------\
\r\nEnter IOA and command\
\r\nLed2 -->IOA = 501\
\r\nLed3 -->IOA = 502\
\r\nType your option here:\r\n"};


//UART2
uint8_t data_buffer[100];
uint8_t recvd_data;
uint32_t count=0;
uint8_t master_send_interrogation =0;
uint8_t master_send_single_command =0;

//gửi cho slave interrogation
uint8_t *data_interrogation;
uint8_t size_data_interrogation =0;
//gửi cho slave single command:
uint8_t *data_single_command;
uint8_t size_data_single_command =0;

uint8_t single_buffer[10];
uint8_t global_single_buffer[3];

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* Callback handler to log sent or received messages (optional) */
static void rawMessageHandler (void* parameter, uint8_t* msg, int msgSize, bool sent)
{
    if (sent)
        printf("SEND: ");
    else
        printf("RCVD: ");

    int i;
    for (i = 0; i < msgSize; i++) {
        printf("%02x ", msg[i]);
    }

    printf("\n");
}

static bool asduReceivedHandler (void* parameter, int address, CS101_ASDU asdu)
{
    printf("RECVD ASDU type: %s(%i) elements: %i\n",
            TypeID_toString(CS101_ASDU_getTypeID(asdu)),
            CS101_ASDU_getTypeID(asdu),
            CS101_ASDU_getNumberOfElements(asdu));

    if (CS101_ASDU_getTypeID(asdu) == M_ME_TE_1) {

        printf("  measured scaled values with CP56Time2a timestamp:\n");

        int i;

        for (i = 0; i < CS101_ASDU_getNumberOfElements(asdu); i++) {

            MeasuredValueScaledWithCP56Time2a io =
                    (MeasuredValueScaledWithCP56Time2a) CS101_ASDU_getElement(asdu, i);

            printf("    IOA: %i value: %i\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueScaled_getValue((MeasuredValueScaled) io)
            );

            MeasuredValueScaledWithCP56Time2a_destroy(io);
        }
    }
    else if (CS101_ASDU_getTypeID(asdu) == M_SP_NA_1) {
        printmsg("single point information:\n\r");

        int i;

        for (i = 0; i < CS101_ASDU_getNumberOfElements(asdu); i++) {

            SinglePointInformation io =
                    (SinglePointInformation) CS101_ASDU_getElement(asdu, i);

            printmsg("    IOA: %d value: %i\n\r",
                    InformationObject_getObjectAddress((InformationObject) io),
                    SinglePointInformation_getValue((SinglePointInformation) io)
            );

            SinglePointInformation_destroy(io);
        }
    }

    else if (CS101_ASDU_getTypeID(asdu) == M_ME_NB_1) {
        printmsg("scaled measure value:\n\r");

        int i;

        for (i = 0; i < CS101_ASDU_getNumberOfElements(asdu); i++) {

        	MeasuredValueScaled io =
                    (MeasuredValueScaled) CS101_ASDU_getElement(asdu, i);

            printmsg("    IOA: %d value: %i\n\r",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueScaled_getValue((MeasuredValueScaled)io)
            );

            MeasuredValueScaled_destroy(io);
        }
    }

    else if (CS101_ASDU_getTypeID(asdu) == M_ME_NC_1) {
        printmsg("float value:\n\r");

        int i;

        for (i = 0; i < CS101_ASDU_getNumberOfElements(asdu); i++) {

        	MeasuredValueShort io =
                    (MeasuredValueShort) CS101_ASDU_getElement(asdu, i);

            printmsg("    IOA: %d value: %f\n\r",
                    InformationObject_getObjectAddress((InformationObject) io),
					MeasuredValueShort_getValue((MeasuredValueShort)io)
            );

            MeasuredValueShort_destroy(io);
        }
    }

    return true;
}
static void linkLayerStateChanged(void* parameter, int address, LinkLayerState state)
{
    printf("Link layer state: ");

    switch (state) {
    case LL_STATE_IDLE:
        printf("IDLE\n");
        break;
    case LL_STATE_ERROR:
        printf("ERROR\n");
        break;
    case LL_STATE_BUSY:
        printf("BUSY\n");
        break;
    case LL_STATE_AVAILABLE:
        printf("AVAILABLE\n");
        break;
    }
}





/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

//  SerialPort port = SerialPort_create(serialPort, 9600, 8, 'E', 1);
//
//   CS101_Master master = CS101_Master_create(port, NULL, NULL, IEC60870_LINK_LAYER_BALANCED);
  CS101_Master master = CS101_Master_create(NULL, NULL, NULL, IEC60870_LINK_LAYER_BALANCED);


     CS101_Master_setOwnAddress(master, 2);

     /* Set the address of the slave (optional for balanced master */
     CS101_Master_useSlaveAddress(master, 3);

     /* set handler for received ASDUs (application layer data) */
     CS101_Master_setASDUReceivedHandler(master, asduReceivedHandler, NULL);

     /* modify some of the default parameters */
     LinkLayerParameters llParams = CS101_Master_getLinkLayerParameters(master);
     llParams->useSingleCharACK = false;

     /* set handler for link layer state changes */
     /* set handler for link layer state changes */
     CS101_Master_setLinkLayerStateChanged(master, linkLayerStateChanged, NULL);

     /* uncomment to log messages */
     CS101_Master_setRawMessageHandler(master, rawMessageHandler, NULL);

//     SerialPort_open(port);

     uint8_t slave_len =0;
     uint8_t slave_asdu[40] ;

     HAL_UART_Transmit(&huart2,(uint8_t *) menu, sizeof(menu), HAL_MAX_DELAY);
     HAL_UART_Receive_IT(&huart2, &recvd_data, 1);

	  CS101_StaticASDU cs101_interrogation = (CS101_StaticASDU) GLOBAL_MALLOC(sizeof(sCS101_StaticASDU));
	  struct sCS101_AppLayerParameters huy;
	  struct sCS101_AppLayerParameters *para =&huy;
	//  CS101_AppLayerParameters para;
	//  para = (CS101_AppLayerParameters)huy;
	  para->sizeOfCA = 2;
	  para->sizeOfIOA = 3;
	  para->sizeOfCOT = 2;

	  cs101_interrogation ->parameters =para;
	  cs101_interrogation ->asdu =asdu;
	  cs101_interrogation ->asduHeaderLength =6;
	  cs101_interrogation ->payloadSize =18;
	  cs101_interrogation ->payload = asdu +6;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


//
//	  CS101_ASDU asdu_huy =(CS101_ASDU) cs101_interrogation;

//
//
//	  asduReceivedHandler(para, 0, asdu_huy);






//mai làm hàm hẳn hoi gửi tổng số byte ở đầu.
//sẽ gửi length trước rồi gửi data sau.

	  if(master_send_interrogation ==1)
	  {
		  CS101_Master_sendInterrogationCommand(master, CS101_COT_ACTIVATION, 1, IEC60870_QOI_STATION);

//		  data_interrogation[size_data_interrogation] = size_data_interrogation;
		  HAL_UART_Transmit(&huart1, &size_data_interrogation, 1, HAL_MAX_DELAY);
		  HAL_UART_Transmit(&huart1, data_interrogation, size_data_interrogation, HAL_MAX_DELAY);

		  //receive len(confirm)
		  HAL_UART_Receive(&huart1, &slave_len, 1, HAL_MAX_DELAY);
		  //receive asdu:(confirm)
		  HAL_UART_Receive(&huart1, slave_asdu, slave_len, HAL_MAX_DELAY);
		  if((slave_asdu[2] & 0x3f) == CS101_COT_ACTIVATION_CON)
		  {
			  //confirm to terminal
			  printmsg("ACTIVATION_CONFIRM\r\n");

			  while (1)
			  {
				  //receive asdu (len)
				  HAL_UART_Receive(&huart1, &slave_len, 1, HAL_MAX_DELAY);
				  //receive asdu
				  HAL_UART_Receive(&huart1, slave_asdu, slave_len, HAL_MAX_DELAY);
//				  printmsg("ahihi\r\n");
//				  printmsg("slave_len: %d \r\n",slave_len);
//				  for(uint8_t i=0; i<slave_len; i++)
//				  {
//					  printmsg("0x%x",slave_asdu[i] );
//				  }
//				  printmsg("\r\n");
				  if((slave_asdu[2] & 0x3f )== CS101_COT_ACTIVATION_TERMINATION)
				  {
					  printmsg("TERMINATION\r\n");
					  break;
				  }
//				  printmsg("vu huy\r\n");
				  cs101_interrogation->payloadSize =  slave_len - (cs101_interrogation->asduHeaderLength);
				  cs101_interrogation->asdu =slave_asdu;
				  cs101_interrogation->payload =slave_asdu+6;
				  CS101_ASDU asdu_huy =(CS101_ASDU) cs101_interrogation;
				  asduReceivedHandler(para, 0, asdu_huy);

			  }

			  //process asdu
			  master_send_interrogation=0;
			  //process asdu
		  }
		  else
		  {
			  printmsg("error");
		  }

		  HAL_UART_Transmit(&huart2,(uint8_t *) menu, sizeof(menu), HAL_MAX_DELAY);
//		  HAL_UART_Receive_IT(&huart2, &recvd_data, 1);

		  master_send_interrogation=0;

	  }


	  if(master_send_single_command ==1)
	  {
		  int a= (((global_single_buffer[2]-48)+500));


		  InformationObject sc = (InformationObject)
				  SingleCommand_create(NULL, (((global_single_buffer[2]-48)+500)),( global_single_buffer[1]-48), false, 0);

		  printf("Send control command C_SC_NA_1\n");
		  CS101_Master_sendProcessCommand(master, CS101_COT_ACTIVATION, 1, sc);

		  HAL_UART_Transmit(&huart1, &size_data_single_command, 1, HAL_MAX_DELAY);
		  HAL_Delay(10);
		  HAL_UART_Transmit(&huart1, data_single_command, size_data_single_command, HAL_MAX_DELAY);
		  InformationObject_destroy(sc);
		  master_send_single_command=0;
		  printmsg("confirmation!!!!!\r\n");
		  HAL_Delay(1000);
		  HAL_UART_Transmit(&huart2,(uint8_t *) menu, sizeof(menu), HAL_MAX_DELAY);


//		  //lần 2
//		  if(1)
//		  {
//		  InformationObject sc = (InformationObject)
//				  SingleCommand_create(NULL, 4000, false, false, 0);
//
//
//		  printf("Send control command C_SC_NA_1\n");
//		  CS101_Master_sendProcessCommand(master, CS101_COT_ACTIVATION, 1, sc);
//
//		  HAL_UART_Transmit(&huart1, data_single_command, size_data_single_command, HAL_MAX_DELAY);
//		  InformationObject_destroy(sc);
//		  master_send_single_command=0;
//		  HAL_UART_Transmit(&huart2, menu, sizeof(menu), HAL_MAX_DELAY);
//		  }
	  }


	  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	  HAL_Delay(1000);




  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void printmsg(char *format,...)
 {
#ifdef BL_DEBUG_MSG_EN
	char str[100];

	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, format);
	vsprintf(str, format,args);
	HAL_UART_Transmit(D_UART,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
	va_end(args);
#endif
 }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{

		 if(recvd_data == '\r')
		 {
			 count =0;
			 if (data_buffer[0] == '1')
			 {
				 master_send_interrogation =1;
//				 HAL_UART_Transmit(&huart2, menu, sizeof(menu), HAL_MAX_DELAY);
			 }

			 if(data_buffer[0] =='2')
			 {
//				 uint8_t single_buffer[10];
				 master_send_single_command=1;
				 HAL_UART_Transmit(&huart2,(uint8_t *) menu_single_command, sizeof(menu_single_command), HAL_MAX_DELAY);
				 HAL_UART_Receive(&huart2, single_buffer, 5, HAL_MAX_DELAY);
				 global_single_buffer[2] = single_buffer[3];

				 HAL_UART_Receive(&huart2, single_buffer, 3, HAL_MAX_DELAY);
				 global_single_buffer[1] = single_buffer[1];
			 }
		 }
		 if(recvd_data == '\n')
		 {
			 count =0;

		 }
		 else
		 {
			 data_buffer[count++] =recvd_data;
		 }

		 HAL_UART_Receive_IT(&huart2,&recvd_data,1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


}








/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
