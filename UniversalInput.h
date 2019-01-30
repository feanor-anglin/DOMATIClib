/*
 * This is a code written for easy management of digital input/output sensors such as door/window/pir security sensors,
 * buttons and relays. It menages easy sensor initialization, holds sensor states, changes relays states and provides a quite smart 
 * function for reading inputs (including special button functionality which change its state after one second of holding a button).
 * 
 * 
 * SensorType:
 * 0 - Door/window sensor
 * 1 - Motion sensor
 * 2 - Button input
 * 3 - Relay output
 * 4 - Button input + Relay output
 *
 */

#ifndef UniversalInput_h
#define UniversalInput_h

#include "Arduino.h"

#ifndef UI_SENSORS_NUMBER
#define UI_SENSORS_NUMBER 4  // ilosc UI sensorow
#endif

#ifndef RELAY_ON
#define RELAY_ON HIGH
#endif

#ifndef RELAY_OFF
#define RELAY_OFF LOW
#endif


class UniversalInput
{
  public:
  UniversalInput();       

  int SensorType;
  int NewState;
  int OldState;

  void SetValues(int Type, int Pin1, int Pin2=0);
  void CheckInput();
  void SetRelay();
  
  private:
  int _RelayPin;
  int _SensorPin;
  bool _LowStateDetection;
  bool _HighStateDetection;
  bool _Condition;
  
};

#endif
