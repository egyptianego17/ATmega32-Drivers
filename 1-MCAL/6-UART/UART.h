/************************************************************/
/**************  Name: Abdulrahman Omar     *****************/
/**************  Software Component: UART   *****************/
/************************************************************/

#ifndef UART_H_
#define UART_H_

void UART_Init(void);

void UART_SendChar(u8 data);

u8 UART_GetChar(void);

#endif /* UART_H_ */
