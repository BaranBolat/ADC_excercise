/*  
  Baran Bolat
  20.04.2025
  ADC_exercise
*/

#include <Arduino.h>

volatile bool readADC = false; 

void setup() 
{
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);

  ADMUX &= 0b0000;

  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);

  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS10) | (1<<WGM12);

  OCR1A = 7812;
  TIMSK1 |= (1<<OCIE1A);

  sei();
  Serial.begin(115200); 
}

void loop() 
{
  if(readADC)
  {
    ADCSRA |=(1<<ADSC);

    while(ADCSRA & (1<<ADSC));
    int analogValue = ADC;
    float voltage = (ADC * 5.0) /1023.0;

    Serial.print("Potentiometer analog value = ");
    Serial.print(voltage); 
    Serial.println(" V");
  }

}

ISR(TIMER1_COMPA_vect)
{
  readADC = true;
}

