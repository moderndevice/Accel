// include this library's description file
#include "accel.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif

Accel::Accel(int X_Pin, int Y_Pin, int Z_Pin){
    /* values for Modern Device MMA7361 based analog accelerometer running on 3.3 volts
     with an Arduino running at 5 volts - otherwise calibration (or new values here) will be required. */
    xMax = 494;  // xr value maximum value
    xMin = 171;  // xr value minimum value
    yMax = 513;  // yr value maximum value
    yMin = 187;  // yr value minimum value
    zMax = 455;  // zr value maximum value
    zMin = 132;  // zr value minimum value
    
    xMid = (xMax + xMin) / 2;  // xr value mid range - board on level surface
    yMid = (yMax + yMin) / 2;  // yr value mid range - board on level surface
    zMid = (zMax + zMin) / 2;  // zr value mid range - board tipped vertically
    xRng = (xMax - xMin);  // 508 max - 177 min
    yRng = (yMax - yMin);  //  529 max - 193 min
    zRng = (zMax - zMin);  //  468 max - 136 min
    
    xPin = X_Pin;  // arduino pin for x - change to your setup
    yPin = Y_Pin;  // arduino pin for y
    zPin = Z_Pin;  // arduino pin for z
}


Accel::Accel(int X_Pin, int Y_Pin, int Z_Pin, int x_Max, int x_Min, int y_Max, int y_Min, int z_Max, int z_Min ){
    xPin = X_Pin;  // arduino pin for x - change to your setup
    yPin = Y_Pin;  // arduino pin for y
    zPin = Z_Pin;  // arduino pin for z
    
    xMax = xMax;  // xr value maximum value
    xMin = xMin;  // xr value minimum value
    yMax = yMax;  // yr value maximum value
    yMin = yMin;  // yr value minimum value
    zMax = zMax;  // zr value maximum value
    zMin = zMin;  // zr value minimum value */
    
    xMid = (xMax + xMin) / 2;  // xr value mid range - board on level surface
    xMid = (yMax + yMin) / 2;  // yr value mid range - board on level surface
    xMid = (zMax + zMin) / 2;  // zr value mid range - board tipped vertically
    xRng = (xMax - xMin);  // 508 max - 177 min
    yRng = (yMax - yMin);  //  529 max - 193 min
    zRng = (zMax - zMin);  //  468 max - 136 min
}


Accel::tilt Accel::getTilt90(){
   // Accel::tilt retTilt;
    int  xr = analogRead(xPin);      // read analog pin for x raw
    int  yr = analogRead(yPin);      // read analog pin for y raw
    int  zr = analogRead(zPin);      // read analog pin for z raw
    
    x = (xr - xMid) / (float)xRng;  //shift range down by midpoint for signed result
    y = (yr - yMid) / (float)yRng;
    z = (zr - zMid) / (float)zRng;
    
    // you might want to comment out tilt calculations below that you are not using as these
    // floating point trig calculations are fairly slow.
    gtilt.x = ((atan2(x, sqrt((y * y) + (z * z)))) * 57.295);
    gtilt.y = (atan2(y, sqrt((x * x) + (z * z)))) * 57.295;
    gtilt.z = atan2(z, sqrt((y * y) + (x * x))) * 57.295;
    gtilt.XYRot = (atan2(gtilt.y, gtilt.x)) * 57.295;
    
    return gtilt;
}

void Accel::printRawVals(){
    int  xr = analogRead(xPin);      // read analog pin for x raw
    int  yr = analogRead(yPin);      // read analog pin for y raw
    int  zr = analogRead(zPin);      // read analog pin for z raw
    Serial.print("x ");
    Serial.print(xr);
    Serial.print("  \t");
    Serial.print("y ");
    Serial.print(yr);
    Serial.print("  \t");
    Serial.print("z ");
    Serial.println(zr);
 
}


void Accel::printTiltVals() {
    Serial.print(gtilt.x); // use "tilt.x", "tilt.y" etc in your program
    Serial.print("\t");   // "\t" is tab character
    Serial.print(gtilt.y);
    Serial.print("\t");
    Serial.print(gtilt.z);
    Serial.print("\t");
    Serial.println(gtilt.XYRot);  // revolve x & y axes around horizontal z axis
}
