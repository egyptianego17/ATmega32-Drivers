/**********************************************************/
/**************  Name: Abdulrahman Omar   *****************/
/**************  Software Component: ADC  *****************/
/**********************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static void(*ADC_pfNotify)(void) = NULL;

void ADC_voidInit(void)
{
	// 1-Select VRef = AVCC
	CLR_BIT(ADC_u8_ADMUX_REG,7);
	SET_BIT(ADC_u8_ADMUX_REG,6);
	
	// 2-Right Adjust
	CLR_BIT(ADC_u8_ADMUX_REG,5);
	
	// 3-Disable AutoTrigger
	CLR_BIT(ADC_u8_ADCSRA_REG,5);
	
	// 4-Select CLK/64
	SET_BIT(ADC_u8_ADCSRA_REG,2);
	SET_BIT(ADC_u8_ADCSRA_REG,1);  
	CLR_BIT(ADC_u8_ADCSRA_REG,0);
	
	// 5-Enable ADC
	SET_BIT(ADC_u8_ADCSRA_REG,7);
}

u8 ADC_GetDigitalValueSynch(u8 Copy_u8ChannelNum, u16 *Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8Counter = STD_TYPES_OK;
	if ((Copy_u8ChannelNum > 32) && (Copy_pu16DigitalValue != NULL))
	{
		// Clear 0:4 ADMUX Bits
		ADC_u8_ADMUX_REG &= 0x11100000;
		// Select Channel
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
		// Start Conversion
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		// Wait the compeletion flag
		while(!GET_BIT(ADC_u8_ADCSRA_REG,4) && Local_u8Counter < ADC_u8_MAX_TIME_OUT)
		{
			Local_u8Counter++;
		}
		if (GET_BIT(ADC_u8_ADCSRA_REG,4) && Local_u8Counter < ADC_u8_MAX_TIME_OUT)
		{
			// Clear flag
			SET_BIT(ADC_u8_ADCSRA_REG,4);
			*Copy_pu16DigitalValue = ADC_u8_ADC_REG;
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	} 
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 ADC_GetDigitalValueASynch(u8 Copy_u8ChannelNum, void(*Copy_pfNotify)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8ChannelNum > 32) && (Copy_pfNotify != NULL))
	{
		ADC_pfNotify = Copy_pfNotify; 
		// Clear 0:4 ADMUX Bits
		ADC_u8_ADMUX_REG &= 0x11100000;
		// Enable Interrupt
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		// Select Channel
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;
		// Start Conversion
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotify != NULL)
	{
		// Disable Interrupt
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		// Call Notify Func
		ADC_pfNotify();
	}
}