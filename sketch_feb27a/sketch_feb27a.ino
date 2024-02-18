#include <TimerOne.h>

const uint8_t displayValues[10] = { 126, 48, 109, 121, 51, 91, 95, 112, 127, 115 }; //valores del display en decimal 
                                  // 0    1   2    3   4   5   6    7    8    9
volatile bool timeSetFlag = false;
volatile double temperatureIntPart, temperature;

void callback(){
	temperature = (5.0 * analogRead(A0) * 100.0) / 1023.0;
	Serial.println(temperature);
	PORTD = PORTB = B00000000; //coloca los 8 puertos a output, b significa binario
	shiftOut(3, 4, LSBFIRST, displayValues[(int) (modf(temperature, &temperatureIntPart) * 10)]);
	shiftOut(6, 7, LSBFIRST, displayValues[(int) temperatureIntPart % 10]);
	shiftOut(11, 12, LSBFIRST, displayValues[(int) temperatureIntPart / 10]);
	PORTD = PORTB = B00100100;
}

void setup(){
	Serial.begin(9600);
	DDRD = DDRB = B11111100;
}

void loop(){
		Timer1.initialize(1000000);
		Timer1.attachInterrupt(callback);
}