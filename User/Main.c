
/******************** (C) COPYRIGHT 2022 BeFC ********************
* File Name          : Empty_project/User/Main.c 
* Author             : Zeus 
* Version            : V1.1.0
* Date               : July-2022
* Description        : Template use to begin a project
********************************************************************************
* THE PRESENT FIRMWARE IS FOR INTERNAL BeFC USE ONLY
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_BeFC_Lib.h"
#include "Screen.h"
#include "BlueNRG_Interface_Lib.h"
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint8_t validate_press;
int value_press;
uint8_t minute_set;
uint8_t hour_set;
uint8_t day_set;
uint8_t day_week_set;
uint8_t mouth_set;

int main(void)
{

  /* System initialization function */
  SystemInit();
  
  /* Identify BlueNRG1 platform */
  SdkEvalIdentification();
		
	
	/*Init Clock*/
	Clock_Init() ;
	

  SdkEvalComUartInit(UART_BAUDRATE);
	/* USE the UART debug*/

	printf("Initialisation\r\n");
	
	Init_io();
	Screen_init();
	Screen_set_up();
	
	 while(1) 
		{
	
		}
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
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

/**
  * @}
  */

/******************* (C) COPYRIGHT 2022 BeFC *****END OF FILE****/
