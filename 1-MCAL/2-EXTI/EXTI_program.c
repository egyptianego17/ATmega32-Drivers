/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Software Component: EXTI *****************/
/**********************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"


// Global pointers to functions
static void (*EXTI_ApfExt[3])(void)={NULL,NULL,NULL};

u8 EXTI_u8EXTIEnable  (u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeIndex)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8EXTIIndex <= EXTI_u8_INT2) && (Copy_u8EdgeIndex <= EXTI_u8_LOW_LEVEL_EDGE))
	{
		switch (Copy_u8EXTIIndex)
		{
			case (EXTI_u8_INT0):
				switch(Copy_u8EdgeIndex)
				{
					case (EXTI_u8_RAISING_EDGE): 
					    // ENABLE EXTI 0
						SET_BIT(EXTI_u8_GICR,  6);
						SET_BIT(EXTI_u8_MCUCR, 1);
						SET_BIT(EXTI_u8_MCUCR, 0);
						break;
					case (EXTI_u8_FALLING_EDGE): 
						// ENABLE EXTI 0
						SET_BIT(EXTI_u8_GICR,  6);
						SET_BIT(EXTI_u8_MCUCR, 1);
						CLR_BIT(EXTI_u8_MCUCR, 0);
						break;
					case (EXTI_u8_ANY_LOGICAL_EDGE): 
						// ENABLE EXTI 0
						SET_BIT(EXTI_u8_GICR,  6);
						CLR_BIT(EXTI_u8_MCUCR, 1);
						SET_BIT(EXTI_u8_MCUCR, 0);
						break;
					case (EXTI_u8_LOW_LEVEL_EDGE): 
						// ENABLE EXTI 0
						SET_BIT(EXTI_u8_GICR,  6);
						CLR_BIT(EXTI_u8_MCUCR, 1);
						CLR_BIT(EXTI_u8_MCUCR, 0);
						break;
				}
			break;
			case (EXTI_u8_INT1):
				switch(Copy_u8EdgeIndex)
				{
					case (EXTI_u8_RAISING_EDGE): 
					    // ENABLE EXTI 1
						SET_BIT(EXTI_u8_GICR,  7);
						SET_BIT(EXTI_u8_MCUCR, 3);
						SET_BIT(EXTI_u8_MCUCR, 2);
						break;
					case (EXTI_u8_FALLING_EDGE): 
						// ENABLE EXTI 1
						SET_BIT(EXTI_u8_GICR,  7);
						SET_BIT(EXTI_u8_MCUCR, 3);
						CLR_BIT(EXTI_u8_MCUCR, 2);
						break;
					case (EXTI_u8_ANY_LOGICAL_EDGE): 
						// ENABLE EXTI 1
						SET_BIT(EXTI_u8_GICR,  7);
						CLR_BIT(EXTI_u8_MCUCR, 3);
						SET_BIT(EXTI_u8_MCUCR, 2);
						break;
					case (EXTI_u8_LOW_LEVEL_EDGE): 
						// ENABLE EXTI 1
						SET_BIT(EXTI_u8_GICR,  7);
						CLR_BIT(EXTI_u8_MCUCR, 3);
						CLR_BIT(EXTI_u8_MCUCR, 2);
						break;
				}
			break;
			case (EXTI_u8_INT2):
				switch(Copy_u8EdgeIndex)
				{
					case (EXTI_u8_RAISING_EDGE): 
					    // ENABLE EXTI 2
						SET_BIT(EXTI_u8_GICR,  5);
						SET_BIT(EXTI_u8_MCUCSR, 6);
						break;
					case (EXTI_u8_FALLING_EDGE): 
						// ENABLE EXTI 2
						SET_BIT(EXTI_u8_GICR,  5);
						CLR_BIT(EXTI_u8_MCUCSR, 6);
						break;
					default: Local_u8ErrorState = STD_TYPES_NOK;
				}
			break;
		}
	}
	else
	{
		STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8    EXTI_u8EXTISetCallBack(u8 Copy_u8EXTIIndex, void (*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8EXTIIndex <= EXTI_u8_INT2) && (Copy_pf!= NULL))
	{
		EXTI_ApfExt[Copy_u8EXTIIndex] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}



u8 EXTI_u8EXTIDisable (u8 Copy_u8EXTIIndex)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8EXTIIndex <= EXTI_u8_INT2)
	{
		switch (Copy_u8EXTIIndex)
		{
			case (EXTI_u8_INT0):CLR_BIT(EXTI_u8_GICR, 6);break;
			case (EXTI_u8_INT1):CLR_BIT(EXTI_u8_GICR, 7);break;
			case (EXTI_u8_INT2):CLR_BIT(EXTI_u8_GICR, 5);break;
		}
	}
	else
	{
		STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


void __vector_1(void)  __attribute__((signal));
void __vector_1(void)
{
	if (EXTI_ApfExt[EXTI_u8_INT0] != NULL)
	{		
		EXTI_ApfExt[EXTI_u8_INT0]();
	}
}

void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	if (EXTI_ApfExt[EXTI_u8_INT1] != NULL)
	{		
		EXTI_ApfExt[EXTI_u8_INT1]();
	}
}

void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	if (EXTI_ApfExt[EXTI_u8_INT2] != NULL)
	{		
		EXTI_ApfExt[EXTI_u8_INT2]();
	}
}
