/********************  ********************

To do 


ajouter le ble
ajouter si pas de message recu en 10 min afficher --
print force du signal et temp hum ext
changer police mar mer jeu ven sam dim janv	....
coder min max
ajouter dessin météo
ajouter capteur I2C



*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_BeFC_Lib.h"
#include "Screen.h"
#include "BlueNRG_Interface_Lib.h"
#include "SHT4.h"
#include "hal_radio.h"
#include "osal.h"
#include "fifo.h"
#include "vtimer.h"
#include "clock.h"


uint8_t validate_press;
int value_press;
uint8_t minute_set;
uint8_t hour_set;
uint8_t day_set;
uint8_t day_week_set;
uint8_t mouth_set;

#define BLE_ADV_ACCESS_ADDRESS  (uint32_t)(0x8E89BED6)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Blue FIFO */
circular_fifo_t blueRec_fifo;
uint8_t blueRec_buffer[MAX_PACKET_LENGTH*2+MAX_PACKET_LENGTH];


uint8_t receivedData[MAX_PACKET_LENGTH];

uint32_t delay =1000;
uint8_t channel = 39;                    
uint32_t timeOut = 100000;
int32_t rssi_val = 0;
uint32_t timestamp = 0;


uint8_t nullfunction(ActionPacket* p,  ActionPacket* next)
{
  return TRUE;
}


uint8_t RxCallback(ActionPacket* p, ActionPacket* next)
{
  if( (p->status & IRQ_DONE) != 0) {
    
    /* received a packet */
    if( (p->status & BIT_TX_MODE) == 0) {
      
      if((p->status & IRQ_RCV_OK) != 0) {
        /* Check if there is enough space in the FIFO to store the incoming data */
        if(MAX_PACKET_LENGTH*2 - fifo_size(&blueRec_fifo) > (p->data[1]+ 4 + 4 + 4)){
          fifo_put_var_len_item(&blueRec_fifo, p->data[1]+2, p->data);
          fifo_put(&blueRec_fifo, 4, (uint8_t*)(&p->rssi));
          fifo_put(&blueRec_fifo, 4, (uint8_t*)(&p->timestamp_receive));
        }
          HAL_RADIO_ReceivePacket(channel, delay, receivedData, timeOut, RxCallback);
      }
      else if((p->status & IRQ_TIMEOUT) != 0) {
        HAL_RADIO_ReceivePacket(channel,delay, receivedData, timeOut, RxCallback);
      }
      else if((p->status & IRQ_CRC_ERR) != 0) {
        HAL_RADIO_ReceivePacket(channel, delay, receivedData, timeOut, RxCallback);
      }
    }
    
    /* Transmit complete */ 
    else {
    }
  }
  return TRUE;
}

int main(void)
{
  uint8_t packet[MAX_PACKET_LENGTH];
	HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};

  uint16_t length;
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
	//Screen_set_up();
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
