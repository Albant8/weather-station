#include <stdio.h>
#include <stdint.h>
#include "SDK_EVAL_I2C.h"
#include "clock.h"
#include <math.h>

#define SHT4_Adress 0x44

#define SHT4_OK 0

void SHT4_Take_Measurement(uint8_t *pBuffer);
void SHT4_Take_Data(float* temperature,float* humidity);
int SHT4_I2C_Write(uint8_t *pData);
int SHT4_I2C_Read(uint8_t* pBuffer,  uint8_t NumByteToRead);
