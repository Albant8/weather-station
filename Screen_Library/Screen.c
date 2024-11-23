#include "Screen.h"

void Lcd_Writ_Bus(unsigned char d)
{
  SPI_SendData(d);
	while (SET == SPI_GetFlagStatus(SPI_FLAG_BSY));
	
}

void Lcd_Write_Com(unsigned char VH)  
{   
  GPIO_ResetBits(RS);//LCD_RS=0;
	
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned char VH)
{
  GPIO_SetBits(RS);//LCD_RS=1;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned char dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}


void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  Lcd_Write_Com(0x2a);
	Lcd_Write_Data(x1>>8);
	Lcd_Write_Data((uint8_t)x1);
	Lcd_Write_Data(x2>>8);
	Lcd_Write_Data((uint8_t)x2);
  Lcd_Write_Com(0x2b);
	Lcd_Write_Data(y1>>8);
	Lcd_Write_Data((uint8_t)y1);
	Lcd_Write_Data(y2>>8);
	Lcd_Write_Data((uint8_t)y2);
	Lcd_Write_Com(0x2c); 							 
}

void SPI_init(void)
{
	SPI_InitType SPI_InitStructure;
  GPIO_InitType GPIO_InitStructure;
  
  /* Enable SPI and GPIO clocks */
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO | CLOCK_PERIPH_SPI, ENABLE);   
  
  /* Configure SPI pins */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = SPI_MOSI;
  GPIO_InitStructure.GPIO_Mode = Serial0_Mode;
  GPIO_InitStructure.GPIO_Pull = ENABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init(&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = SPI_MISO;
  GPIO_InitStructure.GPIO_Mode = Serial0_Mode;  
  GPIO_Init(&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = SPI_CLK;
  GPIO_InitStructure.GPIO_Mode = Serial0_Mode;
  GPIO_Init(&GPIO_InitStructure);  
  


SPI_StructInit(&SPI_InitStructure);
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b ;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_BaudRate = 32000000;
  SPI_Init(&SPI_InitStructure);
  
  /* Set null character */
  SPI_SetDummyCharacter(0xFF);
  
  /* Clear RX and TX FIFO */
  SPI_ClearTXFIFO();
  SPI_ClearRXFIFO();
  
  /* Enable SPI functionality */
  SPI_Cmd(ENABLE);  
}

void Lcd_Init(void)
{
  GPIO_SetBits(Reset);
  Clock_Wait(5); 
  GPIO_ResetBits(Reset);
  Clock_Wait(15);
  GPIO_SetBits(Reset);
  Clock_Wait(15);

  GPIO_ResetBits(CS);  //CS
//ST7796S
     Lcd_Write_Com(0xF0);
    Lcd_Write_Data(0xC3);
    Lcd_Write_Com(0xF0);
    Lcd_Write_Data(0x96);
    Lcd_Write_Com(0x36);
    Lcd_Write_Data(0x68);  
    Lcd_Write_Com(0x3A);
    Lcd_Write_Data(0x05);  
    Lcd_Write_Com(0xB0);
    Lcd_Write_Data(0x80);  
    Lcd_Write_Com(0xB6);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x02);  
    Lcd_Write_Com(0xB5);
    Lcd_Write_Data(0x02);
    Lcd_Write_Data(0x03);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x04);
    Lcd_Write_Com(0xB1);
    Lcd_Write_Data(0x80);  
    Lcd_Write_Data(0x10);  
    Lcd_Write_Com(0xB4);
    Lcd_Write_Data(0x00);
    Lcd_Write_Com(0xB7);
    Lcd_Write_Data(0xC6);
    Lcd_Write_Com(0xC5);
    Lcd_Write_Data(0x24);
    Lcd_Write_Com(0xE4);
    Lcd_Write_Data(0x31);
    Lcd_Write_Com(0xE8);
    Lcd_Write_Data(0x40);
    Lcd_Write_Data(0x8A);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x00);
    Lcd_Write_Data(0x29);
    Lcd_Write_Data(0x19);
    Lcd_Write_Data(0xA5);
    Lcd_Write_Data(0x33);
    Lcd_Write_Com(0xC2);
    Lcd_Write_Com(0xA7);
    
    Lcd_Write_Com(0xE0);
    Lcd_Write_Data(0xF0);
    Lcd_Write_Data(0x09);
    Lcd_Write_Data(0x13);
    Lcd_Write_Data(0x12);
    Lcd_Write_Data(0x12);
    Lcd_Write_Data(0x2B);
    Lcd_Write_Data(0x3C);
    Lcd_Write_Data(0x44);
    Lcd_Write_Data(0x4B);
    Lcd_Write_Data(0x1B);
    Lcd_Write_Data(0x18);
    Lcd_Write_Data(0x17);
    Lcd_Write_Data(0x1D);
    Lcd_Write_Data(0x21);
  
    Lcd_Write_Com(0XE1);
    Lcd_Write_Data(0xF0);
    Lcd_Write_Data(0x09);
    Lcd_Write_Data(0x13);
    Lcd_Write_Data(0x0C);
    Lcd_Write_Data(0x0D);
    Lcd_Write_Data(0x27);
    Lcd_Write_Data(0x3B);
    Lcd_Write_Data(0x44);
    Lcd_Write_Data(0x4D);
    Lcd_Write_Data(0x0B);
    Lcd_Write_Data(0x17);
    Lcd_Write_Data(0x17);
    Lcd_Write_Data(0x1D);
    Lcd_Write_Data(0x21);
  
    Lcd_Write_Com(0X36);
    Lcd_Write_Data(0x48);
    Lcd_Write_Com(0xF0);
    Lcd_Write_Data(0xC3);
    Lcd_Write_Com(0xF0);
    Lcd_Write_Data(0x69);
    Lcd_Write_Com(0X13);
    Lcd_Write_Com(0X11);
    Lcd_Write_Com(0X29);

    GPIO_SetBits(CS);
}


void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i;
  GPIO_ResetBits(CS);
  Lcd_Write_Com(0x2c); //write_memory_start
  //digitalWrite(RS,HIGH);
  Address_set(x,y,x+l,y);
  for(i=1;i<=l;i++)
  {
      Lcd_Write_Data(c>>8);
      Lcd_Write_Data((uint8_t)c);
  }
  GPIO_SetBits(CS);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i;
  GPIO_ResetBits(CS);
  Lcd_Write_Com(0x2c); //write_memory_start
  //digitalWrite(RS,HIGH);
  Address_set(x,y,x,y+l);
  for(i=1;i<=l;i++)
  { 
      Lcd_Write_Data(c>>8);
      Lcd_Write_Data((uint8_t)c);
  }
  GPIO_SetBits(CS);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y+i, w, c);
  }
}

int RGB(int r,int g,int b)
{
  return r << 16 | g << 8 | b;
}

void LCD_Clear(unsigned int j)                   
{	
  unsigned int i,m;
  GPIO_ResetBits(CS);
  Address_set(0,0,320,480);
  for(i=0;i<320;i++)
    for(m=0;m<480;m++)
    {
      Lcd_Write_Data(j>>8);
      Lcd_Write_Data((uint8_t)j);
    }
  GPIO_SetBits(CS);   
}

void LCD_damier()                   
{	
  unsigned int i,m;
  GPIO_ResetBits(CS);
  Address_set(0,0,320,480);
  for(i=0;i<320;i++)
    for(m=0;m<480;m++)
    {

			Lcd_Write_Data(i);
      Lcd_Write_Data(m);
			
	}	
  GPIO_SetBits(CS);   
}

void draw_baterrie_level(uint8_t baterie_level);
void Screen_init(void){
  SPI_init();
	
  GPIO_InitType GPIO_InitStructure;
  
  /* Enable SPI and GPIO clocks */
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO , ENABLE);   
  
  /* Configure SPI pins */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = LED | RS | Reset | CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Output;
  GPIO_InitStructure.GPIO_Pull = ENABLE;
  GPIO_InitStructure.GPIO_HighPwr = ENABLE;
  GPIO_Init(&GPIO_InitStructure);

	
	GPIO_SetBits(LED | RS | Reset | CS);


  Lcd_Init();		
	LCD_Clear(0x0); 
	
	H_line(0, 100, 320, white);
	H_line(0, 101, 320, white);

	
	H_line(0, 290, 320, white);
	H_line(0, 291, 320, white);
	
	
	V_line(160,100,190,white);
	uint8_t size_of_digit =35;

	draw_digit_35 (2,digit_Tin_1_x ,digit_Tin_y,white);
	draw_digit_35 (5,digit_Tin_2_x ,digit_Tin_y,white);
	draw_digit_35 (8,digit_Tin_3_x ,digit_Tin_y,white);
	draw(12+2*size_of_digit-1, 150+25+25,dot_size,dot_size,(uint8_t *)dot_figure_1);
	draw(130, 150,dot_size,dot_size,(uint8_t *)dot_8_empty);
	/*draw(dot_x, dot_y2,dot_size,dot_size,(uint8_t *)dot_figure_1);*/
	draw(c_round_x1,c_round_y,c_size_x,c_size_y,(uint8_t *)c_round);
	
	draw_digit_35 (5,digit_Hin_1_x ,digit_Hin_y,white);
	draw_digit_35 (1,digit_Hin_2_x ,digit_Hin_y,white);
	draw_digit_35 (6,digit_Hin_3_x ,digit_Hin_y,white);	
	draw(12+2*size_of_digit-1, 220+53,dot_size,dot_size,(uint8_t *)dot_figure_1);
	draw(pourcentage_x1,pourcentage_y,pourcentage_size_x,pourcentage_size_y,(uint8_t *)pourcentage_figure);
	
	
	
	Rectf(45,105,65,30,yellow);
	//i
	Rectf( 60+3, 106, 9,  3, black);
	Rectf( 60+3, 106+24, 9,  3, black);	
	Rectf( 60+6, 106+3, 3,  21, black);
	//n
	Rectf( 80, 106+12, 15,  3, black);
	Rectf( 80, 106+15, 3,  12, black);		
	Rectf( 80+12, 106+15, 3,  12, black);	
	
	Rectf(45+160,105,65,30,blue);
	
	Rectf( 215+3, 106, 9,  3, black);
	Rectf( 215+3, 106+24, 9,  3, black);
	Rectf( 215, 106+3, 3, 21, black);		
	Rectf( 215+12, 106+3, 3, 21, black);
	
	Rectf( 234, 106+12, 3,  15, black);
	Rectf( 234+9, 106+12, 3,  15, black);
	Rectf( 234+3, 106+24,9, 3, black);
	
	Rectf( 244+6, 106+6,3, 19, black);
	Rectf( 244+3, 106+9,9, 2, black);
	Rectf( 244+11, 106+23,2, 3, black);
	Rectf( 244+10, 106+24,1, 3, black);
	Rectf( 244+7, 106+25,4, 2, black);
	
	draw_digit_35 (1,digit_Tout_1_x ,digit_Tin_y,white);
	draw_digit_35 (2,digit_Tout_2_x ,digit_Tin_y,white);
	draw_digit_35 (4,digit_Tout_3_x ,digit_Tin_y,white);
	draw(12+2*size_of_digit-1+160, 150+25+25,dot_size,dot_size,(uint8_t *)dot_figure_1);
	draw(130+160, 150,dot_size,dot_size,(uint8_t *)dot_8_empty);
	/*draw(dot_x, dot_y2,dot_size,dot_size,(uint8_t *)dot_figure_1);*/
	draw(c_round_x2,c_round_y,c_size_x,c_size_y,(uint8_t *)c_round);
	
	draw_digit_35 (8,digit_Hout_1_x ,digit_Hin_y,white);
	draw_digit_35 (4,digit_Hout_2_x ,digit_Hin_y,white);
	draw_digit_35 (7,digit_Hout_3_x ,digit_Hin_y,white);	
	draw(12+2*size_of_digit-1+160, 220+53,dot_size,dot_size,(uint8_t *)dot_figure_1);
	draw(pourcentage_x2,pourcentage_y,pourcentage_size_x,pourcentage_size_y,(uint8_t *)pourcentage_figure);
	
	//reseau 
	draw_reseau(128);
	Clock_Wait(2000);
	draw_reseau(85);
	Clock_Wait(2000);
	draw_reseau(70);
	Clock_Wait(2000);
	draw_reseau(40);
	Clock_Wait(2000);
	draw_baterrie_level(2);	
	Clock_Wait(2000);
	draw_baterrie_level(60);	
	Clock_Wait(2000);
	draw_baterrie_level(100);	
}

void draw(unsigned int x,unsigned int y,unsigned int w,unsigned int h,uint8_t figure[]){
  int i,j;
  GPIO_ResetBits(CS);
  Lcd_Write_Com(0x2c); //write_memory_start
  //digitalWrite(RS,HIGH);

  Address_set(x,y,x+w-1,y+h-1);
  for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			switch (figure[i*h+j])
      {
      	case 0: //black
					Lcd_Write_Data(black>>8);
					Lcd_Write_Data((uint8_t)black);
				break;
      	case 1: //white
					Lcd_Write_Data(white>>8);
					Lcd_Write_Data((uint8_t)white);
      		break;
				case 2: //red
					Lcd_Write_Data(red>>8);
					Lcd_Write_Data((uint8_t)red);
      		break;
				case 3: //green
					Lcd_Write_Data(green>>8);
					Lcd_Write_Data((uint8_t)green);
      		break;				
				case 4: //blue
					Lcd_Write_Data(blue>>8);
					Lcd_Write_Data((uint8_t)blue);
      		break;
				case 5: //yellow
					Lcd_Write_Data(yellow>>8);
					Lcd_Write_Data((uint8_t)yellow);
      		break;
				case 6: //cian
					Lcd_Write_Data(cyan>>8);
					Lcd_Write_Data((uint8_t)cyan);
      		break;
				case 7: //magenta
					Lcd_Write_Data(magenta>>8);
					Lcd_Write_Data((uint8_t)magenta);
      		break;				
      	default: //black
					Lcd_Write_Data(black>>8);
					Lcd_Write_Data((uint8_t)black);
      		break;
      }
			

		}
	}
  GPIO_SetBits(CS); 

}

void draw_letter(char letter, unsigned int x,unsigned int y,unsigned int color){
	switch (letter)
  {
  	case 'a':
			Rectf( x, y, 15,  3, color);
			Rectf( x, y+3, 3,  24, color);
			Rectf( x+12, y+3, 3,  24, color);
			Rectf( x+3, y+12, 9,  3, color);
  		break;
  	case'c':
			Rectf( x, y+9, 12,  3, color);
			Rectf( x, y+24, 12,  3, color);		
			Rectf( x, y+12, 3,  12, color);
  		break;
		case'd':
			Rectf( x, y, 12,  3, color);
			Rectf( x, y+24, 12,  3, color);		
			Rectf( x, y+3, 3,  21, color);
			Rectf( x+12, y+3, 3,  21, color);
  		break;
		case'e':
			Rectf( x, y, 15,  3, color);
			Rectf( x, y+12, 12,  3, color);	
			Rectf( x, y+24, 15,  3, color);		
			Rectf( x, y+3, 3,  21, color);
  		break;
		case'f':
			Rectf( x, y, 15,  3, color);
			Rectf( x, y+12, 9,  3, color);	
			Rectf( x, y+3, 3,  24, color);
  		break;
		case'i':
			Rectf( x+3, y, 9,  3, color);
			Rectf( x+3, y+24, 9,  3, color);	
			Rectf( x+6, y+3, 3,  21, color);
  		break;
		case'j':
			Rectf( x+6, y, 9,  3, color);
			Rectf( x+9, y+3, 3,  21, color);
			Rectf( x+3, y+21, 3,  3, color);
			Rectf( x+6, y+24, 3,  3, color);
  		break;	
		case'l':
			Rectf( x, y, 3,  27, color);
			Rectf( x+3, y+24, 12,  3, color);

  		break;
		case 'm':
			Rectf( x, y, 3,  27, color);
			Rectf( x+12, y, 3,  27, color);
			for(int i = 0; i<5;i++){
				V_line(x+3+i, y+1+i, 6, color);
				V_line(x+11-i, y+1+i, 6, color);
			}
			break;
			case 'N':
			Rectf( x, y, 3,  27, color);
			Rectf( x+12, y, 3,  27, color);
			for(int i = 0; i<3;i++){
				Rectf( x+3+i, y+3+3*i, 2, 3, color);
				Rectf( x+10-i, y+21-3*i, 2, 3, color);
			}
			V_line(x+6, y+12, 2, color);
			V_line(x+7, y+12, 3, color);
			V_line(x+8, y+13, 2, color);
  		break;
			case'n':
			Rectf( x, y+12, 15,  3, color);
			Rectf( x, y+15, 3,  12, color);		
			Rectf( x+12, y+15, 3,  12, color);		
  		break;			
			case'O':
			Rectf( x+3, y, 9,  3, color);
			Rectf( x+3, y+24, 9,  3, color);
			Rectf( x, y+3, 3, 21, color);		
			Rectf( x+12, y+3, 3, 21, color);
  		break;
			case'o':
			Rectf( x, y+12, 15,  3, color);
			Rectf( x, y+24, 15,  3, color);		
			Rectf( x, y+15, 3,  9, color);
			Rectf( x+12, y+15, 3, 9, color);			
  		break;
			case'p':
			Rectf( x, y, 11,  3, color);
			Rectf( x, y+3,3, 24, color);
			Rectf( x+10, y+2,3, 7, color);
			Rectf( x+3, y+9,7, 2, color);			
			H_line(x+11, y+1, 1, color);
			H_line(x+10, y+9, 2, color);
			H_line(x+10, y+10, 1, color);
			H_line(x+3, y+11, 6, color);
			break;
			case'r':
			Rectf( x, y, 11,  3, color);
			Rectf( x, y+3,3, 24, color);
			Rectf( x+10, y+2,3, 7, color);
			Rectf( x+3, y+9,7, 2, color);			
			H_line(x+11, y+1, 1, color);
			H_line(x+10, y+9, 2, color);
			H_line(x+10, y+10, 1, color);
			H_line(x+3, y+11, 6, color);
			Rectf( x+7, y+12,3, 3, color);	
			Rectf( x+8, y+15,3, 3, color);	
			Rectf( x+9, y+18,3, 3, color);	
			Rectf( x+10, y+21,3, 3, color);	
			Rectf( x+11, y+24,3, 3, color);	
			H_line(x+11, y+26, 1, black);
  		break;
			case's':
			Rectf( x+2, y, 13,  3, color);
			Rectf( x+2, y+12,11, 3, color);
			Rectf( x, y+24,13, 3, color);
			Rectf( x, y+2,3, 11, color);			
			Rectf( x+12, y+14,3, 11, color);
			H_line(x+1, y+1, 1, color);
			H_line(x+3, y+3, 1, color);
			H_line(x+1, y+13, 1, color);
			H_line(x+3, y+11, 1, color);
			H_line(x+13, y+13, 1, color);
			H_line(x+11, y+15, 1, color);
			H_line(x+11, y+23, 1, color);
			H_line(x+13, y+25, 1, color);
			break;
			case't':
			Rectf( x, y, 15,  3, color);
			Rectf( x+6, y+3,3, 24, color);
			break;
			case'u':
			Rectf( x, y+12, 3,  15, color);
			Rectf( x+12, y+12, 3,  15, color);
			Rectf( x+3, y+24,9, 3, color);
			break;
			case'v':
			for(int i = 0; i<7; i++){
				V_line(x+i, y+10+2*i, 4, color);		
				V_line(x+14-i, y+10+2*i, 4, color);
			}
			V_line(x+7, y+24, 3, color);
			break;
  	default:
  		break;
  }
}


void draw_seg_35_a(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 0;
	uint8_t x_start[9]={5,3,2,1,1,3,5,6,8};
	uint8_t x_stop[9]={27,26,26,25,25,25,24,24,24};
	for(uint8_t i =0;i<9;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}
void draw_seg_35_b(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 26;
	uint8_t y_start[9]={7,4,1,0,1,2,3,4,6};
	uint8_t y_stop[9]={23,24,24,26,26,27,28,27,24};
	for(uint8_t i =0;i<9;i++){
	V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);
	}	
}
void draw_seg_35_c(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 26;
	uint8_t y_start[9]={36,36,35,35,34,33,32,33,36};
	uint8_t y_stop[9]={55,58,61,61,61,60,59,58,56};
	for(uint8_t i =0;i<9;i++){
	V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);
	}	
}
void draw_seg_35_d(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 54;
	uint8_t x_start[9]={7,2,0,0,1,1,2,3,5};
	uint8_t x_stop[9]={23,24,24,25,25,25,26,26,26};
	for(uint8_t i =0;i<9;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}
void draw_seg_35_e(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 0;
	uint8_t y_start[9]={34,32,32,33,34,34,35,35,36};
	uint8_t y_stop[9]={54,53,53,53,53,52,52,52,51};
	for(uint8_t i =0;i<9;i++){
	V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);
	}	
}
void draw_seg_35_f(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 0;
	uint8_t y_start[9]={6,7,7,8,8,9,9,10,11};
	uint8_t y_stop[9]={26,28,28,27,26,25,25,24,24};
	for(uint8_t i =0;i<9;i++){
	V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);
	}	
}
void draw_seg_35_g(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 26;
	uint8_t x_start[9]={9,7,5,4,3,4,5,7,9};
	uint8_t x_stop[9]={26,27,29,30,31,30,29,27,25};
	for(uint8_t i =0;i<9;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}						

void draw_digit_35 (uint8_t value, unsigned int x,unsigned int y,unsigned int color){
	switch (value)
  {
  	case 0:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_d(x,y,color);
			draw_seg_35_e(x,y,color);
			draw_seg_35_f(x,y,color);
  		break;
  	case 1:
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
  		break;  	
		case 2:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_g(x,y,color);
			draw_seg_35_d(x,y,color);
			draw_seg_35_e(x,y,color);
  		break;  	
		case 3:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_g(x,y,color);
			draw_seg_35_d(x,y,color);
  		break;  	
		case 4:
			draw_seg_35_f(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_g(x,y,color);
  		break;  	
		case 5:
			draw_seg_35_f(x,y,color);
			draw_seg_35_a(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_g(x,y,color);
			draw_seg_35_d(x,y,color);
  		break;  	
		case 6:
			draw_seg_35_a(x,y,color);
			draw_seg_35_f(x,y,color);
			draw_seg_35_e(x,y,color);
			draw_seg_35_g(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_d(x,y,color);
  		break;  	
		case 7:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
  		break;  	
		case 8:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_d(x,y,color);
			draw_seg_35_e(x,y,color);
			draw_seg_35_f(x,y,color);
			draw_seg_35_g(x,y,color);
  		break;  	
		case 9:
			draw_seg_35_a(x,y,color);
			draw_seg_35_b(x,y,color);
			draw_seg_35_c(x,y,color);
			draw_seg_35_d(x,y,color);
			draw_seg_35_f(x,y,color);
			draw_seg_35_g(x,y,color);
  		break;
  	default:
  		break;
  }
}


void draw_seg_90_a(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 0;
	uint8_t x_start[13]={7,5,4,3,2,1,1,3,5,7,8,10,12};
	uint8_t x_stop[13]={38,37,37,37,36,36,36,35,35,35,34,34,34};
	for(uint8_t i =0;i<13;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}

void draw_seg_90_b(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 36;
	uint8_t y_start[13]={11,8,5,2,1,1,1,2,3,3,5,6,8};
	uint8_t y_stop[13]={35,35,36,36,37,37,38,39,40,41,40,38,36};
	for(uint8_t i =0;i<13;i++){
	V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);
	}	
}
void draw_seg_90_c(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 36;
	uint8_t y_start[13]={52,51,50,50,49,49,48,47,46,45,46,48,50};
	uint8_t y_stop[13]={77,80,83,87,89,89,89,89,88,87,86,84,82};
	for(uint8_t i =0;i<13;i++){
		V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);	}	
	}
void draw_seg_90_d(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 77;
	uint8_t x_start[13]={11,7,3,0,0,0,1,1,2,3,4,6,8};
	uint8_t x_stop[13]={33,34,34,34,35,35,35,36,36,36,37,37,37};
	for(uint8_t i =0;i<13;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}
void draw_seg_90_e(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 0;
	uint8_t y_start[12]={49,47,45,46,47,48,49,49,50,50,51,51};
	uint8_t y_stop[12]={77,77,77,77,76,76,76,76,75,75,75,74};
	for(uint8_t i =0;i<12;i++){
		V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);	
	}
}
void draw_seg_90_f(unsigned int x,unsigned int y,unsigned int color){
	uint8_t x_offset = 0;
	uint8_t y_start[12]={8,8,9,10,10,11,11,12,13,13,14,14};
	uint8_t y_stop[12]={37,39,41,40,39,38,37,37,36,36,35,35};
	for(uint8_t i =0;i<12;i++){
		V_line(x+x_offset+i,y+y_start[i],y_stop[i]+1-y_start[i],color);	
	}
}
void draw_seg_90_g(unsigned int x,unsigned int y,unsigned int color){
	uint8_t y_offset = 37;
	uint8_t x_start[13]={12,10,8,6,5,4,3,4,5,6,7,9,11};
	uint8_t x_stop[13]={35,37,39,41,42,43,44,43,42,41,40,38,35};
	for(uint8_t i =0;i<13;i++){
	H_line(x+x_start[i],y+y_offset+i,x_stop[i]+1-x_start[i],color);
	}	
}
void draw_digit_90 (uint8_t value, unsigned int x,unsigned int y,unsigned int color){
	switch (value)
  {
  	case 0:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_d(x,y,color);
			draw_seg_90_e(x,y,color);
			draw_seg_90_f(x,y,color);
  		break;
  	case 1:
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
  		break;  	
		case 2:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_g(x,y,color);
			draw_seg_90_d(x,y,color);
			draw_seg_90_e(x,y,color);
  		break;  	
		case 3:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_g(x,y,color);
			draw_seg_90_d(x,y,color);
  		break;  	
		case 4:
			draw_seg_90_f(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_g(x,y,color);
  		break;  	
		case 5:
			draw_seg_90_f(x,y,color);
			draw_seg_90_a(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_g(x,y,color);
			draw_seg_90_d(x,y,color);
  		break;  	
		case 6:
			draw_seg_90_a(x,y,color);
			draw_seg_90_f(x,y,color);
			draw_seg_90_e(x,y,color);
			draw_seg_90_g(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_d(x,y,color);
  		break;  	
		case 7:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
  		break;  	
		case 8:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_d(x,y,color);
			draw_seg_90_e(x,y,color);
			draw_seg_90_f(x,y,color);
			draw_seg_90_g(x,y,color);
  		break;  	
		case 9:
			draw_seg_90_a(x,y,color);
			draw_seg_90_b(x,y,color);
			draw_seg_90_c(x,y,color);
			draw_seg_90_d(x,y,color);
			draw_seg_90_f(x,y,color);
			draw_seg_90_g(x,y,color);
  		break;
  	default:
  		break;
  }
}
void draw_seg_30_V(unsigned int x,unsigned int y,unsigned int color){
	V_line(x,y,10,color);
	V_line(x+1,y-1,12,color);
	V_line(x+2,y,10,color);
}
void draw_seg_30_H(unsigned int x,unsigned int y,unsigned int color){
	H_line(x,y,8,color);
	H_line(x-1,y+1,10,color);
	H_line(x,y+2,8,color);
}
void draw_seg_30_a(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_H(x+4,y,color);
}

void draw_seg_30_b(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_V(x+13,y+3,color);
}

void draw_seg_30_c(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_V(x+13,y+16,color);
}

void draw_seg_30_d(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_H(x+4,y+26,color);
}
void draw_seg_30_e(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_V(x,y+16,color);
}

void draw_seg_30_f(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_V(x,y+3,color);
}

void draw_seg_30_g(unsigned int x,unsigned int y,unsigned int color){
	draw_seg_30_H(x+4,y+13,color);
}

void draw_digit_30 (uint8_t value, unsigned int x,unsigned int y,unsigned int color){
	switch (value)
  {
  	case 0:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_d(x,y,color);
			draw_seg_30_e(x,y,color);
			draw_seg_30_f(x,y,color);
  		break;
  	case 1:
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
  		break;  	
		case 2:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_g(x,y,color);
			draw_seg_30_d(x,y,color);
			draw_seg_30_e(x,y,color);
  		break;  	
		case 3:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_g(x,y,color);
			draw_seg_30_d(x,y,color);
  		break;  	
		case 4:
			draw_seg_30_f(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_g(x,y,color);
  		break;  	
		case 5:
			draw_seg_30_f(x,y,color);
			draw_seg_30_a(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_g(x,y,color);
			draw_seg_30_d(x,y,color);
  		break;  	
		case 6:
			draw_seg_30_a(x,y,color);
			draw_seg_30_f(x,y,color);
			draw_seg_30_e(x,y,color);
			draw_seg_30_g(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_d(x,y,color);
  		break;  	
		case 7:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
  		break;  	
		case 8:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_d(x,y,color);
			draw_seg_30_e(x,y,color);
			draw_seg_30_f(x,y,color);
			draw_seg_30_g(x,y,color);
  		break;  	
		case 9:
			draw_seg_30_a(x,y,color);
			draw_seg_30_b(x,y,color);
			draw_seg_30_c(x,y,color);
			draw_seg_30_d(x,y,color);
			draw_seg_30_f(x,y,color);
			draw_seg_30_g(x,y,color);
  		break;
  	default:
  		break;
  }
}

void draw_week_day(uint8_t week_day){
	Rectf(letter_WD1_x,letter_WD_y,55,27,0);
	switch (week_day)
	{
		case 1:
			draw_letter( 'd',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'i',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'm',  letter_WD3_x, letter_WD_y, white);
			break;
		case 2:
			draw_letter( 'l',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'u',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'n',  letter_WD3_x, letter_WD_y, white);
			break;
		case 3:
			draw_letter( 'm',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'a',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'r',  letter_WD3_x, letter_WD_y, white);
			break;
		case 4:
			draw_letter( 'm',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'e',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'r',  letter_WD3_x, letter_WD_y, white);
			break;
		case 5:
			draw_letter( 'j',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'e',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'u',  letter_WD3_x, letter_WD_y, white);
			break;
		case 6:
			draw_letter( 'v',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'e',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'n',  letter_WD3_x, letter_WD_y, white);
			break;
		case 7:
			draw_letter( 's',  letter_WD1_x, letter_WD_y, white);
			draw_letter( 'a',  letter_WD2_x, letter_WD_y, white);
			draw_letter( 'm',  letter_WD3_x, letter_WD_y, white);
			break;
		default:
			break;
	}
}

void draw_day(uint8_t day){
	Rectf(digit_D1_x,digit_D_y,36,29,0);
	if(day != 99){
		draw_digit_30 ( day%10, digit_D2_x, digit_D_y, white);
		day =day /10;
		if(day !=0){		
			draw_digit_30 ( day, digit_D1_x, digit_D_y, white);
		}
	}
}

void draw_mouth(uint8_t mouth){
	Rectf(digit_M1_x,digit_M_y,75,27,0);
	switch (mouth)
  {
  	case 1:
			draw_letter( 'j',  digit_M1_x, digit_M_y, white);
			draw_letter( 'a',  digit_M2_x, digit_M_y, white);
			draw_letter( 'n',  digit_M3_x, digit_M_y, white);
			draw_letter( 'v',  digit_M4_x, digit_M_y, white);
  		break;
  	case 2:
			draw_letter( 'f',  digit_M1_x, digit_M_y, white);
			draw_letter( 'e',  digit_M2_x, digit_M_y, white);
			draw_letter( 'v',  digit_M3_x, digit_M_y, white);
			draw_letter( 'r',  digit_M4_x, digit_M_y, white);
  		break;
		 case 3:
			draw_letter( 'm',  digit_M1_x, digit_M_y, white);
			draw_letter( 'a',  digit_M2_x, digit_M_y, white);
			draw_letter( 'r',  digit_M3_x, digit_M_y, white);
			draw_letter( 's',  digit_M4_x, digit_M_y, white);
  		break;
	 	case 4:
			draw_letter( 'a',  digit_M1_x, digit_M_y, white);
			draw_letter( 'v',  digit_M2_x, digit_M_y, white);
			draw_letter( 'r',  digit_M3_x, digit_M_y, white);
			draw_letter( 'i',  digit_M4_x, digit_M_y, white);
  		break;
		case 5:
			draw_letter( 'm',  digit_M1_x, digit_M_y, white);
			draw_letter( 'a',  digit_M2_x, digit_M_y, white);
			draw_letter( 'i',  digit_M3_x, digit_M_y, white);
  		break;
		case 6:
			draw_letter( 'j',  digit_M1_x, digit_M_y, white);
			draw_letter( 'u',  digit_M2_x, digit_M_y, white);
			draw_letter( 'i',  digit_M3_x, digit_M_y, white);
			draw_letter( 'n',  digit_M4_x, digit_M_y, white);
  		break;
		case 7:
			draw_letter( 'j',  digit_M1_x, digit_M_y, white);
			draw_letter( 'u',  digit_M2_x, digit_M_y, white);
			draw_letter( 'i',  digit_M3_x, digit_M_y, white);
			draw_letter( 'l',  digit_M4_x, digit_M_y, white);
  		break;
		case 8:
			draw_letter( 'a',  digit_M1_x, digit_M_y, white);
			draw_letter( 'o',  digit_M2_x, digit_M_y, white);
			draw_letter( 'u',  digit_M3_x, digit_M_y, white);
			draw_letter( 't',  digit_M4_x, digit_M_y, white);
  		break;
		case 9:
			draw_letter( 's',  digit_M1_x, digit_M_y, white);
			draw_letter( 'e',  digit_M2_x, digit_M_y, white);
			draw_letter( 'p',  digit_M3_x, digit_M_y, white);
			draw_letter( 't',  digit_M4_x, digit_M_y, white);
  		break;
		case 10:
			draw_letter( 'O',  digit_M1_x, digit_M_y, white);
			draw_letter( 'c',  digit_M2_x, digit_M_y, white);
			draw_letter( 't',  digit_M3_x, digit_M_y, white);
			draw_letter( 'o',  digit_M4_x, digit_M_y, white);
  		break;
		case 11:
			draw_letter( 'N',  digit_M1_x, digit_M_y, white);
			draw_letter( 'o',  digit_M2_x, digit_M_y, white);
			draw_letter( 'v',  digit_M3_x, digit_M_y, white);
			draw_letter( 'e',  digit_M4_x, digit_M_y, white);
  		break;
	 case 12:
			draw_letter( 'd',  digit_M1_x, digit_M_y, white);
			draw_letter( 'e',  digit_M2_x, digit_M_y, white);
			draw_letter( 'c',  digit_M3_x, digit_M_y, white);
			draw_letter( 'e',  digit_M4_x, digit_M_y, white);
  		break;										
  	default:
  		break;
  }
}

void draw_hour(uint8_t hour){
	Rectf(digit_H1_x,digit_H_Min_y,104,90,0);
	if(hour != 99){
		draw_digit_90 ( hour%10, digit_H2_x, digit_H_Min_y, white);
		hour =hour /10;
		if(hour !=0){		
			draw_digit_90 ( hour, digit_H1_x, digit_H_Min_y, white);
		}
}
}
void draw_minute(uint8_t minute){
	Rectf(digit_Min1_x,digit_H_Min_y,104,90,0);
		if(minute != 99){
		draw_digit_90 ( minute%10, digit_Min2_x, digit_H_Min_y, white);
		minute =minute /10;
		draw_digit_90 ( minute, digit_Min1_x, digit_H_Min_y, white);
		}
}
void draw_year(int year){
	Rectf(digit_H1_x,digit_H_Min_y,220,90,0);
	if(year != 99){
		draw_digit_90 ( year%10, digit_Min2_x, digit_H_Min_y, white);
		year =year /10;
		draw_digit_90 ( year%10, digit_Min1_x, digit_H_Min_y, white);
		year =year /10;
		draw_digit_90 ( year%10, digit_H2_x, digit_H_Min_y, white);
		year =year /10;
		draw_digit_90 ( year%10, digit_H1_x, digit_H_Min_y, white);
	}
}	
extern uint8_t validate_press;
extern int value_press;
extern uint8_t minute_set;
extern uint8_t hour_set;
extern uint8_t day_set;
extern uint8_t day_week_set;
extern uint8_t mouth_set;
#define RTC_PERIOD_30s          32767*30
void Screen_set_up(void){
	
	SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_RTC, ENABLE);
  RTC_InitType RTC_Init_struct;
  RTC_DateTimeType RTC_DateTime;  
  /* Set the present time and date */
  RTC_DateTime.Second = 0;
	value_press = 2;
	//set week day
	while (validate_press == 0 ){
		if(value_press >=8){
			value_press = 1;
		}
		draw_week_day(value_press);
		Clock_Wait(400);
		draw_week_day(0);
		Clock_Wait(400);	
	}
	RTC_DateTime.WeekDay = value_press;
	draw_week_day(value_press);
	day_week_set = value_press;
	value_press=1;
	validate_press=0;
		
	//set day
	while (validate_press == 0 ){
	if(value_press >=32){
		value_press = 1;
	}
	draw_day(value_press);
	Clock_Wait(400);
	draw_day(99);
	Clock_Wait(400);	
	}
	RTC_DateTime.MonthDay = value_press;
	draw_day(value_press);
	day_set = value_press;
	value_press=1;
	validate_press=0;
	
	//set mounth
	while (validate_press == 0 ){
		if(value_press >=13){
			value_press = 1;
		}
		draw_mouth(value_press);
		Clock_Wait(400);
		draw_mouth(99);
		Clock_Wait(400);	
		}
	draw_mouth(value_press);
	mouth_set=value_press;
	RTC_DateTime.Month = value_press;
	value_press=2024;
	validate_press=0;
	//set year
	while (validate_press == 0 ){
		if(value_press >=10000){
			value_press = 1;
		}
		draw_year(value_press);
		Clock_Wait(600);
		draw_year(99);
		Clock_Wait(200);	
		}
		draw_year(value_press);
		RTC_DateTime.Year = value_press;
		value_press=0;
		validate_press=0;
	
	Clock_Wait(1000);		
	draw_year(99);
	draw(dot_x, dot_y1,dot_size,dot_size,(uint8_t *)dot_figure_1);	
	draw(dot_x, dot_y2,dot_size,dot_size,(uint8_t *)dot_figure_1);
		
	
	//set hour
	while (validate_press == 0 ){
		if(value_press >= 24){
			value_press = 0;
		}
		draw_hour(value_press);
		Clock_Wait(400);
		draw_hour(99);
		Clock_Wait(400);	
		}
	  RTC_DateTime.Hour = value_press;
		draw_hour(value_press);
		hour_set = value_press;
		value_press=0;
		validate_press=0;	
		//set minute
	while (validate_press == 0 ){
		if(value_press >=60){
			value_press = 0;
		}
		draw_minute(value_press);
		Clock_Wait(400);
		draw_minute(99);
		Clock_Wait(400);	
		}
	  RTC_DateTime.Minute = value_press;
		draw_minute(value_press);		
		minute_set = value_press;
		
		RTC_SetTimeDate(&RTC_DateTime);
		RTC_ClockwatchCmd(ENABLE);

		NVIC_InitType NVIC_InitStructure;
  
		SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_RTC, ENABLE);
  
		RTC_Init_struct.RTC_operatingMode = RTC_TIMER_PERIODIC;    /**< Periodic RTC mode */
		RTC_Init_struct.RTC_PATTERN_SIZE = 1 - 1;                  /**< Pattern size set to 1 */
		RTC_Init_struct.RTC_TLR1 = RTC_PERIOD_30s;               /**< Enable 0.5s timer period */
		RTC_Init_struct.RTC_PATTERN1 = 0x00;                       /**< RTC_TLR1 selected for time generation */
		RTC_Init(&RTC_Init_struct);
  
		/* Enable RTC Timer interrupt*/
		RTC_IT_Config(RTC_IT_TIMER, ENABLE);
		RTC_IT_Clear(RTC_IT_TIMER);

		for (volatile uint16_t i=0; i<600; i++) {
			__asm("NOP");
		}
  
  /* Set the RTC_IRQn interrupt priority and enable it */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable RTC */
  RTC_Cmd(ENABLE);
}

void draw_reseau (uint8_t signal){
	uint8_t reseau_x=165;
	uint8_t reseau_y=105;
	uint16_t color = white;
	//reseau min
	Rectf(reseau_x+17, reseau_y+22 ,2,2,color);
	
	if(signal >100){
		color = black;
	}
	//reseau first arc circle
	H_line(reseau_x+13, reseau_y+19 ,1,color);
	Rectf(reseau_x+14, reseau_y+18 ,8,2,color);
	H_line(reseau_x+22, reseau_y+19 ,1,color);
	H_line(reseau_x+14, reseau_y+20 ,3,color);
	H_line(reseau_x+19, reseau_y+20 ,3,color);
	H_line(reseau_x+16, reseau_y+17 ,4,color);
	if(signal >75){
		color = black;
	}
	//reseau second arc circle
	Rectf(reseau_x+15, reseau_y+12 ,6,3,color);
	Rectf(reseau_x+21, reseau_y+13 ,2,3,color);
	Rectf(reseau_x+23, reseau_y+14 ,2,3,color);
	V_line(reseau_x+25, reseau_y+15,2,color);
	V_line(reseau_x+10, reseau_y+15,2,color);
	Rectf(reseau_x+11, reseau_y+14 ,2,3,color);
	Rectf(reseau_x+13, reseau_y+13 ,2,3,color);
	if(signal >60){
		color = black;
	}
	//reseau third 
	Rectf(reseau_x+15, reseau_y+7 ,6,3,color);
	Rectf(reseau_x+21, reseau_y+8 ,4,3,color);
	Rectf(reseau_x+11, reseau_y+8 ,4,3,color);
	V_line(reseau_x+6, reseau_y+12,2,color);
	V_line(reseau_x+7, reseau_y+11,3,color);
	V_line(reseau_x+8, reseau_y+10,4,color);
	V_line(reseau_x+9, reseau_y+10,3,color);
	V_line(reseau_x+10, reseau_y+9,3,color);
	V_line(reseau_x+25, reseau_y+9,3,color);
	V_line(reseau_x+26, reseau_y+10,3,color);
	V_line(reseau_x+27, reseau_y+10,4,color);
	V_line(reseau_x+28, reseau_y+11,3,color);
	V_line(reseau_x+29, reseau_y+12,2,color);	
}
 
void draw_baterrie_level(uint8_t baterie_level){

//Rectf(275,105,40,30,green);
Rectf(275,105,41,2,white);
Rectf(275,105+28,41,2,white);
Rectf(275,105+2,2,27,white);
Rectf(275+39,105+2,2,27,white);
Rectf(275+41,105+11,3,8,white);

if(baterie_level <20){
	Rectf(275+3,105+3,11,24,red);
	Rectf(275+15,105+3,11,24,black);
	Rectf(275+27,105+3,11,24,black);
}else if(baterie_level >60){
	Rectf(275+3,105+3,11,24,green);
	Rectf(275+15,105+3,11,24,green);
	Rectf(275+27,105+3,11,24,green);
}else{
	Rectf(275+3,105+3,11,24,yellow);
	Rectf(275+15,105+3,11,24,yellow);
	Rectf(275+27,105+3,11,24,black);
}
}

