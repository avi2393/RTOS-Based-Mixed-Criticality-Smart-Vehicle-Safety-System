/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define OBSTACLE_BIT   (1 << 0)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
uint32_t last_cycles = 0;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BreakTask */
osThreadId_t BreakTaskHandle;
const osThreadAttr_t BreakTask_attributes = {
  .name = "BreakTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for IRSensor */
osThreadId_t IRSensorHandle;
const osThreadAttr_t IRSensor_attributes = {
  .name = "IRSensor",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for MonitorTask */
osThreadId_t MonitorTaskHandle;
const osThreadAttr_t MonitorTask_attributes = {
  .name = "MonitorTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for LoggingTask */
osThreadId_t LoggingTaskHandle;
const osThreadAttr_t LoggingTask_attributes = {
  .name = "LoggingTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow7,
};
/* Definitions for uartMutex */
osMutexId_t uartMutexHandle;
const osMutexAttr_t uartMutex_attributes = {
  .name = "uartMutex"
};
/* Definitions for systemEvents */
osEventFlagsId_t systemEventsHandle;
const osEventFlagsAttr_t systemEvents_attributes = {
  .name = "systemEvents"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void *argument);
void Start_Break_Task(void *argument);
void Start_IRSensor_Task(void *argument);
void Start_Motor_Task(void *argument);
void Start_Monitor_Task(void *argument);
void Start_Logging_Task(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

volatile uint32_t idle_counter = 0;
volatile uint8_t stress_request = 0;

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of uartMutex */
  uartMutexHandle = osMutexNew(&uartMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  systemEventsHandle = osEventFlagsNew(&systemEvents_attributes);

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of BreakTask */
  BreakTaskHandle = osThreadNew(Start_Break_Task, NULL, &BreakTask_attributes);

  /* creation of IRSensor */
  IRSensorHandle = osThreadNew(Start_IRSensor_Task, NULL, &IRSensor_attributes);

  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(Start_Motor_Task, NULL, &MotorTask_attributes);

  /* creation of MonitorTask */
  MonitorTaskHandle = osThreadNew(Start_Monitor_Task, NULL, &MonitorTask_attributes);

  /* creation of LoggingTask */
  LoggingTaskHandle = osThreadNew(Start_Logging_Task, NULL, &LoggingTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of systemEvents */
 // systemEventsHandle = osEventFlagsNew(&systemEvents_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|Dc_motar_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin Dc_motar_Pin */
  GPIO_InitStruct.Pin = LED_Pin|Dc_motar_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IRF_Pin */
  GPIO_InitStruct.Pin = IRF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(IRF_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Buzzer_Pin */
  GPIO_InitStruct.Pin = Buzzer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Buzzer_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void StressTask(void *arg)
{


	 printf("stress thread\r\n");
	 volatile float x = 1.0;

	    while(1)
	    {
	        for(int i = 0; i < 500000; i++)
	        {
	            x = x * 1.0001f;
	        }

	        osDelay(1);
	    }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	  for(;;)
	  {
		//HAL_GPIO_TogglePin(GPIOA, LED_Pin);
	    osDelay(500);
	  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Start_Break_Task */
/**
* @brief Function implementing the BreakTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Break_Task */
void Start_Break_Task(void *argument)
{
  /* USER CODE BEGIN Start_Break_Task */
  /* Infinite loop */
	static uint8_t brake_active = 0;

	 for(;;)
	  {
	      if (osEventFlagsGet(systemEventsHandle) & OBSTACLE_BIT)
	      {
	          //  OBSTACLE DETECTED
	          HAL_GPIO_WritePin(GPIOA, Dc_motar_Pin, GPIO_PIN_RESET); // motor OFF
	          HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_SET);     // buzzer ON
	      }
	      else
	      {
	          //  SAFE CONDITION
	          HAL_GPIO_WritePin(GPIOA, Dc_motar_Pin, GPIO_PIN_SET);   // motor ON
	          HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_RESET);   // buzzer OFF
	      }

	      osDelay(50);
	  }
  /* USER CODE END Start_Break_Task */
}

/* USER CODE BEGIN Header_Start_IRSensor_Task */
/**
* @brief Function implementing the IRSensor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_IRSensor_Task */
void Start_IRSensor_Task(void *argument)
{
  /* USER CODE BEGIN Start_IRSensor_Task */
  /* Infinite loop */
	for(;;)
	{
	    if (HAL_GPIO_ReadPin(IRF_GPIO_Port, IRF_Pin) == GPIO_PIN_RESET) // obstacle
	    {
	        osEventFlagsSet(systemEventsHandle, OBSTACLE_BIT);
	    }
	    else
	    {
	        osEventFlagsClear(systemEventsHandle, OBSTACLE_BIT);
	    }

	    osDelay(50);
	}
  /* USER CODE END Start_IRSensor_Task */
}

/* USER CODE BEGIN Header_Start_Motor_Task */
/**
* @brief Function implementing the MotorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Motor_Task */
void Start_Motor_Task(void *argument)
{
  /* USER CODE BEGIN Start_Motor_Task */
  /* Infinite loop */

	  for(;;)
	  {
	  //  HAL_GPIO_WritePin(GPIOA, Dc_motar_Pin, GPIO_PIN_SET); // motor ON
	    osDelay(20);
	  }

  /* USER CODE END Start_Motor_Task */
}

/* USER CODE BEGIN Header_Start_Monitor_Task */
/**
* @brief Function implementing the MonitorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Monitor_Task */
void Start_Monitor_Task(void *argument)
{
  /* USER CODE BEGIN Start_Monitor_Task */

	    static uint8_t critical_mode = 0;
	    static uint8_t critical_printed = 0;
	    static uint8_t initialized = 0;

	    static uint32_t max_idle = 0;

	    for(;;)
	    {

	    	 if (stress_request)
	    		    {
	    		        stress_request = 0;

	    		        osThreadAttr_t stress_attr = {.priority = osPriorityAboveNormal};

	    		        osThreadNew(StressTask, NULL, &stress_attr);

	    		        osMutexAcquire(uartMutexHandle, osWaitForever);
	    		        printf("Stress Task Started\r\n");
	    		        osMutexRelease(uartMutexHandle);
	    		    }

	        //  FIRST TIME → CALIBRATION (system idle reference)
	        if (!initialized)
	        {
	            idle_counter = 0;

	            osDelay(2000);   // allow system to stabilize

	            max_idle = idle_counter;   // store max idle
	            initialized = 1;

	            osMutexAcquire(uartMutexHandle, osWaitForever);
	            printf("Calibration Done: %lu\r\n", max_idle);
	            osMutexRelease(uartMutexHandle);

	            continue;  // skip first measurement
	        }

	        //  NORMAL MEASUREMENT WINDOW
	        idle_counter = 0;

	        osDelay(1000);

	        uint32_t current_idle = idle_counter;

	        //  CPU LOAD CALCULATION
	        float cpu = 100.0f - ((float)current_idle / max_idle) * 100.0f;

	        if (cpu > 100) cpu = 100;
	        if (cpu < 0) cpu = 0;

	        //  ENTER CRITICAL MODE
	        if (!critical_mode && cpu > 80.0f)
	        {
	            critical_mode = 1;
	        }

	        //  PRINT ONLY ONCE
	        if (critical_mode && !critical_printed)
	        {
	            critical_printed = 1;

	            osMutexAcquire(uartMutexHandle, osWaitForever);
	            printf("\r\n===== CRITICAL MODE =====\r\n");
	            printf("CPU = %d%%\r\n", (int)cpu);
	            printf("Critical Tasks Running: IR, Brake, Motor\r\n");
	            printf("Non-Critical Tasks Stopped: Logging, LED\r\n");
	            osMutexRelease(uartMutexHandle);

	            osThreadSuspend(LoggingTaskHandle);
	        }

	        //  NORMAL MODE PRINT
	        if (!critical_mode)
	        {
	            osMutexAcquire(uartMutexHandle, osWaitForever);

	            if (osEventFlagsGet(systemEventsHandle) & OBSTACLE_BIT)
	                printf("System Running | Obstacle Detected | CPU = %d%%\r\n", (int)cpu);
	            else
	                printf("System Running | No Obstacle | CPU = %d%%\r\n", (int)cpu);

	            osMutexRelease(uartMutexHandle);
	        }
	        else
	        {
	            //  critical mode LED indication
	            HAL_GPIO_TogglePin(GPIOA, LED_Pin);
	        }
	    }



  /* USER CODE END Start_Monitor_Task */
}

/* USER CODE BEGIN Header_Start_Logging_Task */
/**
* @brief Function implementing the LoggingTask thread.
* @param argument: Not used
* @retval None
/* USER CODE END Header_Start_Logging_Task */
void Start_Logging_Task(void *argument)
{
  /* USER CODE BEGIN Start_Logging_Task */
  /* Infinite loop */
	 for(;;)
	  {
	    osMutexAcquire(uartMutexHandle, osWaitForever);
	    printf("LOG\r\n");
	    osMutexRelease(uartMutexHandle);

	    osDelay(1000);
	  }

  /* USER CODE END Start_Logging_Task */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 if (GPIO_Pin == GPIO_PIN_13)
	    {
	        stress_request = 1;
	    }
}
/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
