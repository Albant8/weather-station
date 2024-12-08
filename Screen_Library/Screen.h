#include "clock.h"
#include "SDK_EVAL_SPI.h"
#include "dot.h"
#include "c_round.h"
#include "%.h"


#define LED   GPIO_Pin_4    

#define SPI_MOSI GPIO_Pin_2
#define SPI_MISO GPIO_Pin_3
#define SPI_CLK GPIO_Pin_0
#define CS GPIO_Pin_1
#define Reset GPIO_Pin_6
#define RS GPIO_Pin_14

#define white   0xFFFF
#define red		  0xF800
#define green   0x07E0
#define blue    0x001F
#define yellow  0xffe0
#define cyan    0x07FF
#define magenta 0xf81f
#define black   0

#define letter_WD1_x 18
#define letter_WD2_x 38
#define letter_WD3_x 58
#define letter_WD_y  5

#define digit_D1_x 27
#define digit_D2_x 47
#define digit_D_y 35

#define digit_M1_x 8
#define digit_M2_x 28
#define digit_M3_x 48
#define digit_M4_x 68
#define digit_M_y  69

#define digit_H1_x 90
#define digit_H2_x 144
#define digit_Min1_x 207
#define digit_Min2_x 261
#define digit_H_Min_y  5


#define digit_Tin_1_x 5
#define digit_Tin_2_x 45
#define digit_Tin_3_x 90
#define digit_Tin_y 145

#define digit_Hin_1_x 5
#define digit_Hin_2_x 45
#define digit_Hin_3_x 90
#define digit_Hin_y 220

#define digit_Tout_1_x 5+160
#define digit_Tout_2_x 45+160
#define digit_Tout_3_x 90+160
#define digit_Tout_y 145

#define digit_Hout_1_x 5+160
#define digit_Hout_2_x 45+160
#define digit_Hout_3_x 90+160
#define digit_Hout_y 220



void Screen_init(void);
void LCD_Clear(unsigned int j);
void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
void draw(unsigned int x,unsigned int y,unsigned int w,unsigned int h,uint8_t figure[]);

void draw_digit_35 (uint8_t value, unsigned int x,unsigned int y,unsigned int color);
void draw_week_day(uint8_t week_day);
void draw_day(uint8_t day);
void draw_mouth(uint8_t mouth);
void draw_hour(uint8_t hour);
void draw_minute(uint8_t minute);
void draw_year(int year);
void Screen_set_up(void);
void draw_reseau (uint8_t signal);
void draw_temp_in(float temp_in);
void draw_hum_in(float hum_in);
void draw_temp_out(float temp_out);
void draw_hum_out(float hum_out);
void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);

