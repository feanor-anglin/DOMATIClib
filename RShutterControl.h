/*
 * 
 */


#ifndef RShutterControl_h
#define RShutterControl_h

#include "Arduino.h"
#include <EEPROM.h>
#include "NodeDefinitions.h"
#include "PowerSensor.h"
#include "UniversalInput.h"

#ifndef PS_OFFSET
#define PS_OFFSET 0.2
#endif

#ifndef CALIBRATION_SAMPLES
#define CALIBRATION_SAMPLES 2
#endif

class RShutterControl
{
  public:
    RShutterControl(int UpPin, int DownPi);

    int Position;

    void Calibration();     // Find up and down time by measuring current, save values to eeprom for use even after power failure
    int Move(int Direction);
    void Stop();

  private:
    int _UpPin;
    int _DownPin;
    int _UpTime;
    int _DownTime;

    PowerSensor PS;
        
};

#endif
