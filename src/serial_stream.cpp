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

#define PORT "/dev/ttyACM0"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <sstream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

SerialStream mySerial;
ros::Publisher  arduino_pub;

void sendSerial(string Data)
{
    cout << "sending string = " << Data << endl;
    mySerial << Data;
}
    
int getSerial(){
    int res;
    char str[16];
    mySerial.read(str,2);
    sscanf(str,"%d",&res);
    return res;
}

void arduinoCallback( const std_msgs::String& msgArduino)
{ 
	char buf[16];
	sprintf(buf, "%s", msgArduino.data.c_str());
	std::cout << "sending string to serial port, string is " << msgArduino.data.c_str() << std::endl;
	mySerial << buf;
	
    char cmdChar = msgArduino.data[0];
	int batteryPercent = -1;
	if (cmdChar == 'B' || cmdChar == 'b')   // asking for battery percentage
	{
        batteryPercent = getSerial();
        std::cout << "battery percentage = " << batteryPercent << std::endl;
	    std_msgs::String arduinoCommand;
	    arduinoCommand.data = batteryPercent;
	    arduino_pub.publish(arduinoCommand);
	 }
	 else ros::Duration(0.05).sleep(); // put at least 50 msec between serial port outputs
}	    
	    
int main(int argc, char** argv)
{
    cout << "opening port" << endl;
    mySerial.Open(PORT);
    mySerial.SetBaudRate(SerialStreamBuf::BAUD_9600);
    mySerial.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    cout << "port open" << endl;
    
    ros::init(argc, argv, "serialCommands");
    ros::NodeHandle nh_;
    ros::Subscriber arduino_sub = nh_.subscribe("arduino_commands", 60, arduinoCallback);
    arduino_pub = nh_.advertise<std_msgs::String>("arduino_sensors", 5);
    ros::spin();
    mySerial.Close();
}
