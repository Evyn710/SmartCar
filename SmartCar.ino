/*
   Smart Car Program Version 0.81
   By: Evyn Rissling, Curtis Eck, Brandon Jones

*/

#include <Servo.h>

#define ENA 5 // Motor A Enable (Left)
#define ENB 6 // Motor B Enable (Right)

#define IN1 7 // Left side forward
#define IN2 8 // Left side back
#define IN3 9 // Right side back
#define IN4 11 // Right side forward

#define SRVO 3 // Ultrasonic servo
#define ECHO A4 // Receives pulse
#define TRIG A5 // Sends pulse

#define SPEED 150 // Motor speed DON"T CHANGE UNLESS REALLY NECESSARY
#define DEFAULT_TIME 100 // Default time for movement

// Function Declarations
long distanceInCM();
void forward(int time = DEFAULT_TIME);
void reverse(int time = DEFAULT_TIME);
void turnRight(int time = DEFAULT_TIME);
void turnLeft(int time = DEFAULT_TIME);
void turnSharpRight(int time = DEFAULT_TIME);
void turnSharpLeft(int time = DEFAULT_TIME);
void stopMoving();
void turnMotorsOff();
void setMotorSpeed(int speed = SPEED);

Servo ultraSonicServo;
int right = 0, sharpRight = 0, left = 0, sharpLeft = 0, forwardCounter = 0;

void setup()
{
  Serial.begin(9600); // Open serial for communication

  pinMode(ENA, OUTPUT); // enables left side
  pinMode(ENB, OUTPUT); // enables right side

  pinMode(IN1, OUTPUT); // left side forward
  pinMode(IN2, OUTPUT); // left side backwards
  pinMode(IN3, OUTPUT); // right side backwards
  pinMode(IN4, OUTPUT); // right side forward

  pinMode(ECHO, INPUT); // Pulse receiver
  pinMode(TRIG, OUTPUT); // Pulse generator

  setMotorSpeed(); // Set move speed to SPEED

  ultraSonicServo.attach(SRVO); // Attach ultrasonic servo motor

  ultraSonicServo.write(0); // Turn Sensor to the right
  delay(3000); // wait 3 seconds to start

}

void loop()
{
  moveRightAroundObject(); // move right around the object forever
}

// Move in right circle around object
void moveRightAroundObject()
{
  ultraSonicServo.write(15); // turns ultrasonic sensor to the right

  int x = distanceInCM(); // pings distance away from object
  Serial.println(x); // for debug
  
  if (x < 30) // if too close to the object, turn left
  {
    left++;
    right = 0;
    sharpRight = 0;

    if (left = 5) // checks if the same reading has happened 5 times
    {             // to reduce probability of outlier
      turnLeft();
      left = 0;
    }
  }
  else if (x > 185 && forwardCounter > 1) // if the robot detects open space
  { // it does a 90 degree right turn as long as its had at least 2 forward movements
    sharpRight++;
    left = 0;
    right = 0;
    forward(20);
    if (sharpRight == 5) // again, it only does the turn if it has got 5 consistent readings
    {
      sharpRight = 0;
      forward(750);
      turnSharpRight(500);
      forward(1000);
      forwardCounter = 0;
    }
  }
  else if (x > 45) // if too far away, turn right
  {
    left = 0;
    right++;
    sharpRight = 0;
    
    if (right == 5)
    {
      turnRight();
      right = 0;
    }
  }
  else // else. the robot continues straight
  {
    forwardCounter++;
    forward(300);
  }

}

// A function that returns the distance in front of the ultrasonic sensor in CM
long distanceInCM()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // Set to low for 2 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); // Sends pulse out for 10 microseconds
  digitalWrite(TRIG, LOW);

  float duration = pulseIn(ECHO, HIGH);
  return (long)(duration * 0.01715); // calculates distance based on the time to return the pulse
}

// Move car forwards
void forward(int time = DEFAULT_TIME)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
  delay(time);
  stopMoving();
}

// Move car backwards
void reverse(int time = DEFAULT_TIME)
{
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  delay(time);
  stopMoving();
}

// Turns car in a wide right arc
void turnRight(int time = DEFAULT_TIME)
{
  digitalWrite(IN1, HIGH);
  analogWrite(ENB, 25); // make this higher to make the turn wider
  digitalWrite(IN4, HIGH); 
  delay(time);
  setMotorSpeed();
  stopMoving();
}

// Turns car in a wide left arc
void turnLeft(int time = DEFAULT_TIME)
{
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 0); // make this higher to make the turn wider
  digitalWrite(IN1, HIGH);
  delay(time);
  setMotorSpeed();
  stopMoving();
}

// Turns car in a sharp right arc
void turnSharpRight(int time = DEFAULT_TIME)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  delay(time);
  stopMoving();
}

// Turns car in a sharp left arc
void turnSharpLeft(int time = DEFAULT_TIME)
{
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  delay(time);
  stopMoving();
}

// Stops the car's motors temporarily
void stopMoving()
{
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Turns motor output pins off
void turnMotorsOff()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

// Sets the speed of the motors
void setMotorSpeed(int speed = SPEED)
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}
