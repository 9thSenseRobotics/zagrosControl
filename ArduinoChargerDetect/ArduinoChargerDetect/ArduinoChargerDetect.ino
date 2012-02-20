/*
Copyright (c) 2012, 9th Sense, Inc.
All rights reserved.

  ArduinoChargerDetect.ino
     Detect the presence of the battery charger, and command the computer to shut down after it's 
     there consistently for three seconds

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define SerialSpeed 9600
#define chargingDetectionPin 2 // detects presence of battery charger

#define BATTERY_CHARGING_SHUTDOWN_TIME 3000 // in ms

long currentTime = 0;
long chargingStartTime = 0;
long chargingElapsedTime = 0;
int inChargingCountdown = false;
int doingShutdown = false;

void setup()
{ 
  Serial.begin(SerialSpeed);   // connect to laptop
  
  pinMode (chargingDetectionPin, INPUT);
   
}
 
void loop()
{ 
  // get a command from the serial port
 // currentTime = millis() / 1000;
  
//  Serial.println(inChargingCountdown);
  int chargingDetectionSensorValue = digitalRead(chargingDetectionPin);
  
  if (!chargingDetectionSensorValue)
  {
   // Serial.println("not in countdown");
    inChargingCountdown = false;
    chargingElapsedTime = 0;
    chargingStartTime = 0;
  } else if (chargingDetectionSensorValue && !inChargingCountdown) {
    // start the countdown
    inChargingCountdown = true;
    chargingStartTime = millis();
    chargingElapsedTime = 0;
  } else { // you're in the countdown. set the elapsed time, and if it's past the time, print shutdown command
    doingShutdown = true;
    chargingElapsedTime = millis() - chargingStartTime;
    inChargingCountdown = true;
    if (chargingElapsedTime >= BATTERY_CHARGING_SHUTDOWN_TIME)
    {
      Serial.println ("charging shutdown");
      inChargingCountdown = false;
    }
  }
}


