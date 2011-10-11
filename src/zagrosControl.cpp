// This controls a robot base with input commands from skype chat
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
#define DRIVING_FORWARD 1
#define DRIVING_BACKWARD 2
#define DRIVING_TURNLEFT 3
#define DRIVING_TURNRIGHT 4

#define MAX_FORWARD_SPEED 255  // speeds are 0 - 255
#define MAX_BACKWARD_SPEED 255
#define MAX_TURN_SPEED 255		// turns 0 - 255
#define MIN_FORWARD_SPEED 150
#define MIN_BACKWARD_SPEED 150
#define MIN_TURN_SPEED 150
#define DELTA_FORWARD_SPEED 20
#define DELTA_BACKWARD_SPEED 20
#define DELTA_TURN_SPEED 20
#define DEFAULT_FORWARD_SPEED 255
#define DEFAULT_BACKWARD_SPEED 255
#define DEFAULT_TURN_SPEED 255

#define ARDUINO_FILENAME "/dev/ttyACM0"

#define RAMPUP_SPEED_DELAY 100  // controls how long between speed steps when ramping up from a stop to default speed
#define MIN_TURN_TIME 1	// 1 to 9
#define MIN_MOVE_TIME 1
#define TIME_OUT 8000.  // number of milliseconds to wait for command before you consider it a timeout and stop the base
#define TURN_OFF_CREATE 900000.  // number of milliseconds of inactivity before powering down base to save battery power

#define END_COMMAND_CHARACTER '#'

#include <ros/ros.h>
#include <std_msgs/String.h>

FILE * fp;
char buf[16];
std::string cmdString;
int cmdTime, cmdSpeed;

class ZagrosSkypeCmd
{
public:
  ZagrosSkypeCmd();

private:
  void skypeCallback(const std_msgs::String& msgSkype);
  void moveForward();
  void moveBackward();
  void turn();
  ros::NodeHandle nh_;
  int numSteps, driving;
  std_msgs::String ReceivedCommands; 
  ros::Subscriber skypechat_sub;
  ros::Publisher cmd_pub_;
};

ZagrosSkypeCmd::ZagrosSkypeCmd()
{
  cmd_pub_ = nh_.advertise<std_msgs::String>("robot_commands", 1);
  skypechat_sub = nh_.subscribe("SkypeChat", 10, &ZagrosSkypeCmd::skypeCallback, this);
}

void ZagrosSkypeCmd::skypeCallback( const std_msgs::String& msgSkype)
{ 
    ReceivedCommands = msgSkype;
    cmd_pub_.publish(ReceivedCommands);
    ROS_INFO("%s", ReceivedCommands.data.c_str());
    numSteps = strlen( (const char* ) ReceivedCommands.data.c_str());
    if ( numSteps > 10 ) numSteps = 2;  // likely just a mistake of holding down too many characters
    else if (numSteps > 5) numSteps = 5;
    for (int i = 1; i < numSteps; i++) if ( (msgSkype.data[i] != msgSkype.data[0]) && msgSkype.data[i] != msgSkype.data[0] + 32) return; 
          // if string is not all identical characters, allowing for first character to be a capital, return    
    char cmd = msgSkype.data[0]; 
    switch(cmd)
    {
      /*
      case 'z':    // stop
      case 'Z': 
        ReceivedCommands.data = "command issued to stop";
        cmd_pub_.publish(ReceivedCommands);
        break;
         
      case 'x':    // stop
      case 'X':    // stop
        stop();
        ReceivedCommands.data = "command issued to stop";
        cmd_pub_.publish(ReceivedCommands);
        break;
       */
      
      case 'w':  // move forward
      case 'W':
        ReceivedCommands.data = "command issued to move forward";
        cmd_pub_.publish(ReceivedCommands);
        driving = DRIVING_FORWARD;
        moveForward();
        break;
        
      case 's':  //move backward
      case 'S':
        ReceivedCommands.data = "command issued to move backward";
        cmd_pub_.publish(ReceivedCommands);
        driving = DRIVING_BACKWARD;
        moveBackward();
        break;
        
      case 'd':  //turn right
      case 'D':
        driving = DRIVING_TURNRIGHT;
        ReceivedCommands.data = "command issued to turn right";
        cmd_pub_.publish(ReceivedCommands);
        turn();
        break;
         
      case 'a':  // turn left
      case 'A':
        driving = DRIVING_TURNLEFT;
        ReceivedCommands.data = "command issued to turn left";
        cmd_pub_.publish(ReceivedCommands);
        turn();
        break;
      
      /*
      case 'p':    // toggle power
      case 'P':    // toggle power
        ReceivedCommands.data = "command issued to toggle Create power";
        cmd_pub_.publish(ReceivedCommands);
        togglePower();
        break;
      */
        
      default:  // unknown command
        //stop();  w// we need to ignore, not stop because otherwise we will stop when people are just saying stuff like "hi"
        break;
    }
}

/*
void ZagrosSkypeCmd::togglePower()
{
	fputc ('y', fp);
}
*/

void ZagrosSkypeCmd::moveForward()
{
 cmdTime = MIN_MOVE_TIME * numSteps;
 cmdSpeed = DEFAULT_FORWARD_SPEED;
 sprintf(buf, "%c%d%d%c", 'F', cmdTime, cmdSpeed, END_COMMAND_CHARACTER);
 fputs(buf, fp);
 fflush (fp); 

 /*
  else  // use ramp up and ramp down
  {
    cmdSpeed = MIN_FORWARD_SPEED;
    while (cmdSpeed < DEFAULT_FORWARD_SPEED)  // ramp up to speed from a stop
    {
        cmdSpeed += DELTA_FORWARD_SPEED;
 
    }
    for (int i = 1; i < numSteps; i++)
    {
      vel.linear.x += DELTA_FORWARD_SPEED;
      if (vel.linear.x <= MAX_FORWARD_SPEED) publish();
      delay(RAMPUP_SPEED_DELAY);
    }
    delay(MIN_MOVE_TIME * ( (3 * numSteps) - 6 ));  // numSteps here can range from 2 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT 
    slowStop();
  }
  */
}

void ZagrosSkypeCmd::moveBackward()
{
 cmdTime = MIN_MOVE_TIME * numSteps;
 cmdSpeed = DEFAULT_BACKWARD_SPEED;
 sprintf(buf, "%c%d%d%c", 'B', cmdTime, cmdSpeed, END_COMMAND_CHARACTER);
 fputs(buf, fp);
 fflush (fp); 
 
 /*cmdString = "B";
 if (numSteps == 1)     // just get it done
 {      
	//goTime = MIN_MOVE_TIME * numSteps:
	cmdString += MIN_MOVE_TIME;
	cmdString += DEFAULT_BACKWARD_SPEED;
	cmdString += "\n";
	fputs (cmdString.c_str(), fp);
 }
  	
  	vel.angular.z = 0;
  if (numSteps == 1) 
  {
    vel.linear.x = DEFAULT_BACKWARD_SPEED;
  	publish();
    delay(MIN_MOVE_TIME);
    stop();
  }
  else
  {
    vel.linear.x = MIN_BACKWARD_SPEED;
    publish();
    vel.linear.x = MIN_BACKWARD_SPEED;
    while (vel.linear.x > DEFAULT_BACKWARD_SPEED)  // ramp up to speed from a stop, note that these are negative numbers
    {
        vel.linear.x += DELTA_BACKWARD_SPEED;
        publish();
        delay(RAMPUP_SPEED_DELAY);
    }
    for (int i = 1; i < numSteps; i++)
    {
      vel.linear.x += DELTA_BACKWARD_SPEED;
      if (vel.linear.x >= MAX_BACKWARD_SPEED) publish();
      delay(RAMPUP_SPEED_DELAY);
    }
    delay(MIN_MOVE_TIME * ( (3 * numSteps) - 6 ));  // numSteps here can range from 2 to 5, so we can get 0, 3MMT, 6MMT, and 9MMT 
    if (numSteps > 3) delay(1000);  // for longer runs, add some extra time
    slowStop();
  }
  */
}

void ZagrosSkypeCmd::turn()
{
 cmdTime = MIN_MOVE_TIME * numSteps;
 cmdSpeed = DEFAULT_TURN_SPEED;
 if (driving == DRIVING_TURNRIGHT) sprintf(buf, "%c%d%d%c", 'R', cmdTime, cmdSpeed, END_COMMAND_CHARACTER);
 else sprintf(buf, "%c%d%d%c", 'L', cmdTime, cmdSpeed, END_COMMAND_CHARACTER);
 fputs(buf, fp);
 fflush (fp); 
 
 /*
  if (driving == DRIVING_TURNRIGHT) cmdString = "R";
 else cmdString = "L";
 if (numSteps == 1)     // just get it done
 {      
	cmdString += MIN_TURN_TIME;
	cmdString += DEFAULT_TURN_SPEED;
	cmdString += "\n";
	fputs (cmdString.c_str(), fp);
 }
  
  
  vel.angular.z = -DEFAULT_TURN_SPEED;
  else vel.angular.z = DEFAULT_TURN_SPEED;
  publish();
  delay(MIN_TURN_TIME * numSteps);  // numSteps here can range from 1 to 5, so we can get 1, 3MMT, 9MMT, 13MMT, and 17MT numSteps);
  if (numSteps > 3) delay(500);  // for longer runs, add some extra time
  stop();
  */
 }

/*
void ZagrosSkypeCmd::slowStop()
{
  if (driving < 3) // not turning
  {
    vel.angular.z = 0;
    while (vel.linear.x > MIN_FORWARD_SPEED) 
    {
        vel.linear.x -= DELTA_FORWARD_SPEED;
        publish();
        delay(RAMPUP_SPEED_DELAY);
    }
    while (vel.linear.x < MIN_BACKWARD_SPEED)  // negative numbers here
    {
        vel.linear.x -= DELTA_BACKWARD_SPEED;
        publish();
        delay(RAMPUP_SPEED_DELAY);
    }
  }
  else  // turning
  { 
    int absTurnSpeed = abs(vel.angular.z);
    vel.linear.x = 0;
    while (absTurnSpeed > MIN_TURN_SPEED)
    {
      absTurnSpeed -= DELTA_TURN_SPEED;
      if (driving == DRIVING_TURNRIGHT) vel.angular.z = absTurnSpeed; 
      else vel.angular.z = -absTurnSpeed; 
      publish();
      delay(RAMPUP_SPEED_DELAY);
    }
  }
  stop();
}

void ZagrosSkypeCmd::stop()
{
  vel.angular.z = 0;
  vel.linear.x = 0;
  publish();
  last_published_ = vel;
  driving = DRIVING_NONE;
}

void ZagrosSkypeCmd::delay(float delayMsec)
{
	ros::Duration(delayMsec/1000.).sleep(); 
}

void ZagrosSkypeCmd::publish()
{
  boost::mutex::scoped_lock lock(publish_mutex_);
  vel_pub_.publish(vel);
  //ReceivedCommands.data = "velocities published";
  //ROS_INFO("%s", ReceivedCommands.data.c_str());
  //cmd_pub_.publish(ReceivedCommands);
  
}
*/

int main(int argc, char** argv)
{
  fp = fopen (ARDUINO_FILENAME, "w");
  //setvbuf ( fp, buf, _IOLBF, 16 );	// set file for line buffering, so data is written when a newline character is used
  										// or when the buffer is full, whatever happens first.
  ros::init(argc, argv, "zagrosControl");
  ZagrosSkypeCmd zagrosControl;

  /*
  while (nh_.ok()) 
  {
  	//ros::Duration(delayMsec/1000.).sleep();
  	usleep(100000); 
    ros::spinOnce();
  }
  */
  ros::spin();
  fclose (fp);
}
