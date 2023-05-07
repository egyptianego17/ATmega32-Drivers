/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Date: 1/28/2023          *****************/
/**************  Software Component: LCD  *****************/
/**************  Version: 1.0             *****************/
/**********************************************************/ 
/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_int.h"

void LCD_voidInit(void)
{
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	_dealy_ms(35);
	LCD_voidSendCmnd(0b00111000);
	_dealy_us(40);
	LCD_voidSendCmnd(0b00001111);
	_dealy_us(40);
	LCD_voidSendCmnd(0b00000001);
	_dealy_ms(2);
	LCD_voidSendCmnd(0b0000010);
#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	_dealy_ms(35);
	LCD_voidSendCmnd(0b00111000);
	LCD_voidSendCmnd(0b00111000);
	_dealy_us(40);
	LCD_voidSendCmnd(0b00001111);
	_dealy_us(40);
	LCD_voidSendCmnd(0b00000001);
	_dealy_ms(2);
	LCD_voidSendCmnd(0b0000010);
#endif
}

void LCD_voidSendCmnd(u8 Copy_u8Cmnd)
{
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	// Send data in 4 bit mode
	/* Setting pins direction */
	DIO_SetPortDirection(LCD_u8_CONTROL_PORT, OUTPUT);
	DIO_SetPortDirection(LCD_u8_DATA_PORT, OUTPUT);
	
	/* RS = 0 & RW = 0 */
	DIO_SetPinValue(LCD_u8_RS_PIN, LOW);
	DIO_SetPinValue(LCD_u8_RW_PIN, LOW);
	
	/* Setting pins data */ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);
	
#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	// Send data in 8 bit mode
	/* Setting pins direction */ 
	DIO_SetPortDirection(LCD_u8_CONTROL_PORT, OUTPUT);
	DIO_SetPortDirection(LCD_u8_DATA_PORT, OUTPUT);
	
	/* RS = 0 & RW = 0 */
	DIO_SetPinValue(LCD_u8_RS_PIN, LOW);
	DIO_SetPinValue(LCD_u8_RW_PIN, LOW);
	
	/* Setting pins data to send the first 4 bits*/ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd << 4 );
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);

	/* Setting pins data to send the second 4 bits*/ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);
	
#endif
}

void LCD_voidSendChar(u8 Copy_u8Char)
{
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT

	/* Setting pins direction */
	DIO_SetPortDirection(LCD_u8_CONTROL_PORT, OUTPUT);
	DIO_SetPortDirection(LCD_u8_DATA_PORT, OUTPUT);
	
	/* RS = 1 & RW = 0 */
	DIO_SetPinValue(LCD_u8_RS_PIN, HIGH);
	DIO_SetPinValue(LCD_u8_RW_PIN, LOW);
	
	/* Setting pins data */ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);
	
#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT

	/* Setting pins direction */
	DIO_SetPortDirection(LCD_u8_CONTROL_PORT, OUTPUT);
	DIO_SetPortDirection(LCD_u8_DATA_PORT, OUTPUT);
	
	/* RS = 1 & RW = 0 */
	DIO_SetPinValue(LCD_u8_RS_PIN, HIGH);
	DIO_SetPinValue(LCD_u8_RW_PIN, LOW);
	
	/* Setting pins data to send the first 4 bits   */ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char >> 4);
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);

	/* Setting pins data to send the second 4 bits   */ 
	DIO_SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);
	
	/* Latch E=0 -> E=1 -> E=0 */
	DIO_SetPinValue(LCD_u8_E_PIN, HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_u8_E_PIN, LOW);
		
	
	
#endif
}


u8 LCD_voidGoToXY(u8 Copy_u8LineNum, u8 Copy_u8Location)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8Location <= 39)
	{
		switch (Copy_u8LineNum)
		{
			case LCD_u8_LINE1: LCD_voidSendCmnd(0x80+Copy_u8Location);break;
			case LCD_u8_LINE2: LCD_voidSendCmnd(0xC0+Copy_u8Location);break;
			default: Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
}
