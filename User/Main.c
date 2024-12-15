/********************  ********************

To do 

modifier le p pour le baisser
coder min max



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
uint8_t flag_take_TH; 
uint8_t flag_display_dash_ext;

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
uint8_t last_time_ble;
float temp_out =0;
float hum_out = 0;
int main(void)
{
	flag_take_TH=0;
	flag_display_dash_ext=0;
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
  fifo_init(&blueRec_fifo, MAX_PACKET_LENGTH*2, blueRec_buffer, 1);
  RADIO_Init(NULL, ENABLE);
  HAL_VTIMER_Init(&VTIMER_InitStruct);
  HAL_RADIO_SetNetworkID(BLE_ADV_ACCESS_ADDRESS); /* 0x8E89BED6 */
  HAL_RADIO_ReceivePacket(channel, delay, receivedData, timeOut, RxCallback);

	printf("Initialisation\r\n");
	
	Init_io();
	SdkEvalI2CInit(100000);
	printf("fin init i2c\r\n");	
	
  RTC_DateTimeType RTC_DateTime;  
	float temp_adc,temp,hum;;
	Screen_init();
	draw_weather();
	Screen_set_up();
	uint8_t message_sec, message_min;
	
	while(1) 
	{
		
		  while(fifo_size(&blueRec_fifo) !=0) {
      HAL_VTIMER_Tick();
      /* Get the length of the packet and the packet itself */
      fifo_get_var_len_item(&blueRec_fifo, &length, packet);

      /* Get the RSSI information */
      fifo_get(&blueRec_fifo, 4, (uint8_t*)&rssi_val);
      
      /* Get the timestamp */
      fifo_get(&blueRec_fifo, 4, (uint8_t*)&timestamp);
      timestamp = (uint32_t) (timestamp/410); //convert in ms
      
     
       if(packet[14] == 0x4d & packet[15] == 0x65 & packet[16] == 0x74 & packet[17] == 0x65 & length >15){ //Message from Befc
					RTC_GetTimeDate(&RTC_DateTime);
					if( (RTC_DateTime.Second - message_sec > 3) & (RTC_DateTime.Minute == message_min) ||  RTC_DateTime.Minute != message_min ){
					//reset artefact
					message_min = RTC_DateTime.Minute;
					message_sec = RTC_DateTime.Second;
				  Rectf(45+160,105,10,30,blue);
					Rectf(161,105,45,30,black);
					Rectf(161,105+30,45+20,130,black);
					temp_adc = ((packet[24]/10.0+packet[25]/100.0+packet[26]/1000.0)*225)-100;
					draw_baterrie_level((uint8_t)temp_adc);
					
					last_time_ble = RTC_DateTime.Minute;
					temp_out = (float)((float)(packet[18]*100+packet[19]*10+packet[20])/10);
					hum_out = (float)((float)(packet[21]*100+packet[22]*10+packet[23])/10);
				 	draw_temp_out(temp_out);
					draw_hum_out(hum_out);
					draw_reseau(rssi_val);
					}
			}
		}
		if(flag_take_TH == 1){
			SHT4_Take_Data(&temp,&hum);		
			draw_hum_in(hum);
			draw_temp_in(temp);		
			flag_take_TH = 0;		
		}

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
