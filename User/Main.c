/********************  ********************

To do 

changer police mar mer jeu ven sam dim janv	....
affichr des -- quand le capteur dehors n'a rien envoyer
coder min max
ajouter dessin météo
ajouter capteur I2C
ajouter si pas de message recu en 10 min afficher --


*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_BeFC_Lib.h"
#include "Screen.h"
#include "BlueNRG_Interface_Lib.h"
#include "SHT4.h"
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
	SdkEvalI2CInit(100000);
	printf("fin init i2c\r\n");	
	
	/*uint8_t ret[2];
	I2C_Read(0x10, 0, 1, ret, 2);*/
	
	Screen_init();
	Screen_set_up();
	float temp,hum;
	while(1) 
	{
		Clock_Wait(10000);
		SHT4_Take_Data(&temp,&hum);		
		draw_hum_in(hum);
		draw_temp_in(temp);
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
