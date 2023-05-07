/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Software Component: EXTI *****************/
/**********************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define EXTI_u8_INT0 0  
#define EXTI_u8_INT1 1  
#define EXTI_u8_INT2 2

#define EXTI_u8_RAISING_EDGE       0
#define EXTI_u8_FALLING_EDGE       1
#define EXTI_u8_ANY_LOGICAL_EDGE   2 
#define EXTI_u8_LOW_LEVEL_EDGE     3


u8    EXTI_u8EXTIEnable  (u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex);
		   
u8    EXTI_u8EXTIDisable (u8 Copy_u8EXTIIndex);

u8    EXTI_u8EXTISetCallBack(u8 Copy_u8EXTIIndex, void (*Copy_pf)(void));



#endif
