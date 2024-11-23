#include "BlueNRG1_gpio.h"
#include "SDK_EVAL_I2C.h"
#include <stdio.h>
#include "clock.h"

#define I2C_Stop           I2C_StopCondition_Enable       
#define I2C_No_Stop     I2C_StopCondition_Disable        

#define GPIO_SET        Bit_SET
#define GPIO_RESET    Bit_RESET

#define GPIO_NFC_pin     GPIO_Pin_0
#define GPIO_NFC_port     0

#define BlueNRG_transmition_OK 0

int I2C_Transmit(uint8_t i2c_address, uint8_t *i2c_transmit_buf,uint8_t i2c_transmit_buf_size);
int I2C_Receive(uint8_t i2c_address, uint8_t *i2c_receive_buf,uint8_t i2c_receive_buf_size);
int I2C_Read(uint16_t DevAddress, uint16_t MemAddress,uint8_t size_MemAddress  , uint8_t *pData, uint16_t Size);

void GPIO_Init_Lib(uint32_t GPIO_pin,uint8_t GPIO_port, uint8_t GPIO_Type);
void GPIO_Write( uint32_t GPIO_pin,uint8_t GPIO_port,uint8_t GPIO_STATUS);

void Wait(uint32_t time_to_wait_in_ms);

void Init_io(void);
