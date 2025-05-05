/*  
  Baran Bolat
  20.04.2025
  ADC_exercise
*/

#include <Arduino.h>

volatile bool readADC = false; 

void setup() 
{
  // Setup for reference voltag ==> 5V
  ADMUX |= (1<<REFS0);  // REFS0 = 1 
  ADMUX &= ~(1<<REFS1); // REFS1 = 0

  ADMUX &= 0b0000; // analog input 0

  ADCSRA |= (1<<ADEN); //Enable ADC

  // Setup for Prescaler
  ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); 

  // Timer1 as Normal Mode
  TCCR1A = 0;
  TCCR1B = 0;

  // Timer as CTC
  TCCR1B |= (1<<WGM12);

  // Prescaler to 1
  TCCR1B |= (1<<CS10) | (1<<WGM12);

  OCR1A = 7812;
  TIMSK1 |= (1<<OCIE1A);

  sei(); // Enable interrupts
  Serial.begin(115200); 
}

void loop() 
{

  if(readADC)
  {
    // Start ADC
    ADCSRA |=(1<<ADSC);

    while(ADCSRA & (1<<ADSC));
    int analogValue = ADC; // Read analog (ADC) value
    float voltage = (ADC * 5.0) /1023.0; // convert analog value to voltage value

    // print out voltage value to serial monitor
    Serial.print("Potentiometer analog value = ");
    Serial.print(voltage); 
    Serial.println(" V");
  }

}

ISR(TIMER1_COMPA_vect)
{
  readADC = true;
}

