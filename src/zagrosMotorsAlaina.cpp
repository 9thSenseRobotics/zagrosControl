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
 
#define DRIVING_NONE 0
#define DRIVING_STRAIGHT 1
#define DRIVING_TURN 2

#define MAX_FORWARD_SPEED 255  // speeds are 0 - 255
#define MAX_TURN_SPEED 255
#define MIN_FORWARD_SPEED 200
#define MIN_TURN_SPEED 255
#define DELTA_FORWARD_SPEED 20
#define DELTA_TURN_SPEED 30
#define DEFAULT_FORWARD_SPEED 255
#define DEFAULT_TURN_SPEED 255

#define MIN_MOVE_TIME 200
#define MIN_TURN_TIME 100

#define END_COMMAND_CHARACTER '#'

#define RAMPUP_TURN_DELAY 100  // controls how long between speed steps when ramping up from a stop to default speed
#define RAMPUP_MOVE_DELAY 200
#define TIME_OUT 8000.  // number of milliseconds to wait for command before you consider it a timeout and stop the base
#define TURN_OFF_MOTOR_POWER 900000.  // number of milliseconds of inactivity before powering down base to save battery power

#include <ros/ros.h>
#include <std_msgs/String.h>

class ZagrosMotorsCmd
{
public:
  ZagrosMotorsCmd();

private:
  void skypeCallback(const std_msgs::String& msgSkype);
  void sendCommand();
  void move();
  void turn();
  void moveNoStop(); // added by alaina
  void turnNoStop(); // added by alaina
  void slowStop();
  void stop();
  void delay(float delayMsec);
  ros::NodeHandle nh_;
  ros::Subscriber skypechat_sub;
  ros::Publisher arduino_pub;
  int numSteps, cmdTime, cmdSpeed, driving;
  char cmdChar;
};

ZagrosMotorsCmd::ZagrosMotorsCmd()
{
  skypechat_sub = nh_.subscribe("SkypeChat", 10, &ZagrosMotorsCmd::skypeCallback, this);
  arduino_pub = nh_.advertise<std_msgs::String>("arduino_commands", 50);
}

void ZagrosMotorsCmd::skypeCallback( const std_msgs::String& msgSkype)
{ 
    numSteps = strlen( (const char* ) msgSkype.data.c_str());
    if ( numSteps > 10 ) numSteps = 2;  // likely just a mistake of holding down too many characters
    else if (numSteps > 5) numSteps = 5;
    for (int i = 1; i < numSteps; i++) if ( (msgSkype.data[i] != msgSkype.data[0]) && msgSkype.data[i] != msgSkype.data[0] + 32) return; 
          // if string is not all identical characters, allowing for first character to be a capital, return    
    cmdChar = msgSkype.data[0];  
     					
    switch(cmdChar)	// motor command
    {     
      case 'w':  // move forward
      case 'W':
      case 's':  //move backward
      case 'S':
        move();
        break;
             
      case 'd':  //turn right
      case 'D':       
      case 'a':  // turn left
      case 'A':
        turn();
        break;

  // ----------------------------------------------------------------------------------
  // this block was added to support GUI driving, e.g., not driving with 1-5 characters
  // alaina 2012-03-12
  // ----------------------------------------------------------------------------------
      case 'o':  // move forward without stopping
      case 'O':  // move forward without stopping
      	cmdChar = 'w'; // reset it to the forward character
        moveNoStop(); // accelerate and drive forward but don't stop after a certain number of steps
        break;
      case 'l':  //move backward without stopping
      case 'L':  //move backward without stopping
      	cmdChar = 's'; // reset to the backward character
        moveNoStop(); // accelerate and drive backward but don't stop after a certain number of steps
        break;
      case 'c':  //turn right without stopping
      case 'C':  //turn right without stopping
      	cmdChar = 'd'; // reset to "turn right" character
        turnNoStop(); // turn but don't stop after a certain number of steps
        break;
      case 'i':  // turn left without stopping
      case 'I':  // turn left without stopping
      	cmdChar = 'a'; // reset to "turn left" character
        turnNoStop(); // turn but don't stop after a certain number of steps
        break;
        
      case 'x':
        slowStop(); // stop with deceleration
  	break;
      case 'z':
  	stop(); // stop with no deceleration
  	break;
  // ----------------------------------------------------------------------------------
  // end block - alaina 2012-03-12
  // ----------------------------------------------------------------------------------
             
      default:  // unknown command
        //stop();  w// we need to ignore, not stop because otherwise we will stop when people are just saying stuff like "hi"
        break;
    }
}

void ZagrosMotorsCmd::move()
{
   // use ramp up and ramp down  
    cmdSpeed = MIN_FORWARD_SPEED;
    while (cmdSpeed < DEFAULT_FORWARD_SPEED)  // ramp up to speed from a stop
    {
       sendCommand();      
       delay(RAMPUP_MOVE_DELAY);
       cmdSpeed += DELTA_FORWARD_SPEED; 
    }
    for (int i = 1; i < numSteps; i++)	// as numSteps gets bigger, go both longer and faster
    {
      sendCommand();
      delay(RAMPUP_MOVE_DELAY);	// give some time for the command to work
      if (cmdSpeed + DELTA_FORWARD_SPEED <= MAX_FORWARD_SPEED) cmdSpeed += DELTA_FORWARD_SPEED;
    }
    // numSteps here can range from 1 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT
    sendCommand();
    delay(MIN_MOVE_TIME * ((2 * numSteps) - 1));  // numSteps here can range from 1 to 5, so we can get 1, 3, 5, 7, 9
    //delay(MIN_TURN_TIME * numSteps);
    driving = DRIVING_STRAIGHT;
    slowStop();
}

void ZagrosMotorsCmd::turn()
{
   // use ramp up and ramp down  
    cmdSpeed = MIN_TURN_SPEED;
    while (cmdSpeed < DEFAULT_TURN_SPEED)  // ramp up to speed from a stop
    {
       sendCommand();      
       delay(MIN_TURN_TIME);
       cmdSpeed += DELTA_TURN_SPEED; 
    }
    for (int i = 1; i < numSteps; i++)	// as numSteps gets bigger, go both longer and faster
    {
      sendCommand();
      delay(RAMPUP_TURN_DELAY);	// give some time for the command to work
      if (cmdSpeed + DELTA_TURN_SPEED <= MAX_TURN_SPEED) cmdSpeed += DELTA_TURN_SPEED;
    }
    // numSteps here can range from 1 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT
    sendCommand();
    delay(MIN_TURN_TIME * ((2 * numSteps) - 1));  // numSteps here can range from 1 to 5, so we can get 1, 3, 5, 7, 9
    //delay(MIN_TURN_TIME * numSteps);
    driving = DRIVING_TURN;
    stop();
}

void ZagrosMotorsCmd::moveNoStop()
// move forward or backward at the given speed, but do it without stopping at the end after a certain number of steps
// added 2012-03-12 by alaina
{
   // use ramp up and ramp down
    cmdSpeed = MIN_FORWARD_SPEED;
    while (cmdSpeed < DEFAULT_FORWARD_SPEED)  // ramp up to speed from a stop
    {
       sendCommand();
       delay(RAMPUP_MOVE_DELAY);
       cmdSpeed += DELTA_FORWARD_SPEED;
    }
    for (int i = 1; i < numSteps; i++)  // as numSteps gets bigger, go both longer and faster
    {
      sendCommand();
      delay(RAMPUP_MOVE_DELAY); // give some time for the command to work
      if (cmdSpeed + DELTA_FORWARD_SPEED <= MAX_FORWARD_SPEED) cmdSpeed += DELTA_FORWARD_SPEED;
    }
    // numSteps here can range from 1 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT
    sendCommand();
    delay(MIN_MOVE_TIME * ((2 * numSteps) - 1));  // numSteps here can range from 1 to 5, so we can get 1, 3, 5, 7, 9
    //delay(MIN_TURN_TIME * numSteps);
    driving = DRIVING_STRAIGHT;
}

void ZagrosMotorsCmd::turnNoStop()
// turn at the given speed, but do it without stopping at the end after a certain number of steps
// added 2012-03-12 by alaina
{
   // use ramp up and ramp down
    cmdSpeed = MIN_TURN_SPEED;
    while (cmdSpeed < DEFAULT_TURN_SPEED)  // ramp up to speed from a stop
    {
       sendCommand();
       delay(MIN_TURN_TIME);
       cmdSpeed += DELTA_TURN_SPEED;
    }
    for (int i = 1; i < numSteps; i++)  // as numSteps gets bigger, go both longer and faster
    {
      sendCommand();
      delay(RAMPUP_TURN_DELAY); // give some time for the command to work
      if (cmdSpeed + DELTA_TURN_SPEED <= MAX_TURN_SPEED) cmdSpeed += DELTA_TURN_SPEED;
    }
    // numSteps here can range from 1 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT
    sendCommand();
    delay(MIN_TURN_TIME * ((2 * numSteps) - 1));  // numSteps here can range from 1 to 5, so we can get 1, 3, 5, 7, 9
    //delay(MIN_TURN_TIME * numSteps);
    driving = DRIVING_TURN;

}


void ZagrosMotorsCmd::slowStop()
{
  if (driving < 2) // not turning
  {
    while (cmdSpeed > MIN_FORWARD_SPEED) 
    {
        cmdSpeed -= DELTA_FORWARD_SPEED;
        sendCommand();
        delay(RAMPUP_MOVE_DELAY);
    }
  }
  else  // turning
  { 
    while (cmdSpeed > MIN_TURN_SPEED)
    {
      cmdSpeed -= DELTA_TURN_SPEED;
      sendCommand();
      delay(RAMPUP_TURN_DELAY);
    }
  }
  cmdSpeed = 0;
  sendCommand();
}

void ZagrosMotorsCmd::stop()
{
	cmdChar = 'X';
	sendCommand();
	driving = DRIVING_NONE;
}

void ZagrosMotorsCmd::delay(float delayMsec)
{
	ros::Duration(delayMsec/1000.).sleep(); 
}

void ZagrosMotorsCmd::sendCommand()
{
		std_msgs::String arduinoCommand;
		std::string cmdString;
		cmdString = cmdChar;
		char buffer[10];
		sprintf(buffer,"%d%c",cmdSpeed, END_COMMAND_CHARACTER);
		cmdString += buffer;
		arduinoCommand.data = cmdString;
		arduino_pub.publish(arduinoCommand);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "zagrosMotors");
  ZagrosMotorsCmd zagrosMotors;
  ros::spin();
}

