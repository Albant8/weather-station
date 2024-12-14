#include "SHT4.h"

int SHT4_I2C_Write(uint8_t *pData)
{
  I2C_TransactionType t;
  
  /* Write the slave address */
  t.Operation = I2C_Operation_Write;
  t.Address = SHT4_Adress;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length = 1;
  
  /* Flush the slave address */
  I2C_FlushTx((I2C_Type*)SDK_EVAL_I2C);
  while (I2C_WaitFlushTx((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ONGOING);
  
  /* Begin transaction */
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);

  /* Fill TX FIFO with data to write */
  I2C_FillTxFIFO((I2C_Type*)SDK_EVAL_I2C, *pData);
  /* Wait loop */
  do {
    if(I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C) == I2C_OP_ABORTED)
      return 1;
   
  } while (I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD) == RESET);
    
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);

  return SHT4_OK;

}


int SHT4_I2C_Read(uint8_t* pBuffer,  uint8_t NumByteToRead)
{
  I2C_TransactionType t;
 
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTDWS);
  
  /* read data */
  t.Operation = I2C_Operation_Read;
  t.Address = SHT4_Adress;
  t.StartByte = I2C_StartByte_Disable;
  t.AddressType = I2C_AddressType_7Bit;
  t.StopCondition = I2C_StopCondition_Enable;
  t.Length = NumByteToRead;  
  I2C_BeginTransaction((I2C_Type*)SDK_EVAL_I2C, &t);
  
  /* Wait loop */
  do {
    if(I2C_OP_ABORTED == I2C_GetStatus((I2C_Type*)SDK_EVAL_I2C))
      return 1;
    
  } while (RESET == I2C_GetITStatus((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD));
  
  /* Clear pending bits */
  I2C_ClearITPendingBit((I2C_Type*)SDK_EVAL_I2C, I2C_IT_MTD | I2C_IT_MTDWS);
  
  /* Get data from RX FIFO */
  while(NumByteToRead--) {
    *pBuffer = I2C_ReceiveData((I2C_Type*)SDK_EVAL_I2C);
    pBuffer ++;
  }
  
  return SHT4_OK;
}


/**
  * @brief  Take measurement of temperature and humidity and put the sensor on sleep mode
  * @param  Temperature and Humidity Pointer to data buffer where the data is
  * @retval HAL status
  */
void SHT4_Take_Measurement(uint8_t *pBuffer){

	uint8_t tx_bytes[1]={0xFD};
	SHT4_I2C_Write(tx_bytes);
	Clock_Wait(20);
	SHT4_I2C_Read(pBuffer, 6);

}

/**
  * @brief  Take the data converted
  * @param  Temperature and Humidity float Pointer
  * @retval HAL status
  */
void SHT4_Take_Data(float* temperature,float* humidity){
	uint8_t value[6];
	SHT4_Take_Measurement(value);
	int temp = value[0]*256 + value[1];
	int rh = value[3]*256 + value[4];
	temperature[0] = 175*temp/65535.0-45;
	humidity[0] = 125*rh/65535.0-6;	
}
