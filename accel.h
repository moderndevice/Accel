/* Accelerometer library for reading accelerometer and converting it to tilt values
Paul Badger 2016
Written for the Modern Device based 3 axis analog accelerometer, but likely useful on
a other accelerometers.
*/

// ensure this library description is only included once
#ifndef Accel_h
#define Accel_h
#include "Arduino.h"


// library interface description
class Accel
{
  // user-accessible "public" interface
  public:
  
  // variables
	int xMax, xMin, yMax, yMin, zMax, zMin, xMid, yMid, zMid, xRng, yRng, zRng ;
	int xPin, yPin, zPin;
	float x, y, z;

	typedef struct  {
	float x;
	float y;
	float z;
	float XYRot;
	}tilt;
    
    typedef struct  {
        int x;
        int y;
        int z;
    }raw;
    
    tilt gtilt;
    raw graw;
			
    // methods	
	// constructor
	Accel(int xPin, int yPin, int zPin);
    Accel(int xPin, int yPin, int zPin, int xMax, int xMin, int yMax, int yMin, int zMax, int zMin );
	
	tilt getTilt90();
	tilt getTilt180();
    void printTiltVals();
    void printRawVals();
		
	// prints raw values to help calibrate the accelerometer
	void calibrateAccel(uint8_t samples);

};
  
#endif