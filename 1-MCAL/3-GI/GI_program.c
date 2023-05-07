/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Software Component: GI   *****************/
/**********************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GI_interface.h"
#include "GI_private.h"

void GI_voidEnable(void)
{
	SET_BIT(EXTI_u8_SREG, 7);
}

void GI_voidDisable(void)
{
	CLR_BIT(EXTI_u8_SREG, 7);
}

