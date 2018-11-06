/*
 * 
 */
 
#include "PowerSensor.h"

/*  *******************************************************************************************
 *                                      Constructor
 *  *******************************************************************************************/
PowerSensor::PowerSensor()  {

  _mVperAmp = MVPERAMP;
}

/*  *******************************************************************************************
 *                                   Current Measurement
 *  *******************************************************************************************/
float PowerSensor::MeasureAC(int SensorPin)  {
  
  float Result;

  int ReadValue;
  int MaxValue = 0;
  int MinValue = 1024;

  uint32_t StartTime = millis();
  while((millis() - StartTime) < POWER_MEASURING_TIME)  {
    ReadValue = analogRead(SensorPin);
    if(ReadValue > MaxValue)  {
      MaxValue = ReadValue;
    }
    if(ReadValue < MinValue)  {
      MinValue = ReadValue;
    }
  }

  Result = ((MaxValue - MinValue) * 5.0) / 1024.0;
    
  float VRMS = (Result / 2) * 0.707;
  AmpsRMS = (VRMS * 1000) / _mVperAmp;

  return AmpsRMS;
}

/*  *******************************************************************************************
 *                                      Power Calculation
 *  *******************************************************************************************/
float PowerSensor::CalculatePower(float Current, int ACVoltage)  {

  float Power = Current * ACVoltage;
  
  return Power;
}

/*  *******************************************************************************************
 *                                  Electrical Status Check
 *  *******************************************************************************************/
bool PowerSensor::ElectricalStatus(float Current) {

  if(Current > MAX_CURRENT)  {
    return true;
  }
  else  {
    return false;
  }
}
