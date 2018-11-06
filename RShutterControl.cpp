/*
 * 
 */

#include "RShutterControl.h"

/*  *******************************************************************************************
 *                                      Constructor
 *  *******************************************************************************************/
RShutterControl::RShutterControl(int UpPin, int DownPin/*, int AddressUpTime, int AddressDownTime, int PS_PIN*/)  {

  int _DownPin = DownPin;
  int _UpPin = UpPin;
  int DownTime = EEPROM.read(EEA_RS_TIME_DOWN);
  int UpTime = EEPROM.read(EEA_RS_TIME_UP);
  
  if(UpTime == 0 || DownTime == 0)  {   //to jest źle!! pusty eeprom trzyma wartosc 255, ale lepiej uzyc dodatkowej zmiennej okreslajacej, ze zapis do eepromu sie powiodl i ja sprawdzac
    Calibration(/*PS_PIN, AddressUpTime, AddressDownTime*/);
  }
  else  {
    _UpTime = UpTime;
    _DownTime = DownTime;
    Position = EEPROM.read(EEA_RS_POSITION);
  }
}

/*  *******************************************************************************************
 *                                        Calibration
 *  *******************************************************************************************/
void RShutterControl::Calibration(/*int PS_PIN, int AddressUpTime, int AddressDownTime*/)  {

  #ifdef MY_DEBUG
    Serial.println("Start Calibration");
  #endif

  // Move the roller shutter from unknown position upwards, stop when there is no current measured
  digitalWrite(_DownPin, RELAY_OFF);  
  digitalWrite(_UpPin, RELAY_ON);

  while(PS.MeasureAC(PS_PIN) > PS_OFFSET)  {     // Tu moze byc problem z okresleniem wartosci pradu
    delay(100);
  }
  digitalWrite(_UpPin, RELAY_OFF);

  // Initialize variables
  int DownTimeCumulated = 0;
  int UpTimeCumulated = 0;
  unsigned long TIME_1 = 0;
  unsigned long TIME_2 = 0;
  unsigned long TIME_3 = 0;

  // Calibration: 1. Move down, 2. Move up, 3. Save measured values
  for(int i=0; i<CALIBRATION_SAMPLES; i++) {

    TIME_1 = millis();
    digitalWrite(_DownPin, RELAY_ON);
    delay(100);
    while(PS.MeasureAC(PS_PIN) > PS_OFFSET) {
      TIME_2 = millis();
    }
    digitalWrite(_DownPin, RELAY_OFF);

    TIME_3 = TIME_2 - TIME_1;
    DownTimeCumulated += (int)(TIME_3 / 1000);

    delay(1000);

    TIME_1 = millis();
    digitalWrite(_UpPin, RELAY_ON);
    delay(100);
    while(PS.MeasureAC(PS_PIN) > PS_OFFSET) {
      TIME_2 = millis();
    }
    digitalWrite(_UpPin, RELAY_OFF);

    TIME_3 = TIME_2 - TIME_1;
    UpTimeCumulated += (int)(TIME_3 / 1000);
  }

  Position = 0;

  _DownTime = (int)(DownTimeCumulated / CALIBRATION_SAMPLES);
  _UpTime = (int)(UpTimeCumulated / CALIBRATION_SAMPLES);

  EEPROM.write(EEA_RS_TIME_DOWN, _DownTime);
  EEPROM.write(EEA_RS_TIME_UP, _UpTime);
  EEPROM.write(EEA_RS_POSITION, Position);
}

int RShutterControl::Move(int Direction)  {
  
  int pin; int pin2; int Time;

  if(Direction = 1) {
    pin = _DownPin; pin2 = _UpPin; Time = _DownTime;
  }
  else if(Direction = 0)  {
    pin = _UpPin; pin2 = _DownPin; Time = _UpTime;
  }
  
  digitalWrite(pin2, RELAY_OFF);
  digitalWrite(pin, RELAY_ON);

  return Time;
}

void RShutterControl::Stop()  {

  digitalWrite(_DownPin, RELAY_OFF);
  digitalWrite(_UpPin, RELAY_OFF);
}

/*  *******************************************************************************************
 *                                   Movement from Buttons
 *  *******************************************************************************************/
/*void RShutterControl::RShutterMove1(int Direction, int UP_ID, int DOWN_ID) {

  int pin; int pin2; int Time;
 
  if(Direction = 0) {
    pin = _DownPin; pin2 = _UpPin; Time = _DownTime;
  }
  else if(Direction = 1)  {
    pin = _UpPin; pin2 = _DownPin; Time = _UpTime;
  }

  digitalWrite(pin2, RELAY_OFF);

  unsigned long TIME_1 = millis();
  unsigned long TIME_2 = 0;
  unsigned long TIME_3 = 0;

  digitalWrite(pin, RELAY_ON);
  while(UI.NewState[UP_ID] == UI.OldState[UP_ID] && UI.NewState[DOWN_ID] == UI.OldState[DOWN_ID]) {
    UI.CheckInput(UP_ID, 1);
    UI.CheckInput(DOWN_ID, 1);
    //wait(100);

    TIME_2 = millis();
    TIME_3 = (TIME_2 - TIME_1) / 1000;

    if(TIME_3 > Time) {
      digitalWrite(pin, RELAY_OFF);
      RSPosition = (Direction == 0 ? 100 : 0);
      break;
    }
  }
  if(digitalRead(pin) != RELAY_OFF) {
    digitalWrite(pin, RELAY_OFF);
    UI.OldState[UP_ID] = UI.NewState[UP_ID];
    UI.OldState[DOWN_ID] = UI.NewState[DOWN_ID];
    int PositionChange = (int)(TIME_3 / Time);
    RSPosition += (Direction == 0 ? PositionChange : -PositionChange);
    RSPosition = RSPosition > 100 ? 100 : RSPosition;
    RSPosition = RSPosition < 0 ? 0 : RSPosition;
  }
  EEPROM.write(EEA_RS_POSITION, RSPosition);
}

/*  *******************************************************************************************
 *                                   Movement from Controller
 *  *******************************************************************************************/
/*void RShutterControl::RShutterMove2(int NewPosition)  {

  float MovementRange = ((float)NewPosition - (float)RSPosition) / 100;       // Downward => MR > 0; Upward MR < 0
  int MovementDirection = MovementRange > 0 ? 1 : -1;
  int MovementTime;

  if(MovementDirection == 1)  {
    MovementTime = _DownTime * abs(MovementRange) * 1000;
    digitalWrite(_DownPin, RELAY_ON);
    wait(MovementTime);
    digitalWrite(_DownPin, RELAY_OFF);
  }
  else if(MovementDirection == -1)  {
    MovementTime = _UpTime * abs(MovementRange) * 1000;
    digitalWrite(_UpPin, RELAY_ON);
    wait(MovementTime);
    digitalWrite(_UpPin, RELAY_OFF);
  }
  RSPosition = NewPosition;
  EEPROM.write(EEA_RS_POSITION, RSPosition);
  
  
}*/

 
/*
 * 
 * EOF
 * 
 */

