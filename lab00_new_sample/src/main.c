/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm324xg_lcd_sklin.h"
#include  "stlogo.h"
#include <stdio.h>

void stm32f4_Hardware_Init (void);
static void delay(__IO uint32_t nCount);
void GLCD_Value(uint8_t row_no, uint8_t col_no, int16_t val);
extern uint8_t startAddress;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	// Hardware intialization
	stm32f4_Hardware_Init();
	//TFT intialization
	LCD_Init();

	LCD_DisplayOn();
  LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLUE); // Text = red; back = blue

  //========= (F4 + EU Board) GLCD test ;
	LCD_DrawBitmap(0, 0, (uint8_t *) stlogo);  // start at xPixel=0 (rightward), yPixel=0 (downward)
  delay(200); /* delay 1000 ms */
  LCD_RGB_Test();
  delay(500); /* delay 1000 ms */


	LCD_DrawBitmap(0, 0, (uint8_t *) 0x08010000);  // start at xPixel=0, yPixel=0
  delay(500); /* delay 1000 ms */


	MenuInit();
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12);
	LCD_DisplayStringLineCol(19, 0,"   Copyright (c) Shir-Kuan Lin, NCTU          " );		// line 10, column 0
	LCD_SetFont(&Font20);

	LCD_DrawBitmap(60, 140, &startAddress);  // start at xPixel=60, yPixel=140
	LCD_DrawBitmap(190, 130, (uint8_t *) stlogo);  // start at xPixel=190 (rightward), yPixel=130 (downward)

	while(1)
	{
		uint16_t val;
		GLCD_Value(5, 12, (int16_t) (++val)); 
		delay(50); /* delay 100 ms */		
	}
}

static void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0;
//  for(index = (100000 * nCount); index != 0; index--)
  for(index = (10000 * nCount); index != 0; index--)
  {
  }
}

void GLCD_Value(uint8_t row_no, uint8_t col_no, int16_t val)
{
  char p_text[6] = "";

	sprintf(p_text, "%i ", val);  //% read a decimal, octal, or hexadecimal integer
	LCD_DisplayStringLineCol(row_no, col_no, p_text);
}

