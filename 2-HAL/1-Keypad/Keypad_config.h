/***********************************************************/
/**************  Name: Abdulrahman Omar    *****************/
/**************  Date: 1/28/2023           *****************/
/**************  Software Component: Keypad*****************/
/**************  Version: 1.0              *****************/
/***********************************************************/

#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#define KPD_u8_PORT               DIO_u8_PORTA

#define KPD_u8_R1_PIN             DIO_u8_PIN0
#define KPD_u8_R2_PIN             DIO_u8_PIN1
#define KPD_u8_R3_PIN             DIO_u8_PIN2
#define KPD_u8_R4_PIN             DIO_u8_PIN3

#define KPD_u8_C1_PIN             DIO_u8_PIN4
#define KPD_u8_C2_PIN             DIO_u8_PIN5
#define KPD_u8_C3_PIN             DIO_u8_PIN6
#define KPD_u8_C4_PIN             DIO_u8_PIN7

#define KPD_u8_Keys {{'1','2','3','+'},\
					 {'4','5','6','-'},\
					 {'7','8','9','*'},\
					 {'0','=','/','%'}}


#endif