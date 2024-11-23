/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_Interface_Lib.h"

int I2C_Transmit(uint8_t i2c_address, uint8_t *i2c_transmit_buf,uint8_t i2c_transmit_buf_size){
  I2C_TransactionType t;
  
  /* Write the slave address */
  t.Operation = I2C_Operation_Write;
  t.Address = i2c_address;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length =i2c_transmit_buf_size ;
  
  /* Flush the slave address */
  I2C_FlushTx((I2C_Type*)SDK_EVAL_I2C);
  while (I2C_WaitFlushTx((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ONGOING);
  
  /* Begin transaction */
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);

  /* Fill TX FIFO with data to write */
	for(uint8_t i=0; i<i2c_transmit_buf_size;i++) {
		I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, i2c_transmit_buf[i]);
		while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_TXFF)== SET);
	}
  
   /* Wait loop */
  do {
    if(I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ABORTED)
      return 1;
   
  } while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD) == RESET);
    
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);
  


  return BlueNRG_transmition_OK;

}





int I2C_Receive(uint8_t i2c_address, uint8_t *i2c_receive_buf,uint8_t i2c_receive_buf_size){

 I2C_TransactionType t;
 
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS);
  
  /* read data */
  t.Operation = I2C_Operation_Read;
  t.Address = i2c_address;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length = i2c_receive_buf_size;  
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);
  
  /* Wait loop */
  do {
    if(I2C_OP_ABORTED == I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C))
      return 1;
    
  } while (RESET == I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD));
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);
  
  /* Get data from RX FIFO */
  while(i2c_receive_buf_size--) {
    *i2c_receive_buf = I2C_ReceiveData((I2C_Type*)SDK_EVAL_I2C);
    i2c_receive_buf ++;
  }
  
  return BlueNRG_transmition_OK;
  
}


int I2C_Read(uint16_t DevAddress, uint16_t MemAddress,uint8_t size_MemAddress  , uint8_t *pData, uint16_t Size)
{
	I2C_TransactionType t;

	/* Write the slave address */
	t.Operation = I2C_Operation_Write;
	t.Address = DevAddress;
	t.StartByte = I2C_StartByte_Disable;
	t.AddressType = I2C_AddressType_7Bit;
	t.StopCondition = I2C_StopCondition_Disable;
	t.Length = 2;

	/* Flush the slave address */
	I2C_FlushTx((I2C_Type*)SDK_EVAL_I2C);
	while (I2C_WaitFlushTx((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ONGOING);

	/* Begin transaction */
	I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);

   if(size_MemAddress == 1){
     I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, (uint8_t)(MemAddress));
   }
  else if(size_MemAddress == 2){
    /* Fill TX FIFO with data to write */
    I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, (uint8_t)(MemAddress>> 8));
    I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, (uint8_t)(MemAddress& 0xff));
  }
  
  else{
      return 1;
  }
	/* Wait loop */
	do {
		if(I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ABORTED)
			return 1;

	} while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS) == RESET);

	/* Clear pending bits */
	I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS);

	/* read data */
	t.Operation = I2C_Operation_Read;
	t.Address = DevAddress;
	t.StartByte = I2C_StartByte_Disable;
	t.AddressType = I2C_AddressType_7Bit;
	t.StopCondition = I2C_StopCondition_Enable;
	t.Length = Size;
	I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);

	/* Wait loop */
	do {
		if(I2C_OP_ABORTED == I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C))
			return 1;

	} while (RESET == I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD));

	/* Clear pending bits */
	I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);

	/* Get data from RX FIFO */
	while(Size--) {
		*pData = I2C_ReceiveData((I2C_Type*)SDK_EVAL_I2C);
		pData ++;
		
	}

	return 0;
}



void GPIO_Init_Lib(uint32_t GPIO_pin,uint8_t GPIO_port, uint8_t GPIO_Type){
  GPIO_InitType GPIO_InitStructure;
  
  /* Enable the GPIO Clock */
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);
  
  /* Configure GPIO as NFC enable */
  GPIO_InitStructure.GPIO_Pin = GPIO_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Type;
  GPIO_InitStructure.GPIO_Pull = ENABLE;
  GPIO_InitStructure.GPIO_HighPwr = ENABLE;
  GPIO_Init(&GPIO_InitStructure);
}

void GPIO_Write( uint32_t GPIO_pin,uint8_t GPIO_port,uint8_t GPIO_STATUS){
  
  if(GPIO_STATUS == 1){  
    GPIO_WriteBit(GPIO_pin,Bit_SET);
  }
  if(GPIO_STATUS == 0){  
    GPIO_WriteBit(GPIO_pin,Bit_RESET);
  }
}

void Wait(uint32_t time_to_wait_in_ms){
    Clock_Wait(time_to_wait_in_ms);
}
  
void Init_io(void){
  /* Enable the GPIO Clock */
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);
  GPIO_InitType GPIO_InitStructure;

  /* Configure the push buttons */
  GPIO_InitStructure.GPIO_Pin = Get_ButtonGpioPin(BUTTON_1) | Get_ButtonGpioPin(BUTTON_2);
  GPIO_InitStructure.GPIO_Mode = GPIO_Input;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init(&GPIO_InitStructure);
  
  /* Set the GPIO interrupt priority and enable it */
  NVIC_InitType NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = GPIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Configures EXTI line for BUTTON_1 */
  GPIO_EXTIConfigType GPIO_EXTIStructure;
  GPIO_EXTIStructure.GPIO_Pin = Get_ButtonGpioPin(BUTTON_1);
  GPIO_EXTIStructure.GPIO_IrqSense = GPIO_IrqSense_Edge;
  GPIO_EXTIStructure.GPIO_Event = IRQ_ON_FALLING_EDGE;
  GPIO_EXTIConfig(&GPIO_EXTIStructure);

  /* Configures EXTI line for BUTTON_2 */
  GPIO_EXTIStructure.GPIO_Pin = Get_ButtonGpioPin(BUTTON_2);
  GPIO_EXTIStructure.GPIO_Event = IRQ_ON_FALLING_EDGE;
  GPIO_EXTIConfig(&GPIO_EXTIStructure);
  
  /* Clear pending interrupt */
  GPIO_ClearITPendingBit(Get_ButtonGpioPin(BUTTON_1) | Get_ButtonGpioPin(BUTTON_2));
  
  /* Enable the interrupt */
  GPIO_EXTICmd(Get_ButtonGpioPin(BUTTON_1) | Get_ButtonGpioPin(BUTTON_2), ENABLE);
}

/* last line*/


