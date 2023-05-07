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

u32 Count=0;
static u8 Flag = 1;

ISR(TIMER0_COMP_vect){
	Count++;
	if (Count == 1875){
		Count = 0;
	}
}

int main (void)
{
		/*
		 * @brief Digital input/output Module to initialize pins
		 */
		DIO_SetPinDirection(PortC, PIN7, OUTPUT);

		/*
		 * @brief if you have 12MHZ clock oscillator
		 * @brief Timerclk = CPUclk / Prescaler
		 * @brief If Prescaler choose 64 (using TCCR0)
		 * @brief Timerclk = 187500 timer tick to get 1 second
		 * @brief So, we can set Output Compare Match Interrupt Enable (usingTIMSK)
		 * @brief and enable CTC mode.
		 *
		 * @brief Set the output compare register by the value which the Interrupt fire on it
		 * @brief Take care the maximum number at OCR0 = 255
		 *
		 * @brief To get 1 second, set OCR0 to 100
		 * @brief and clear the counter after 1875 times
		 */

		OCR0 = 100;
		TIMSK = (1<<OCIE0);
		TCCR0 = (1<<CS00)| (1<<CS01) | (0<<CS02) | (1<<WGM01);
		sei();

		while (1)
		{

			if ( 0 == ( Count % 1874)){
				if (Flag == 0){
					DIO_SetPinValue(PortC, PIN7, LOW);
					Flag = 1;
				} else {
					DIO_SetPinValue(PortC, PIN7, HIGH);
					Flag = 0;
				}
			}
		}
		return 0;
}

