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

FILE * arduinoPort;

void arduinoCallback( const std_msgs::String& msgArduino)
{ 
	char buf[16];
	sprintf(buf, "%s", msgArduino.data.c_str());
	fputs(buf, arduinoPort);
	fflush (arduinoPort);
	ros::Duration(0.05).sleep(); // put at least 50 msec between serial port outputs
}

int main(int argc, char** argv)
{
  arduinoPort = fopen (ARDUINO_FILENAME, "w");
  ros::init(argc, argv, "serialCommands");
  ros::NodeHandle nh_;
  ros::Subscriber arduino_sub = nh_.subscribe("arduino_commands", 60, arduinoCallback);
  ros::spin();
  fclose(arduinoPort);
}
