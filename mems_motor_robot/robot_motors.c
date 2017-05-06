/**
  ******************************************************************************
  * @file    BSP/Src/mems.c 
  * @author  MCD Application Team
  * @version V1.2.7
  * @date    04-November-2016
  * @brief   This example code shows how to use MEMS features.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "mems.h"
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t UserPressButton;

/* Init af threshold to detect acceleration on MEMS */
/* Typical value: 
      - No  acceleration: X, Y inferior to 100 (positive or negative)
      - Max acceleration: X, Y around 2000 (positive or negative) */
int16_t ThresholdHigh = 200;
int16_t ThresholdLow = -200;
int16_t High = 600;
int16_t Low = -600;

/* Private function prototypes -----------------------------------------------*/
static void ACCELERO_ReadAcc(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Test ACCELERATOR MEMS Hardware.
  *         The main objective of this test is to check acceleration on 2 axes X and Y
  * @param  None
  * @retval None
  */
void ACCELERO_MEMS_Test(void)
{
  /* Init Accelerometer MEMS */
  if(BSP_ACCELERO_Init() != ACCELERO_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  UserPressButton = 0;
 // while(!UserPressButton)
  {
    ACCELERO_ReadAcc();
  }
}

/**
  * @brief  Read Acceleration data.
  * @param  None
  * @retval None
  */
/****************************************************************************************************/
/* 
static __IO uint32_t sysTickCounter;
 
void SysTick_Init(void) {
//	 *SystemFrequency/1000      1ms         *
//	 *SystemFrequency/100000    10us        *
//	 *SystemFrequency/1000000   1us         *
	while (SysTick_Config(SystemCoreClock / 1000000) != 0) {
	} // One SysTick interrupt now equals 1us
 
}
 

void TimeTick_Decrement(void) {
	if (sysTickCounter != 0x00) {
		sysTickCounter--;
	}
}
 
void delay_nus(uint32_t n) {
	sysTickCounter = n;
	while (sysTickCounter != 0) {
	}
}
 
void delay_1ms(void) {
	sysTickCounter = 1000;
	while (sysTickCounter != 0) {
	}
}
 
void delay_nms(uint32_t n) {
	while (n--) {
		delay_1ms();
	}
}


void SysTick_Handler(void) {
	TimeTick_Decrement();
}

*/
/*****************************************************************************************************/

//HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET);
static void ACCELERO_ReadAcc(void)
{
  /* Accelerometer variables */
  int16_t buf0[3] = {0};
	int16_t buf1[3] = {0};
  int16_t dx,dy,x0_value, y0_value,x1_value, y1_value = 0x00;
	
	
  /* Read Acceleration */
  BSP_ACCELERO_GetXYZ(buffer);
  x0_value = buf0[0];
  y0_value = buf0[1];
	
  if((ABS(x0_value))>(ABS(y0_value)))
  {
   if(x0_value > ThresholdHigh )
  { 
			BSP_LED_On(LED5);
			HAL_Delay(1);
			BSP_LED_Off(LED5);
			HAL_Delay(19);
    }
    else if(x0_value < ThresholdLow)
    { 
			BSP_LED_On(LED5);
			HAL_Delay(0);
			BSP_LED_Off(LED5);
			HAL_Delay(20);
    }
    else
    { 
      HAL_Delay(10);
    }
  }
  else
  {
    if(y0_value < ThresholdLow)
    {
			BSP_LED_On(LED3);
			HAL_Delay(0);
			BSP_LED_Off(LED3);
			HAL_Delay(20);
    }
    else if(y0_value > ThresholdHigh)
    {
			BSP_LED_On(LED3);
			HAL_Delay(1);
			BSP_LED_Off(LED3);
			HAL_Delay(19);
    } 
    else
    { 
      HAL_Delay(10);
    }
  } 
  
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
}
