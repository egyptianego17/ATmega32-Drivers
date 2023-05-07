/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Date: 1/28/2023          *****************/
/**************  Software Component: LCD  *****************/
/**************  Version: 1.0             *****************/
/**********************************************************/

#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#define LCD_u8_CONTROL_PORT      PORTA 
#define LCD_u8_RS_PIN            PIN0
#define LCD_u8_RW_PIN            PIN1
#define LCD_u8_E_PIN             PIN2
#define LCD_u8_DATA_PORT         PORTB



/* LCD_u8_MODE Options:
                 LCD_u8_MODE_8_BIT
				 LCD_u8_MODE_4_BIT
                                        */
								   
#define LCD_u8_MODE      LCD_u8_MODE_8_BIT

#endif