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

#define ARDUINO_FILENAME_PRIMARY "/dev/ttyACM0"
#define ARDUINO_FILENAME_SECONDARY "/dev/ttyACM1"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

FILE * arduinoPort;
ros::Publisher  arduino_pub;
bool firstRead;

int readSerialFromArduino()
{
    char buf[16];
    for (int i=0; i < 16; i++) buf[i] = 0;

    //std::cout << "about to read port" << std::endl;
    int result = fread(buf,1,1,arduinoPort);
    // results contains the number of bytes read
    // fread parameters are buf = memory block, 1 = size in bytes of each element, count = number of elements
    // if the arduino does a Serial.println("XYZ"); then size = 1 and count = 3
    // if the arduino does a Serial.write('A') or a Serial.print("K")
    // followed by a Serial.println("J"); then size = 1 and count = 2
    // but in testing, it is very robust to getting these numbers right, as long as they are
    // at least as big as the number of bytes you want to get read in
    //std::cout << "serial port read: " << result << std::endl;
    
    if (result <= 0)  return -1;
    //fflush (Port);
    int batteryPercent =  (int) buf[0];
    std::cout << "battery percentage = " << batteryPercent << std::endl;
    //std::cout << "values = " << buf[0] << buf[1] << buf[2] << buf[3] << buf[4] << std::endl;

    return batteryPercent;
}

void arduinoCallback( const std_msgs::String& msgArduino)
{ 
	char buf[16];
	for (int i=0; i < 16; i++) buf[i] = 0;

	sprintf(buf, "%s", msgArduino.data.c_str());
	std::cout << "sending string to serial port, string is " << msgArduino.data.c_str() << std::endl;
	rewind(arduinoPort);
	fwrite(buf, sizeof(buf),arduinoPort);
	//fflush (arduinoPort);
	char cmdChar = msgArduino.data[0];
	int batteryPercent = -1;
	if (cmdChar == 'B' || cmdChar == 'b')   // asking for battery percentage
	{
	    int counter = 0;
	    ros::Duration(0.5).sleep(); // give the arduino a moment to respond to the write request	        
	    while (counter < 3)
	    {
	        batteryPercent = readSerialFromArduino();
	        if (batteryPercent > -1) break;
            ros::Duration(1.0).sleep();
	        counter++;
	        std::cout << "serial port read failed on try " << counter << std::endl;
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
    arduinoPort = fopen(ARDUINO_FILENAME_PRIMARY, "r+"); 
    if (arduinoPort == NULL)
    {
        arduinoPort = fopen (ARDUINO_FILENAME_SECONDARY, "r+");
        if (arduinoPort == NULL)
        {
            std::cout << "Serial port failed to open for writing."  << std::endl;
        }
    }     
    ros::init(argc, argv, "serialCommands");
    ros::NodeHandle nh_;
    ros::Subscriber arduino_sub = nh_.subscribe("arduino_commands", 60, arduinoCallback);
    arduino_pub = nh_.advertise<std_msgs::String>("arduino_sensors", 5);
    firstRead = true;
    ros::spin();
    fclose(arduinoPort);
}
