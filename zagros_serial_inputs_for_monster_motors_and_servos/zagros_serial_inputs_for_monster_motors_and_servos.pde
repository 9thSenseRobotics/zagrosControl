// accepts serial port inputs and responds with moves

// command form is a letter for direction:
// W, S, A, D, = move forward, move backward, right turn, left turn.
// case does not matter, so w, a, s, d are OK
// followed by the time to move from 1 to 9 which will be multiplied by the MIN_TIME for a move
// followed by the speed to move, 0 to 255
// followed by a character to indicate that the input is complete, in our case that character is #
// for example, move forward for 2 * MIN_TIME with a speed of 200 is
// W2200#
// to turn right for 5 * MIN_TIME at full speed is
// D5255#
// if you wish to use the default time and speed (a defined value), then just the letters is sufficient:
// D#
// if you wish to use the default time, just enter the speed:
// D255#
// it moves for a time = delayTime and then stops.  delayTime is a define.
// 
// for servos
// U, N, K, H = move up, down, right, left
// J to center and M for max down
// followed by the number of steps to take, for example, to move 2 steps up:
// U2#
// if there is no number, then the servo will just move by one step (TILT_DELTA or PAN_DELTA)
// U#


#include <Servo.h> 


#define PwmPinMotorA 3  //PWM control for motor outputs 1 and 2 is on digital pin 3 with ardumoto shield
#define PwmPinMotorB 11  //PWM control for motor outputs 3 and 4 is on digital pin 11 with ardumoto shield
#define DirectionPinMotorA 12 //direction control for motor outputs 1 and 2 is on digital pin 12 with ardumoto shield
#define DirectionPinMotorB 13  //direction control for motor outputs 3 and 4 is on digital pin 13 with ardumoto shield
#define tiltPin 5
#define panPin 6
#define powerPin 7
#define LEDpin 8  // indicator that a serial signal was received, off = waiting, on = working
#define SerialSpeed 9600
#define BufferLength 16
#define LineEndCharacter '#' // serial input commands must end with this character

#define MIN_DELAY_TIME 200
#define DEFAULT_DELAY_TIME 200
#define DEFAULT_SPEED 255

#define TILT_CENTER 40
#define TILT_MIN 20
#define TILT_MAX 120
#define TILT_DELTA 10

#define PAN_CENTER 90
#define PAN_MIN 50
#define PAN_MAX 130
#define PAN_DELTA 10

Servo panServo, tiltServo;  // create servo objects to control the servos
int panPos, tiltPos;    // variable to store the servo position 
char inputBuffer[BufferLength];

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}


void go(int speed)
{
  if (speed < 0) speed = 0;
  else if (speed > 255) speed = 255;
  
  analogWrite(PwmPinMotorA, speed * 4);
  analogWrite(PwmPinMotorB, speed * 4);
}

void move(int speed) // speed goes from 0 to 255
{
  //Serial.println("moving, speed = ");
  //Serial.println(speed);
  if (speed > 0)  // go forward
  {
    motorGo(1, 1, speed * 4);
    motorGo(2, 1, speed * 4);
//    digitalWrite(DirectionPinMotorA, LOW);  //Set motor direction, 1 low, 2 high
//    digitalWrite(DirectionPinMotorB, HIGH);  //Set motor direction, 3 high, 4 low
  }
  else  // go backward
  {
    motorGo(1, 2, speed * 4);
    motorGo(2, 2, speed * 4);
//    speed = -speed;    
//    digitalWrite(DirectionPinMotorA, HIGH);
//    digitalWrite(DirectionPinMotorB, LOW); 
  }
  //go(speed);  
}


void turn(int speed) // speed goes from 0 to 255
{
  //Serial.println("turning ");
  if (speed > 0)  // turn right
  {
    motorGo(1, 1, speed * 4);
    motorGo(2, 2, speed * 4);
//    digitalWrite(DirectionPinMotorA, LOW);  //Set motor direction, 1 low, 2 high
//    digitalWrite(DirectionPinMotorB, LOW);  //Set motor direction, 3 high, 4 low
  }
  else  // turn left
  {
    motorGo(1, 1, speed * 4);
    motorGo(2, 2, speed * 4);
    motorGo(1, 1, speed * 4);
    motorGo(2, 2, speed * 4);
    motorGo(1, 1, speed * 4);
    motorGo(2, 2, speed * 4);
//    speed = -speed;
//    digitalWrite(DirectionPinMotorA, HIGH);
//    digitalWrite(DirectionPinMotorB, HIGH); 
  }
  //go(speed);  
}
 
// process a command string
void HandleCommand(char* input, int length)
{
  int speedToGo = DEFAULT_SPEED;
  int delayTime = DEFAULT_DELAY_TIME;
  int stepsToGo = 1;  // servo steps
  int value = 0;
  // calculate number following command
  if (length > 1) {
    value = atoi(&input[1]);
    if (value > 1000)
    {
      delayTime = value - (value % 1000);  // time and speed specified
      speedToGo = value - delayTime;
    }
    else
    {
      speedToGo = value;                  // either servo steps or speed specified, default time
      stepsToGo = value;
    }
  }

  // check commands
  // ************note that if you use more than one character here
  // the bytes are swapped, ie 'FM' means command MF *****************
  // you can use this stmt to get the command:
  // int* command = (int*)input;
  // but not needed when we just have a single character command format
  
  switch(input[0]) {
    case 'W':    // move forward
    case 'w':
      move(speedToGo);
      delay(MIN_DELAY_TIME * (delayTime/1000)); // delay time goes (1 to 9) * MIN_DELAY_TIME
      go(0);  //stop after delay is done
      break;
    case 'S':    // move backward
    case 's':
      move(-speedToGo);
      delay(MIN_DELAY_TIME * (delayTime/1000)); // delay time goes (1 to 9) * MIN_DELAY_TIME
      go(0);  //stop after delay is done
      break;
    case 'D':    // turn right
    case 'd':
      turn(speedToGo);
      delay(MIN_DELAY_TIME * (delayTime/1000)); // delay time goes (1 to 9) * MIN_DELAY_TIME
      go(0);  //stop after delay is done
      break;
    case 'A':    // turn left
    case 'a':
      turn(-speedToGo);
      delay(MIN_DELAY_TIME * (delayTime/1000)); // delay time goes (1 to 9) * MIN_DELAY_TIME
      go(0);  //stop after delay is done
      break;
      
    case 'J':    // center servos
    case 'j':
      panServo.write(PAN_CENTER);
      tiltServo.write(TILT_CENTER);
      panPos = PAN_CENTER;
      tiltPos = TILT_CENTER;
      break;
    case 'U':    // tilt up
    case 'u':
      if (tiltPos - (TILT_DELTA * stepsToGo) >= TILT_MIN) tiltPos -= TILT_DELTA * stepsToGo;
      else tiltPos = TILT_MIN;
      tiltServo.write(tiltPos);
      break;
    case 'N':    // tilt down
    case 'n':
      if (tiltPos + (TILT_DELTA * stepsToGo) <= TILT_MAX) tiltPos += TILT_DELTA * stepsToGo;
      else tiltPos = TILT_MAX;
      tiltServo.write(tiltPos);
      break;
    case 'H':    // pan left
    case 'h':
      if (panPos - (PAN_DELTA * stepsToGo) >= PAN_MIN) panPos -= PAN_DELTA * stepsToGo;
      else panPos = PAN_MIN;
      panServo.write(panPos);
      break;
    case 'K':    // pan right
    case 'k':
      if (panPos + (PAN_DELTA * stepsToGo) <= PAN_MAX) panPos += PAN_DELTA * stepsToGo;
      else panPos = PAN_MAX;
      panServo.write(panPos);
      break;
    case 'M':    // tilt max down
    case 'm':
      tiltPos = TILT_MAX;
      tiltServo.write(tiltPos);
      break;
    case 'P':
    case 'p':
      digitalWrite(powerPin, LOW);
      delay(500);
      digitalWrite(powerPin,HIGH);
      delay(500);
      digitalWrite(powerPin,LOW);
      break;
    default:
      //Serial.println("did not recognize command ");
      break;
  }
  //Serial.println(delayTime);
} 
 
void setup()
{
  // motor pins must be outputs
  pinMode(PwmPinMotorA, OUTPUT);
  pinMode(PwmPinMotorB, OUTPUT);
  pinMode(DirectionPinMotorA, OUTPUT);
  pinMode(DirectionPinMotorB, OUTPUT);
  pinMode(LEDpin, OUTPUT); // LED indicator
  pinMode(powerPin, OUTPUT); // when set from low to high, toggles base power
  
  go(0); //stop both motors
 
  tiltServo.attach(tiltPin); 
  panServo.attach(panPin);  // attaches the pan servo pin to the servo object
  panServo.write(PAN_CENTER);
  tiltServo.write(TILT_CENTER);
  panPos = PAN_CENTER;
  tiltPos = TILT_CENTER;
         
  digitalWrite(powerPin,LOW);  
  digitalWrite(LEDpin,LOW); 
  
  Serial.begin(SerialSpeed);   
  //Serial.println("serial connected");
}
 
void loop()
{ 
  // get a command from the serial port
  int inputLength = 0; 
  digitalWrite(LEDpin,LOW); // show on LED that we are waiting for a serial input
  do {
    while (!Serial.available()); // wait for input
    inputBuffer[inputLength] = Serial.read(); // read it in
  } while (inputBuffer[inputLength] != LineEndCharacter && ++inputLength < BufferLength);
  inputBuffer[inputLength] = 0; //  add null terminator
  digitalWrite(LEDpin,HIGH);  // show on LED that we are received a serial input
  //Serial.println(inputBuffer);
  HandleCommand(inputBuffer, inputLength);
}

