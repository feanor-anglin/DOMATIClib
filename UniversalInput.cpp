/*
 * PinShift - variable corresponding to arythmetical difference
 * between a sensor and its pin
 */

#include "UniversalInput.h"

/*  *******************************************************************************************
 *                                      Constructor
 *  *******************************************************************************************/
UniversalInput::UniversalInput()  {
  
  NewState = 0;
  OldState = 0;
}

/*  *******************************************************************************************
 *                                		Set Values Security
 *  *******************************************************************************************/
void UniversalInput::SetValuesS(int SensorPin) {

  SensorType = 0;
	_SensorPin = SensorPin;
  pinMode(_SensorPin, INPUT_PULLUP);
}

/*  *******************************************************************************************
 *                                		Set Values Button
 *  *******************************************************************************************/
void UniversalInput::SetValuesB(int ButtonPin) {

  SensorType = 1;
	_SensorPin = ButtonPin;
  pinMode(_SensorPin, INPUT_PULLUP);
}

/*  *******************************************************************************************
 *                                		Set Values Button+relay
 *  *******************************************************************************************/
void UniversalInput::SetValuesBR(int RelayPin, int ButtonPin) {

  SensorType = 2;
	_RelayPin = RelayPin;
	_SensorPin = ButtonPin;
  pinMode(_RelayPin, OUTPUT);
  pinMode(_SensorPin, INPUT_PULLUP);
  digitalWrite(_RelayPin, RELAY_OFF);
}

/*  *******************************************************************************************
 *                                      Input Check
 *  *******************************************************************************************/
void UniversalInput::CheckInput() {

  if(SensorType == 0) {   // Security sensor
    if(digitalRead(_SensorPin) == LOW)  {
      NewState = 0;
    }
    else if(digitalRead(_SensorPin) != LOW)  {
      NewState = 1;
    }
  }
  else if(SensorType == 1 || SensorType == 2)  {   // Button
    
    if(digitalRead(_SensorPin) != LOW)  {
      _HighStateDetection = true;
      _LowStateDetection = false;
      _Condition = false;
    }
    if(_HighStateDetection == true) {
      unsigned long StartTime = millis();
      while(digitalRead(_SensorPin) == LOW)  {
        _LowStateDetection = true;
        _HighStateDetection = false;
        if(millis() - StartTime > 1000) {
          _Condition = true;
          break; 
        }
      }
      if(_Condition == false && _LowStateDetection == true) {
        if(OldState == 0) {
          NewState = 1;
        }
        else if(OldState == 1)  {
          NewState = 0;
        }
      }
      else if(_Condition == true) {
        NewState = 2;
      }
    }
  }
}

/*  *******************************************************************************************
 *                                			Set Relay
 *  *******************************************************************************************/
void UniversalInput::SetRelay() {

	digitalWrite(_RelayPin, NewState);
	OldState = NewState;
}
/*
 * 
 * EOF
 * 
 */




