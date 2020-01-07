 /*
  BMA220.h - Library for reading the BMA220 Accel
  Created by TurtleForGaming.
  Shared under the GNU General Public License v3.0
*/

#ifndef BMA220_h
#define BMA220_h

#include "Arduino.h"
#include "Wire.h"

struct AccelResult {
  float x;
  float y;
  float z;
};
  
class BMA220
{

	public:
		BMA220();
		void begin(int range, int divi);
		AccelResult read();
		byte getChipId();
		byte getRevisionId();
	private:
		int _range;
		int _divi;
		int8_t _xdata_raw;
		int8_t _ydata_raw;
		int8_t _zdata_raw;
		byte _Version[3];
};

#endif 
