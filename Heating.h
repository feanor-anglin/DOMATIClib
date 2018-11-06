/*
 * This is a library designed to control a multi-section heating controller.
 * It uses hysteresis principle to compare set points to temperature values from other sensors
 * (remote temperature nodes) and decide when to open/close heating valves. 
 * For now, IDs of remote temperature nodes are hard written in NodeDefinitions.h, 
 * but it is planned to prepare a pairing functionality in the future. 
 * 
 */

#ifndef Heating_h
#define Heating_h

#include "Arduino.h"
#include <EEPROM.h>

#ifndef RELAY_ON
#define RELAY_ON HIGH
#endif

#ifndef RELAY_OFF
#define RELAY_OFF LOW
#endif

#ifndef DEFAULT_DAY_SP
#define DEFAULT_DAY_SP 20
#endif

class Heating
{
  public:
    Heating();
    
    bool RelayState;                               // Current relay state

    void SetRelay(bool NewState);
    int SetSectionValues(int RelayPin, int T_ID, int EEPROM_ADDRESS);
    void SetTemperature(float Temperature);
    void ReadTemperature(float Temperature);
    bool TemperatureCompare(float TemperatureSet, float Hysteresis);
    float GetSetTemp();
    int GetTID();

  private:
    int _EEPROM_ADDRESS;                           // EEPROM address of first value stored in eeprom by the section
    int _RelayPin;                                 // Relay pin to control the valve
    int _T_ID;                                     // Remote temperature sensor ID
    float _TemperatureSet;                         // Temperature set by controller for daytime
    float _TemperatureSensor;                      // Temperature send by remote nodes
};




#endif
