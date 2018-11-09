/*
 * 
 * 
 * SensorType:
 * 0 - security sensor (door/window or pir)
 * 1 - button
 */

#ifndef UniversalInput_h
#define UniversalInput_h

#include "Arduino.h"

#ifndef UI_SENSORS_NUMBER
#define UI_SENSORS_NUMBER 5  // ilosc UI sensorow
#endif

//#ifndef UI_PIN_SHIFT
//#define UI_PIN_SHIFT 2          // roznica pomiedzy sensorem a pinem
//#endif

#ifndef RELAY_ON
#define RELAY_ON HIGH
#endif

#ifndef RELAY_OFF
#define RELAY_OFF LOW
#endif


class UniversalInput
{
  public:
	UniversalInput();								                      // SensorType: 0 - security type, 1 - button type, 2 - button+relay type, 3 - relay only

  int SensorType;
	int NewState;
	int OldState;
  
	void SetValuesS(int SensorPin);								        // Security input type
	void SetValuesB(int ButtonPin);								        // Button input type
	void SetValuesBR(int RelayPin, int ButtonPin);				// Button+Relay input type
  void SetValuesR(int RelayPin);                        // Message input/Relay output type
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
