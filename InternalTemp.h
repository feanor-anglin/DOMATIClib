/*
 * For use with MCP9700A analog temperature sensor
 * mVperC = 10
 * ZeroVoltage = 0.5
 * 
 */


#ifndef InternalTemp_h
#define InternalTemp_h

#include "Arduino.h"

#ifndef MAX_TEMPERATURE
#define MAX_TEMPERATURE 60
#endif

#ifndef MVPERC
#define MVPERC 0.01
#endif

#ifndef ZEROVOLTAGE
#define ZEROVOLTAGE 0.5
#endif

class InternalTemp
{
  public:
    InternalTemp(int SensorPin);
  
    float Temperature;

    float MeasureT();
    bool ThermalStatus(float Temperature);

  private:
    int _SensorPin;
    float _mVperC;
    float _ZeroVoltage;
};


#endif
