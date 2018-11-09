/*
 * Cpp file of Heating.h library
 */

#include "Heating.h"

/*  *******************************************************************************************
 *                                        Constructor
 *  *******************************************************************************************/
Heating::Heating()  {

}

/*  *******************************************************************************************
 *                                   Setting Section Values
 *  *******************************************************************************************/
int Heating::SetSectionValues(int RelayPin, int T_ID, int EEPROM_ADDRESS) {

  float TemperatureSet;

  _EEPROM_ADDRESS = EEPROM_ADDRESS;
  EEPROM.get(_EEPROM_ADDRESS, TemperatureSet);
  if(TemperatureSet < 40.0 && TemperatureSet > 10.0)  {
    _TemperatureSet = TemperatureSet;
  }
  else  {
    _TemperatureSet = DEFAULT_DAY_SP;
  }
  EEPROM_ADDRESS += sizeof(float);
  
  SectionStatus = true;
  
  _T_ID = T_ID;
  
  _RelayPin = RelayPin;
  pinMode(_RelayPin, OUTPUT);
  digitalWrite(_RelayPin, RELAY_OFF);
  
  _TemperatureSensor = -100;

  return EEPROM_ADDRESS;
}

/*  *******************************************************************************************
 *                                    Changing Relay State
 *  *******************************************************************************************/
void Heating::SetRelay(bool NewState) {
  
  if(SectionStatus != false)  {
    digitalWrite(_RelayPin, NewState);
    RelayState = NewState;
  }
}

/*  *******************************************************************************************
 *                               Saving Temperature from Controller
 *  *******************************************************************************************/
void Heating::SetTemperature(float Temperature)  {
  
  _TemperatureSet = Temperature;
  EEPROM.put(_EEPROM_ADDRESS, _TemperatureSet);

}

/*  *******************************************************************************************
 *                                  Get SetPoint Temperature
 *  *******************************************************************************************/
float Heating::GetSetTemp() {
  
  return _TemperatureSet;
}

/*  *******************************************************************************************
 *                                  Get T_ID of this Section
 *  *******************************************************************************************/
int Heating::GetTID() {

  return _T_ID;
}

/*  *******************************************************************************************
 *                             Saving Temperature from Remote Sensor
 *  *******************************************************************************************/
void Heating::ReadTemperature(float Temperature) {
  
  _TemperatureSensor = Temperature;
}

/*  *******************************************************************************************
 *                                 Comparing Temperature Values
 *  *******************************************************************************************/
bool Heating::TemperatureCompare(float TemperatureSet, float Hysteresis) {

  if(_TemperatureSensor != -100)  {
    if(_TemperatureSensor < TemperatureSet) {
      return RELAY_ON;
    }
    else if(_TemperatureSensor >= TemperatureSet+Hysteresis)  {
      return RELAY_OFF;
    }
  }
  else  {
    return RELAY_OFF;
  }
}
/*
 * 
 * EOF
 * 
 */
