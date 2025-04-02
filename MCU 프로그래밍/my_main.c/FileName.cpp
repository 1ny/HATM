/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32l0xx_nucleo.h"
#include "stdio.h"
#include "string.h"
#include "hw_vcom.h"
#include "at.h"
#include "command.h"

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
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define OFF  0
#define ON	 1
#define TRIG 1
#define RISING_DETECT  1
#define FALLING_DETECT 2
#define BUFSIZE 			 128
#define VDDA_VREFINT_CAL				((uint32_t) 3000)
#define VREFINT_CAL		((uint16_t*)((uint32_t)0x1FF80089))


volatile int count = 0;
volatile int detect_state = RISING_DETECT;
volatile int timer_1s = ON;
volatile uint16_t pulse = 0;
volatile int start_echo = 0;
volatile int end_echo = 0;
volatile float distance = 0;

static uint8_t aTxBuffer[BUFSIZE] = "Hello Nucleo-l073RZ\r\n";	// \r\n in UNIX
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC_Init(void);

/* USER CODE BEGIN PFP */
float HW_Get_LM35_Temp(void);
uint16_t HW_AdcReadChannel(uint32_t Channel);

// Vdda = (( (*VREFINT_CAL) *(uint32_t)VDDA_VREFINT_CAL)/measuredVDDA_char);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#if 0
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Prevent unused argument(s) compilation warning */
	switch (GPIO_Pin)
	{
	case GPIO_PIN_13:
		state = OFF;
		count = 0;
		break;
	case GPIO_PIN_5:
		count++;
		if (count == 20) state = ON;
		break;
	default:
		break;
	}
}
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == htim7.Instance) {
		timer_1s = TRIG;
	}
}
#if 0
if (htim->Instance == htim7.Instance) {
	timer_1s = TRIG;
	pulse = pulse + (htim3.Init.Period / 4);
	if (pulse > htim3.Init.Period) pulse = 0;
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pulse);
#endif

	void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef * htim)
	{
		/* Prevent unused argument(s) compilation warning */
		if (htim->Instance == htim3.Instance && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			switch (detect_state) {
			case RISING_DETECT:
				start_echo = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
				detect_state = FALLING_DETECT;
				break;
			case FALLING_DETECT:
				end_echo = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
				detect_state = RISING_DETECT;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
				break;
			}
		}
	}

	void delay_us(uint16_t time) {
		__HAL_TIM_SET_COUNTER(&htim6, 0);
		while (__HAL_TIM_GET_COUNTER(&htim6) < time);
	}

	uint8_t uart_rcvbuf;
	volatile uint8_t RxFlag = 0;

	void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
	{
		if (huart->Instance == huart2.Instance) {
			// RxFlag = 1;
			HW_VCOM_RxCpltCallback(huart);
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
		MX_TIM7_Init();
		MX_TIM3_Init();
		MX_TIM2_Init();
		MX_TIM6_Init();
		MX_USART2_UART_Init();
		MX_ADC_Init();
		/* USER CODE BEGIN 2 */
		BSP_LED_Off(LED2);
		HAL_TIM_Base_Start_IT(&htim6);
		HAL_TIM_Base_Start_IT(&htim7);
		//HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);

		/* UART */
		// UART - HAL
		//HAL_UART_Transmit(&huart2, (uint8_t*)aTxBuffer, 2, 5000);
		//HAL_UART_Receive_IT(&huart2, &uart_rcvbuf, 2);	// generate interrupt at start
		// UART - hw_vcom (Printf)

		//Printf("Hello Nucleo-l073RZ\r\n");

		//CMD_Init();

	  /* USER CODE END 2 */

	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
		while (1)
		{
			/* USER CODE END WHILE */

			/* USER CODE BEGIN 3 */
#if 0
		// UART Tx & Rx - HAL
			switch (RxFlag) {
			case 1:
				RxFlag = 0;
				HAL_UART_Transmit(&huart2, &uart_rcvbuf, 2, 5000);
				HAL_UART_Receive_IT(&huart2, &uart_rcvbuf, 2);
				break;
			}

			HAL_UART_Transmit(&huart2, (uint8_t*)aTxBuffer, BUFSIZE, 5000);
#endif

#if 1
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

			int diff = 0;

			// detect distance by using ultrasonic sensor + Printf to serial
			if (timer_1s == TRIG) {
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
				delay_us(10);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

				Printf("distance[cm] : %.2f\r\n", distance);
				//Printf("temperature : %.2f\r\n", HW_Get_LM35_Temp());
				timer_1s = OFF;
			}

			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
			__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_CC1);

			switch (detect_state) {
			case RISING_DETECT:
				if (start_echo > end_echo) diff = (0xffff - start_echo) + end_echo;
				else diff = end_echo - start_echo;
				distance = ((340 * 100 / 1000) * diff / 1000.0) / 2.0;
				break;
			default:
				break;
			}

			CMD_Process();
			HW_Get_LM35_Temp();


#endif

#if 0
			// toggle USER_LED by using interrupt (IT)
			switch (detect_state)
			{
			case ON:
				BSP_LED_Toggle(USER_LED);
				HAL_Delay(100);
				break;
			case OFF:
				BSP_LED_Off(USER_LED);
				break;
			default:
				break;
			}
#endif
#if 0
			// toggle USER_LED & LED2 by using USER_BUTTON (Polling)
			if (BSP_PB_Getdetect_state(BUTTON_USER))
			{
				BSP_LED_Off(LED2);
				BSP_LED_On(USER_LED);
			}
			else
			{
				BSP_LED_Off(USER_LED);
				BSP_LED_On(LED2);
			}
#endif
#if 0
			// BSP library example
			BSP_LED_Toggle(LED2);
			BSP_LED_Toggle(USER_LED);
			HAL_Delay(1000);
#endif
		}
		/* USER CODE END 3 */
	}

	/**
	  * @brief System Clock Configuration
	  * @retval None
	  */
	void SystemClock_Config(void)
	{
		RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
		RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
		RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

		/** Configure the main internal regulator output voltage
		*/
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

		/** Initializes the RCC Oscillators according to the specified parameters
		* in the RCC_OscInitTypeDef structure.
		*/
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
		if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		{
			Error_Handler();
		}

		/** Initializes the CPU, AHB and APB buses clocks
		*/
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
		{
			Error_Handler();
		}
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
		PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}
	}

	/**
	  * @brief ADC Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_ADC_Init(void)
	{

		/* USER CODE BEGIN ADC_Init 0 */

		/* USER CODE END ADC_Init 0 */

		ADC_ChannelConfTypeDef sConfig = { 0 };

		/* USER CODE BEGIN ADC_Init 1 */

		/* USER CODE END ADC_Init 1 */

		/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
		*/
		hadc.Instance = ADC1;
		hadc.Init.OversamplingMode = DISABLE;
		hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
		hadc.Init.Resolution = ADC_RESOLUTION_12B;
		hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
		hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
		hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		hadc.Init.ContinuousConvMode = DISABLE;
		hadc.Init.DiscontinuousConvMode = DISABLE;
		hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
		hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		hadc.Init.DMAContinuousRequests = DISABLE;
		hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
		hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
		hadc.Init.LowPowerAutoWait = DISABLE;
		hadc.Init.LowPowerFrequencyMode = DISABLE;
		hadc.Init.LowPowerAutoPowerOff = DISABLE;
		if (HAL_ADC_Init(&hadc) != HAL_OK)
		{
			Error_Handler();
		}

		/** Configure for the selected ADC regular channel to be converted.
		*/
		sConfig.Channel = ADC_CHANNEL_0;
		sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
		if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN ADC_Init 2 */

		/* USER CODE END ADC_Init 2 */

	}

	/**
	  * @brief TIM2 Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_TIM2_Init(void)
	{

		/* USER CODE BEGIN TIM2_Init 0 */

		/* USER CODE END TIM2_Init 0 */

		TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
		TIM_MasterConfigTypeDef sMasterConfig = { 0 };
		TIM_IC_InitTypeDef sConfigIC = { 0 };

		/* USER CODE BEGIN TIM2_Init 1 */

		/* USER CODE END TIM2_Init 1 */
		htim2.Instance = TIM2;
		htim2.Init.Prescaler = 7;
		htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim2.Init.Period = 65535;
		htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
		{
			Error_Handler();
		}
		sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
		if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
		sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
		sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
		sConfigIC.ICFilter = 0;
		if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN TIM2_Init 2 */

		/* USER CODE END TIM2_Init 2 */

	}

	/**
	  * @brief TIM3 Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_TIM3_Init(void)
	{

		/* USER CODE BEGIN TIM3_Init 0 */

		/* USER CODE END TIM3_Init 0 */

		TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
		TIM_MasterConfigTypeDef sMasterConfig = { 0 };
		TIM_IC_InitTypeDef sConfigIC = { 0 };
		TIM_OC_InitTypeDef sConfigOC = { 0 };

		/* USER CODE BEGIN TIM3_Init 1 */

		/* USER CODE END TIM3_Init 1 */
		htim3.Instance = TIM3;
		htim3.Init.Prescaler = 7;
		htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim3.Init.Period = 65535;
		htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
		{
			Error_Handler();
		}
		sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
		if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
		sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
		sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
		sConfigIC.ICFilter = 0;
		if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIMEx_RemapConfig(&htim3, TIM3_TI1_GPIO) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = 0;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN TIM3_Init 2 */

		/* USER CODE END TIM3_Init 2 */
		HAL_TIM_MspPostInit(&htim3);

	}

	/**
	  * @brief TIM6 Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_TIM6_Init(void)
	{

		/* USER CODE BEGIN TIM6_Init 0 */

		/* USER CODE END TIM6_Init 0 */

		TIM_MasterConfigTypeDef sMasterConfig = { 0 };

		/* USER CODE BEGIN TIM6_Init 1 */

		/* USER CODE END TIM6_Init 1 */
		htim6.Instance = TIM6;
		htim6.Init.Prescaler = 7;
		htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim6.Init.Period = 65535;
		htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN TIM6_Init 2 */

		/* USER CODE END TIM6_Init 2 */

	}

	/**
	  * @brief TIM7 Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_TIM7_Init(void)
	{

		/* USER CODE BEGIN TIM7_Init 0 */

		/* USER CODE END TIM7_Init 0 */

		TIM_MasterConfigTypeDef sMasterConfig = { 0 };

		/* USER CODE BEGIN TIM7_Init 1 */

		/* USER CODE END TIM7_Init 1 */
		htim7.Instance = TIM7;
		htim7.Init.Prescaler = 799;
		htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim7.Init.Period = 9999;
		htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN TIM7_Init 2 */

		/* USER CODE END TIM7_Init 2 */

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
		huart2.Init.BaudRate = 9600;
		huart2.Init.WordLength = UART_WORDLENGTH_8B;
		huart2.Init.StopBits = UART_STOPBITS_1;
		huart2.Init.Parity = UART_PARITY_NONE;
		huart2.Init.Mode = UART_MODE_TX_RX;
		huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart2.Init.OverSampling = UART_OVERSAMPLING_16;
		huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
		huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		if (HAL_UART_Init(&huart2) != HAL_OK)
		{
			Error_Handler();
		}
		/* USER CODE BEGIN USART2_Init 2 */
		HW_VCOM_Init(&huart2);

		/* USER CODE END USART2_Init 2 */

	}

	/**
	  * @brief GPIO Initialization Function
	  * @param None
	  * @retval None
	  */
	static void MX_GPIO_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		/* USER CODE BEGIN MX_GPIO_Init_1 */
		/* USER CODE END MX_GPIO_Init_1 */

		  /* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

		/*Configure GPIO pin : USER_BUTTON_Pin */
		GPIO_InitStruct.Pin = USER_BUTTON_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

		/*Configure GPIO pin : USER_VIB_Pin */
		GPIO_InitStruct.Pin = USER_VIB_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(USER_VIB_GPIO_Port, &GPIO_InitStruct);

		/*Configure GPIO pin : PB6 */
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

		/* USER CODE BEGIN MX_GPIO_Init_2 */
			/* BSP Library */
		BSP_LED_Init(LED2);
		BSP_LED_Init(USER_LED);
		BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

		/* HAL
		GPIO_InitTypeDef GPIO_Init;
		GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Init.Pull = GPIO_PULLUP;
		GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_Init.Pin = GPIO_PIN_5;
		HAL_GPIO_Init(GPIOA, &GPIO_Init);
		*/
		/* USER CODE END MX_GPIO_Init_2 */
	}

	/* USER CODE BEGIN 4 */
	uint16_t HW_AdcReadChannel(uint32_t Channel)
	{

		ADC_ChannelConfTypeDef adcConf;
		uint16_t adcData = 0;

		/* wait the the Vrefint used by adc is set */
		while (__HAL_PWR_GET_FLAG(PWR_FLAG_VREFINTRDY) == RESET) {};

		__HAL_RCC_ADC1_CLK_ENABLE();

		/*calibrate ADC if any calibraiton hardware*/
		HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);

		/* Deselects all channels*/
		adcConf.Channel = ADC_CHANNEL_MASK;
		adcConf.Rank = ADC_RANK_NONE;
		HAL_ADC_ConfigChannel(&hadc, &adcConf);

		/* configure adc channel */
		adcConf.Channel = Channel;
		adcConf.Rank = ADC_RANK_CHANNEL_NUMBER;
		HAL_ADC_ConfigChannel(&hadc, &adcConf);

		/* Start the conversion process */
		HAL_ADC_Start(&hadc);

		/* Wait for the end of conversion */
		HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

		/* Get the converted value of regular channel */
		adcData = HAL_ADC_GetValue(&hadc);

		__HAL_ADC_DISABLE(&hadc);

		__HAL_RCC_ADC1_CLK_DISABLE();

		return adcData;
	}

	uint32_t HW_GetVRef(void)
	{
		uint16_t measuredLevel = 0;
		uint32_t batteryLevelmV;

		measuredLevel = HW_AdcReadChannel(ADC_CHANNEL_VREFINT);

		if (measuredLevel == 0)
		{
			batteryLevelmV = 0;
		}
		else
		{
			batteryLevelmV = (((uint32_t)VDDA_VREFINT_CAL * (*VREFINT_CAL)) / measuredLevel);
		}

		return batteryLevelmV;
	}

	float HW_Get_LM35_Temp(void)
	{
		uint32_t Vref = HW_GetVRef();
		uint16_t measuredLevel = HW_AdcReadChannel(ADC_CHANNEL_0);

		float temp = 0;
		temp = ((measuredLevel * Vref) / 40960);
		Printf("Celsius = %0.2f, Vref=%d, measuredA0=%d\r\n", temp, Vref, measuredLevel);

		return temp;
	}
	/* USER CODE END 4 */

	/**
	  * @brief  This function is executed in case of error occurrence.
	  * @retval None
	  */
	void Error_Handler(void)
	{
		/* USER CODE BEGIN Error_Handler_Debug */
		/* User can add his own implementation to report the HAL error return detect_state */
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
	void assert_failed(uint8_t * file, uint32_t line)
	{
		/* USER CODE BEGIN 6 */
		/* User can add his own implementation to report the file name and line number,
		   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
		   /* USER CODE END 6 */
	}
#endif /* USE_FULL_ASSERT */
