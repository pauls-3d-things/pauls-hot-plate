/**
 * SteinhartHart.cpp - Library for interacting with NTC thermistors
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "SteinhartHart.h"
#include <math.h>	

	
/**
 * Returns the temperature in kelvin for the given resistance value
 * using the Steinhart-Hart polynom.
 */
double SteinhartHart::steinhartHart(double r)
{
	double log_r  = log(r);
	double log_r3 = log_r * log_r * log_r;

	return 1.0 / (_a + _b * log_r + _c * log_r3);
}


double SteinhartHart::getTempKelvin() 
{
	double adc_raw = analogRead(_reading_pin);
	double voltage = adc_raw / 1024 * V_IN;
	double resistance = ((1024 * _resistance / adc_raw) - _resistance);
	
	// Account for dissipation factor K
	return steinhartHart(resistance) - voltage * voltage / (K * _resistance);
}


double SteinhartHart::getTempCelsius() 
{
	return getTempKelvin() - 273.15;
}


double SteinhartHart::getTempFahrenheit()
{
	return getTempCelsius() * 9/5 + 32;
}
