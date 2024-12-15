#include <stdio.h>
#include <stdint.h>
#include "SDK_EVAL_I2C.h"
#include "clock.h"
#include <math.h>
#include "SHT4.h"


#define LPS22hh_Adress 0x5D

#define LPS22hh_OK 0

int LPS22hh_I2C_Write(uint8_t i2c_register, uint8_t value);
int LPS22hh_I2C_Read(uint8_t i2c_register, uint8_t* pBuffer, uint8_t NumByteToRead);
float LPS22hh_Take_Measurement(void);
