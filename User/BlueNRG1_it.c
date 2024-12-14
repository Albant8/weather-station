/**
  ******************************************************************************
  * @file    ADC/Polling/BlueNRG1_it.c  
  * @author  RF Application Team
  * @version V1.0.0
  * @date    September-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1_it.h"
#include "BlueNRG1_conf.h"
#include "SDK_EVAL_Config.h"
#include "clock.h"
#include "vtimer.h"
#include "Screen.h"
#include "BlueNRG_Interface_Lib.h"
#include "BlueNRG1_radio.h"
#include "SHT4.h"
/** @addtogroup BlueNRG1_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC Examples
  * @{
  */

/** @addtogroup ADC_Polling ADC Polling Example
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t validate_press;
extern int value_press;
extern uint8_t minute_set;
extern uint8_t hour_set;
extern uint8_t day_set;
extern uint8_t day_week_set;
extern uint8_t mouth_set;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles SVCall exception.
  */
void SVC_Handler(void)
{
}


/**
  * @brief  This function handles SysTick Handler.
  */
void SysTick_Handler(void)
{
  SysCount_Handler();
}


void Blue_Handler(void)
{
  RADIO_IRQHandler();
}



void GPIO_Handler(void)
{
  /* If BUTTON_1 is pressed  */
  if(GPIO_GetITPendingBit(Pin_Buton_Set) == SET) {
    GPIO_ClearITPendingBit(Pin_Buton_Set);
    value_press++;   
  }

  /* If BUTTON_2 is pressed  */
  if(GPIO_GetITPendingBit(Pin_Buton_Valid) == SET) {
    GPIO_ClearITPendingBit(Pin_Buton_Valid);
		validate_press++;
    
  }
}
uint8_t counter_double_dot=0;
extern uint8_t last_time_ble;
extern uint8_t flag_take_TH;
extern uint8_t flag_display_dash_ext;
void RTC_Handler(void)
{
  if(SET == RTC_IT_Status(RTC_IT_TIMER))
  {
		RTC_DateTimeType RTC_DateTime;
    /* Clear pending interrupt flag */ 
    RTC_IT_Clear(RTC_IT_TIMER);
        
    /* Read present date and time information */
    RTC_GetTimeDate(&RTC_DateTime);
		
		if(RTC_DateTime.Minute !=  minute_set){
			printf("IRQ mminute\r\n");
			draw_minute(RTC_DateTime.Minute);
			minute_set = RTC_DateTime.Minute;
			uint8_t value_compare = minute_set;
			printf("value_compare = %d last_time_ble = %d\r\n", value_compare, last_time_ble);
			flag_take_TH = 1;
			if(last_time_ble > 49){
					value_compare+=60;
			}
			if(value_compare - last_time_ble >10){
					draw_hum_out(100);
					draw_temp_out(100);
					last_time_ble =255;
			}
		}
		if(RTC_DateTime.Hour !=  hour_set){
			draw_hour(RTC_DateTime.Hour);
			hour_set = RTC_DateTime.Hour;
		}
		if(RTC_DateTime.WeekDay !=  day_week_set){
			draw_week_day(RTC_DateTime.WeekDay);
			day_week_set = RTC_DateTime.WeekDay;
		}
		if(RTC_DateTime.MonthDay !=  day_set){
			draw_day(RTC_DateTime.MonthDay);
			day_set = RTC_DateTime.MonthDay;
		}
		if(RTC_DateTime.Month !=  mouth_set){
			draw_mouth(RTC_DateTime.Month);
			mouth_set = RTC_DateTime.Month;
		}
		
		if(counter_double_dot > 0){
			counter_double_dot = 0;
			draw(dot_x, dot_y1,dot_size,dot_size,(uint8_t *)dot_figure_1);	
			draw(dot_x, dot_y2,dot_size,dot_size,(uint8_t *)dot_figure_1);
		}else{
			counter_double_dot++;
			Rectf(dot_x, dot_y1,dot_size,dot_size,black);
			Rectf(dot_x, dot_y2,dot_size,dot_size,black);
		}
		
  }
  

}


/******************************************************************************/
/*                 BlueNRG-1 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (system_bluenrg1.c).                                               */
/******************************************************************************/

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
