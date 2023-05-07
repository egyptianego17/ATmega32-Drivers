/************************************************************/
/**************  Name: Abdulrahman Omar     *****************/
/**************  Software Component: Servo  *****************/
/************************************************************/


#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 12000000
#include "types.h"
#include "Dio_int.h"
#include "ADC.h"


void main()
{
	u16 u16_ADCValue =0;

	ADC_Init();

   //Configure TIMER1
   TCCR1A|=(0<<COM1A0)|(1<<COM1A1)|(1<<WGM11)|(0<<WGM10);        //NON Inverted Fast PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10)|(0<<CS12); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=3749;  //fPWM=50Hz (Period = 20ms Standard).
   DDRD=(1<<PD4)|(1<<PD5);   //PWM Pins as Out

   while(1)
   {
	  u16_ADCValue= ADC_Read(0);
	  u16_ADCValue /= 3;
      OCR1A = u16_ADCValue;   //0 degree
      _delay_ms (20);

   }
}
