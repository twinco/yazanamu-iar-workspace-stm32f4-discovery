/**
  ******************************************************************************
  * @file    test03/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include <stdio.h>

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
#define STDIO1 device=USART1_sendchar
#define STDIO2 device=GLCD_sendchar

#define LED_GREEN_ON 	GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define LED_ORANGE_ON 	GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define LED_RED_ON 		GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define LED_BLUE_ON 	GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define LED_GREEN_OFF 	GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define LED_ORANGE_OFF 	GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define LED_RED_OFF 	GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define LED_BLUE_OFF 	GPIO_ResetBits(GPIOD,GPIO_Pin_15)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

int (*device)(unsigned char ch);    //함수포인터 선언

int GLCD_sendchar(unsigned char ch)
{ 
        GLCD_displayChar(xref_line, yref_column, ch);  
        yref_column -= 16;                             
        return 0;
}
int USART1_sendchar(unsigned char ch)
{
        USART_SendData(USART1, (uint8_t)ch);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};
        return 0;
}
int USART1_getchar(void)
{
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){};
        return USART_ReceiveData(USART1);
}
//입.출력 재설정
==============================================================================
int fputc(int ch, FILE *f) { return (device(ch)); }
int fgetc(FILE *f){ return (USART1_getchar()); }
==============================================================================

/*
 * Name   : RCC_Configuration
 * Input  : None
 * Output : None
 * Return : None
 */
void RCC_Configuration(void)
{
//    SystemInit();
    /* Enable GPIOA clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Enable GPIOB clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Enable GPIOC clock */
//    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    /* Enable GPIOD clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable USART3 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    /* Enable AFIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    /* Enable DMA1 clock */
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

  RCC_Configuration();

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  while (1)
  {
	LED_BLUE_ON;
	LED_RED_ON;
	LED_ORANGE_ON;
	LED_GREEN_ON;
    /* Insert delay */
    Delay(0x3FFFFF);

	LED_BLUE_OFF;
	LED_RED_OFF;
	LED_ORANGE_OFF;
	LED_GREEN_OFF;    
    /* Insert delay */
    Delay(0x3FFFFF);
	//printf("Hey Hey\r\n");
  }
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
