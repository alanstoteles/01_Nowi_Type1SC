/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char Test[] = "AT\r\n"; 	//Test the GSM module, Attention
char echo[] = "ATE0\r\n";   //Disable the ECHO
char ati[] = "ati\r\n";   	//Get Modem FW information
char IP_Address[] = "AT+CGPADDR=1\r\n";   	//Get Modem FW information
char socket_cmd_allo[] = "AT%SOCKETCMD=\"ALLOCATE\",0,\"UDP\",\"OPEN\",\"20.61.15.37\",8891\r\n";
char socket_cmd_setop[] = "AT%SOCKETCMD=\"SETOP\",1,36000,1\r\n";
char socket_cmd_act[] ="AT%SOCKETCMD=\"ACTIVATE\",1\r\n";
//char payload[] = "XyCeJDw1asIy"+"\n"+"maker:4NKvHe7TVXsmq7VL7J"+"\n"+"{\"VBAT\":{\"value\":91},\"TEMP\":{\"value\":21}}";
//char socket_data[] = "AT%SOCKETDATA=\"SEND\",1,"+str(sizeof(payload));


uint8_t Tx_Delay = 10;
uint8_t Rx_Buffer[256] = " ";
uint8_t Rx_data = 0;
volatile uint8_t Rx_indx = 0;
uint8_t Rx_complete = 1;
uint32_t lastGetTick;
unsigned char state = 1;
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
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(CTRL_PMU_WK_GPIO_Port, CTRL_PMU_WK_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  if(HAL_UART_Receive_IT(&hlpuart1, &Rx_data, 1)!= HAL_OK)
  {
	  Error_Handler();
  }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch (state)
	  {
	  	  case 1:
	  		  if((HAL_GetTick()-lastGetTick)>=1000)
	  		  {
	  			if (Rx_complete == 1)
				{
	  				memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
	  				if(HAL_UART_Transmit(&hlpuart1, (uint8_t *)Test, strlen(Test), HAL_MAX_DELAY) != HAL_OK)
					{
	  					Error_Handler();
					}
					lastGetTick=HAL_GetTick();
					state = 2;
				}
	  		  }
	  		  break;
	  	  case 2:
	  		  if((HAL_GetTick()-lastGetTick)>=1000)
	  		  {
		  		if (Rx_complete == 1)
				{
		  			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
		  			if(HAL_UART_Transmit(&hlpuart1, (uint8_t *)ati, strlen(ati), HAL_MAX_DELAY) != HAL_OK)
		  			{
	  				  Error_Handler();
		  			}
		  			lastGetTick=HAL_GetTick();
		  			state = 3;
				}
	  		  }
	  		  break;
	  	  case 3:
	  		  if((HAL_GetTick()-lastGetTick)>=1000)
	  		  {
		  		if (Rx_complete == 1)
				{
		  			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
		  			if(HAL_UART_Transmit(&hlpuart1, (uint8_t *)IP_Address, strlen(IP_Address), HAL_MAX_DELAY) != HAL_OK)
		  			{
	  				  Error_Handler();
		  			}
		  			lastGetTick=HAL_GetTick();
		  			state = 4;
				}
	  		  }
	  		  break;
	  	  case 4:
	  		  if((HAL_GetTick()-lastGetTick)>=1000)
	  		  {
		  		if (Rx_complete == 1)
				{
		  			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
		  			if(HAL_UART_Transmit(&hlpuart1, (uint8_t *)socket_cmd_allo, strlen(socket_cmd_allo), HAL_MAX_DELAY) != HAL_OK)
		  			{
	  				  Error_Handler();
		  			}
		  			lastGetTick=HAL_GetTick();
		  			state = 5;
				}
	  		  }
	  		  break;
	  	  case 5:
	  		  if((HAL_GetTick()-lastGetTick)>=1000)
	  		  {
		  		if (Rx_complete == 1)
				{
		  			memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
		  			if(HAL_UART_Transmit(&hlpuart1, (uint8_t *)socket_cmd_setop, strlen(socket_cmd_setop), HAL_MAX_DELAY) != HAL_OK)
		  			{
	  				  Error_Handler();
		  			}
		  			lastGetTick=HAL_GetTick();
		  			state = 1;
				}
	  		  }
	  		  break;
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == LPUART1)
	{
		Rx_complete = 0;
		Rx_Buffer[Rx_indx++] = Rx_data;
		if (Rx_indx + 1 > sizeof(Rx_Buffer))
		{
			Rx_indx = 0;
			Rx_complete = 1;
		}
		if (Rx_Buffer[Rx_indx-1] == 0x0a && Rx_Buffer[Rx_indx-2] == 0x0d && Rx_Buffer[Rx_indx-3] == 0x4b && Rx_Buffer[Rx_indx-4] == 0x4f)
		{
			Rx_indx = 0;
			Rx_complete = 1;
		}
		if (Rx_Buffer[Rx_indx-1] == 0x0a && Rx_Buffer[Rx_indx-2] == 0x0d && Rx_Buffer[Rx_indx-3] == 0x52 && Rx_Buffer[Rx_indx-4] == 0x4f && Rx_Buffer[Rx_indx-5] == 0x52 && Rx_Buffer[Rx_indx-6] == 0x52 && Rx_Buffer[Rx_indx-7] == 0x45)
		{
			Rx_indx = 0;
			Rx_complete = 1;
		}

		__HAL_UART_CLEAR_OREFLAG(huart); //clear the overrun flag
		__HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST); // Discard the received data
		HAL_StatusTypeDef status = HAL_UART_Receive_IT(&hlpuart1, &Rx_data, 1); // Restart Receive
		if (status != HAL_OK)
		{
			__NOP(); // Only for setting breakpoint
		}
    }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
 __NOP();
}

void string2hexString(char* input, char* output)
{
    int loop;
    int i;

    i=0;
    loop=0;

    while(input[loop] != '\0')
    {
        //sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
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
