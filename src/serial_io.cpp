 // This sends serial port commands
 
 /*
 * Copyright (c) 2012, 9th Sense, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define ARDUINO_FILENAME "/dev/ttyACM0"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

FILE * arduinoPort;
ros::Publisher  arduino_pub;

int readSerialFromArduino()
{
    char buf[16];
    int result = fread (buf,1,1,arduinoPort);
    if (result <= 0) return -1;
    fflush (arduinoPort);
    int batteryPercent =  (int) buf[0]; //(((int)buf[0]) * 10 ) + (int) buf[1];
    std::cout << "battery percentage = " << batteryPercent << std::endl;
    //std::cout << "buf0 = " << buf[0] << "  buf1 = " << buf[1] << std::endl;
    return batteryPercent;
}

void arduinoCallback( const std_msgs::String& msgArduino)
{ 
	char buf[16];
	sprintf(buf, "%s", msgArduino.data.c_str());
	fputs(buf, arduinoPort);
	fflush (arduinoPort);
	char cmdChar = msgArduino.data[0];
	int batteryPercent = -1;
	if (cmdChar == 'B' || cmdChar == 'b')   // asking for battery percentage
	{
	    int counter = 0;
	    while (counter < 10)
	    {
	        batteryPercent = readSerialFromArduino();
	        if (batteryPercent > -1) break;
	        ros::Duration(0.1).sleep();
	        std::cout << "trying to read battery percentage" << std::endl;
	        counter++;
	     }
	     //std::cout << "battery percentage = " << batteryPercent << std::endl;
	     std_msgs::String arduinoCommand;
	     arduinoCommand.data = batteryPercent;
	     arduino_pub.publish(arduinoCommand);
	}        
	else ros::Duration(0.05).sleep(); // put at least 50 msec between serial port outputs
}

int main(int argc, char** argv)
{
  arduinoPort = fopen (ARDUINO_FILENAME, "r+");   
  ros::init(argc, argv, "serialCommands");
  ros::NodeHandle nh_;
  ros::Subscriber arduino_sub = nh_.subscribe("arduino_commands", 60, arduinoCallback);
  arduino_pub = nh_.advertise<std_msgs::String>("arduino_sensors", 5);
  ros::spin();
  fclose(arduinoPort);
}
