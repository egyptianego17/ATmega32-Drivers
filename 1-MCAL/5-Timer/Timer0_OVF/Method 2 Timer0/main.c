/************************************************************/
/**************  Name: Abdulrahman Omar     *****************/
/**************  Software Component: TIMER  *****************/
/************************************************************/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#define F_CPU 12000000UL
#include "types.h"
#include "DIO_int.h"

static u32 Count=0;
static u8 Flag = 1;

ISR(TIMER0_OVF_vect){
	TCNT0 = 131;
	Count++;
}


int main (void)
{
	/*
	 * @brief Digital input/output Module to initialize pins
	 */
	DIO_SetPinDirection(PortC, PIN7, OUTPUT);

	/*
	 * @brief We are using timer0
	 * @brief Intialize the Counter (using TCNT0)
	 * @brief Choose the prescaler (256)
	 * @brief wait untill the OverFlow flag set to 0
	 * @brief then clear counter register TCNT0
	 * @brief then increment the count
	 *
	 * @brief To get 1 second
	 * @brief Timerclk = CPUclk / Prescaler = 12Mhz / 256 = 46875 clock tick per second
	 * @brief Overflow happen each 256 tick
	 * @brief if we devide timer ticks over 125 we will get 375 cycle to get 1 second
	 * @brief intialize timer counter register by 256-125 = 131
	 * @breif and set the counter to perform the functionality each 375 interrupt
	 *
	 */

	TCNT0 = 131 ;
	TIMSK = (1<<TOIE0);
	TCCR0 = (0<<CS00)| (0<<CS01) | (1<<CS02) | (0<<WGM01) | (0<<WGM00);
	sei();

	while (1)
	{
		if ( 0 == (Count % 375))
		{

			if (Flag == 0){
				DIO_SetPinValue(PortC, PIN7, LOW);
				Flag = 1;
			} else {
				DIO_SetPinValue(PortC, PIN7, HIGH);
				Flag = 0;
			}
			Count = 0;
		}


	}
	return 0;
}

