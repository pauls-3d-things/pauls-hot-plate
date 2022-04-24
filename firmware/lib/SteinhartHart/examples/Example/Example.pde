/**
 * Example sketch for the SteinhartHart library.
 */

#include "SteinhartHart.h"

/* *
 * Instantiate with reading pin 0.
 * Defaults can be overridden in the constructor call.
 *
 * Example: SteinhartHart sh(0, 1000.0) for a NTC 10k thermistor
 * with a 1k voltage divider.
 */
SteinhartHart sh(0);

double temp = 0.0;


void setup(void)
{
	Serial.begin();
}


void loop(void) 
{
	double curTemp = sh.getTempCelsius();
	
	if(temp != curTemp)
	{
		temp = curTemp;
		Serial.print("Temperature in °C: ");
		Serial.println(temp);
	}
	
	delay(1000);
}
