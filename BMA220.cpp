 /*
  BMA220.h - Library for reading the BMA220 Accel
  Created by TurtleForGaming.
  Shared under the GNU General Public License v3.0
*/

#include "Arduino.h"
#include "BMA220.h"
#include "Wire.h"

BMA220::BMA220() {
}

void BMA220::begin(int range, int divi) {
	Wire.begin();
	Wire.beginTransmission(0x0A); // address of the accelerometer
	// range settings
	Wire.write(0x22); //register address
	Wire.write(range); //can be set at"0x00""0x01""0x02""0x03", refer to Datashhet on wiki
	// low pass filter
	Wire.write(0x20); //register address
	Wire.write(0x05); //can be set at"0x05""0x04"......"0x01""0x00", refer to Datashhet on wiki
	Wire.endTransmission();
	_range = range;
	_divi = divi;
}


AccelResult BMA220::read()
{
	Wire.beginTransmission(0x0A); // address of the accelerometer
	Wire.write(0x04); // X data
	Wire.endTransmission();
	Wire.requestFrom(0x0A,1);		// request 6 bytes from slave device #2
	while(Wire.available()) {		// slave may send less than requested
		_Version[0] = Wire.read();   // receive a byte as characte
	}
	_xdata_raw=(int8_t)_Version[0]>>2;


	Wire.beginTransmission(0x0A); // address of the accelerometer
	Wire.write(0x06); // Y data
	Wire.endTransmission();
	Wire.requestFrom(0x0A,1);		// request 6 bytes from slave device #2
	while(Wire.available()) {		// slave may send less than requested
		_Version[1] = Wire.read();   // receive a byte as characte
	}
	_ydata_raw=(int8_t)_Version[1]>>2;


	Wire.beginTransmission(0x0A); // address of the accelerometer
	Wire.write(0x08); // Z data
	Wire.endTransmission();
	Wire.requestFrom(0x0A,1);		// request 6 bytes from slave device #2
	while(Wire.available())	{	    // slave may send less than requested
		_Version[2] = Wire.read();   // receive a byte as characte
	}
	_zdata_raw=(int8_t)_Version[2]>>2;
	
	AccelResult r;
	r.x = (float)_xdata_raw/_divi;
	r.y = (float)_ydata_raw/_divi;
	r.z = (float)_zdata_raw/_divi;
	
	return r;
}

byte BMA220::getChipId()
{
	Wire.beginTransmission(0x0A); // address of the accelerometer
	Wire.write(0x00); // X data
	Wire.endTransmission();
	Wire.requestFrom(0x0A,1);		// request 6 bytes from slave device #2
	
	byte r;
	while(Wire.available()) {		// slave may send less than requested
		r = Wire.read();            // receive a byte as characte
	}
	return r;
}

byte BMA220::getRevisionId()
{
	Wire.beginTransmission(0x0A); // address of the accelerometer
	Wire.write(0x02); // X data
	Wire.endTransmission();
	Wire.requestFrom(0x0A,1);		// request 6 bytes from slave device #2
	
	byte r;
	while(Wire.available()) {		// slave may send less than requested
		r = Wire.read();            // receive a byte as characte
	}
	return r;
}
