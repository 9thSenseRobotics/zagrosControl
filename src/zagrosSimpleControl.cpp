// This controls a robot base with input commands from skype chat
// The commands are wasd format, w = forward, a = left, s = backward, d = right


// It is derived from TurtlebotTeleop in the Turtlebot package from Willow Garage
// Copyright (c) 2011, 9th Sense, Inc.
// All rights reserved.

// For the Willow Garage parts of the code:
/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 */
 
 // For all of this code:
 
 /*
 * Copyright (c) 2010, Willow Garage, Inc.
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

#define DEFAULT_SPEED 255	// 0 to 255
#define ARDUINO_FILENAME "/dev/ttyACM0"
#define END_COMMAND_CHARACTER '#'

#include <ros/ros.h>
#include <std_msgs/String.h>

FILE * fp;

class ZagrosSkypeCmd
{
public:
  ZagrosSkypeCmd();

private:
  void skypeCallback(const std_msgs::String& msgSkype);
  void sendCommand();
  void moveForward();
  void moveBackward();
  void turn();
  void Pan();
  void Tilt();
  ros::NodeHandle nh_;
  ros::Subscriber skypechat_sub;
  int numSteps, cmdTime, cmdSpeed, cmdChar;
};

ZagrosSkypeCmd::ZagrosSkypeCmd()
{
  skypechat_sub = nh_.subscribe("SkypeChat", 10, &ZagrosSkypeCmd::skypeCallback, this);
}

void ZagrosSkypeCmd::skypeCallback( const std_msgs::String& msgSkype)
{ 
    numSteps = strlen( (const char* ) msgSkype.data.c_str());
    if ( numSteps > 10 ) numSteps = 2;  // likely just a mistake of holding down too many characters
    else if (numSteps > 5) numSteps = 5;
    for (int i = 1; i < numSteps; i++) if ( (msgSkype.data[i] != msgSkype.data[0]) && msgSkype.data[i] != msgSkype.data[0] + 32) return; 
          // if string is not all identical characters, allowing for first character to be a capital, return    
    cmdChar = msgSkype.data[0];   					
    if (cmdChar != 'W' && cmdChar != 'w' && cmdChar != 'A' && cmdChar != 'a' && cmdChar != 'S' && cmdChar != 's' && cmdChar != 'D' && cmdChar != 'd')
    { 				
		cmdSpeed = numSteps;	// not a motor command, so it is either a servo command or a mistake.  This sets the size of the servo move.
		if (cmdChar != 'U' && cmdChar != 'u' && cmdChar != 'H' && cmdChar != 'h' && cmdChar != 'J' && cmdChar != 'j'
		    && cmdChar != 'K' && cmdChar != 'k' && cmdChar != 'N' && cmdChar != 'n'&& cmdChar != 'M' && cmdChar != 'm' ) return; // unknown command
		else cmdSpeed = DEFAULT_SPEED;	// motor command
    }   
    cmdTime = (2 * numSteps) - 1;  // numSteps here can range from 1 to 5, so we can get 1, 3, 5, 7, 9 and that is correct, since it will get 
    				// multiplied by MIN_TIME in the arduino code 
    sendCommand();
}
     
void ZagrosSkypeCmd::sendCommand()
{
	char buf[16];
	sprintf(buf, "%c%d%d%c", cmdChar, cmdTime, cmdSpeed, END_COMMAND_CHARACTER);
	fputs(buf, fp);
	fflush (fp);
}

int main(int argc, char** argv)
{
  fp = fopen (ARDUINO_FILENAME, "w");
  ros::init(argc, argv, "zagrosSimpleControl");
  ZagrosSkypeCmd zagrosSimpleControl;
  ros::spin();
  fclose (fp);
}
