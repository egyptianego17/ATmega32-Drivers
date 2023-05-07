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

static u8 Flag = 1;

ISR(TIMER1_OVF_vect){
	TCNT1 = 18660;   // for 1 sec at 12 MHz
	Flag ^=1;

}


int main (void)
{
		/*
		 * @brief Digital input/output Module to initialize pins
		 */
		DIO_SetPinDirection(PortC, PIN7, OUTPUT);


		TCNT1 = 18660;   // for 1 sec at 12 MHz

			TCCR1A = 0x00;
			TCCR1B = (0<<CS10) | (0<<CS11) | (1<<CS12);  // Timer mode with 256 prescler
			TIMSK = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
			sei();        // Enable global interrupts by setting global interrupt enable bit in SREG

		while (1)
		{


				if (Flag == 0){
					DIO_SetPinValue(PortC, PIN7, LOW);

				} else {
					DIO_SetPinValue(PortC, PIN7, HIGH);

				}

		}
		return 0;
}

