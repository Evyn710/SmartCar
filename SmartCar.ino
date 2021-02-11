/*
   Smart Car Program Version 1.0
   By: Evyn Rissling, Curtis Eck, Brandon Jones

*/

#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define ENA 5 // Motor A Enable (Left)
#define ENB 6 // Motor B Enable (Right)

#define IN1 7 // Left side forward
#define IN2 8 // Left side back
#define IN3 9 // Right side back
#define IN4 11 // Right side forward

#define SRVO 3 // Ultrasonic servo
#define ECHO A4 // Receives pulse
#define TRIG A5 // Sends pulse

#define SPEED 225 // Motor speed DON"T CHANGE UNLESS REALLY NECESSARY
#define GYRO_Z_OFFSET -22 // define the gyroscope z offset

// Function Declarations
long distanceInCM();
void forward();
void rightForward();
void reverse();
void turnRight();
void sharpTurnRight();
void turnLeft();
void stopMoving();
void turnMotorsOff();
void setMotorSpeed(int speed = SPEED);
void gyroUpdate();

Servo ultraSonicServo; // new servo object
MPU6050 gyroScope; // new MPU6050 object

float gyroDegree = 0;

boolean oneLoopComplete = false;
float previousTime;

void setup()
{
  Serial.begin(115200); // open serial for gyro testing

  // Motor stuff
  pinMode(ENA, OUTPUT); // enables left side
  pinMode(ENB, OUTPUT); // enables right side

  pinMode(IN1, OUTPUT); // left side forward
  pinMode(IN2, OUTPUT); // left side backwards
  pinMode(IN3, OUTPUT); // right side backwards
  pinMode(IN4, OUTPUT); // right side forward

  setMotorSpeed(); // Set move speed to SPEED

  // Ultrasonic sensor stuff
  pinMode(ECHO, INPUT); // Pulse receiver
  pinMode(TRIG, OUTPUT); // Pulse generator
  ultraSonicServo.attach(SRVO); // Attach ultrasonic servo motor
  ultraSonicServo.write(0);
  
  // IMU Stuff
  Wire.begin();
  gyroScope.initialize(); // initialize the IMU
  gyroScope.CalibrateGyro(); // Calibrate the IMU
  gyroScope.setZGyroOffset(GYRO_Z_OFFSET); // Set the z offset
  gyroScope.CalibrateGyro(6); // calibrate it again after the offset


  //ACTUAL MOVEMENT CODE
  moveRightAroundObject(); 

  // turns robot 180 degrees around
  gyroDegree = 0;
  while (gyroDegree > -140)
  {
    gyroUpdate();
    sharpTurnRight();
  }
  stopMoving();
  
  reverse();
  delay(600);
  stopMoving();
  
  ultraSonicServo.write(180);
  delay(3000);
  gyroDegree = 0;
  
  moveLeftAroundObject();

  reverse();
  delay(500);
  stopMoving();

  // turns robot 180 degrees around
  gyroDegree = 0;
  while (gyroDegree > -160)
  {
    gyroUpdate();
    sharpTurnRight();
  }
  stopMoving();
}

void loop()
{
  // nothing needs to be in loop()
}

void gyroUpdate()
{
  float gyroZ = gyroScope.getRotationZ() / 131.0; // get the current Z orientation in degrees/second
  if (oneLoopComplete) {
    float timeForOneLoop = micros() - previousTime; // calculates how long loop took
    gyroDegree += gyroZ * timeForOneLoop / 1000000.0; // calculates new orientation based on the degrees/s * seconds
  }
  previousTime = micros();

  // Change the boolean flag to true to enable collection of gyroscope data
  if (!oneLoopComplete) {
    oneLoopComplete = true;
  }
}

// Move in right circle around object
void moveRightAroundObject()
{
  ultraSonicServo.write(0); // turns ultrasonic sensor to the right

  while (1)
  {
    gyroUpdate();
    
    if (gyroDegree < -1780)
    {
      turnMotorsOff();
      return;
    }

    int x = distanceInCM(); // pings distance away from object
    if (x < 35) // if too close to the object, turn left
    {
      turnLeft();
    }
    else if (x > 40)
    {
      turnRight();
    }
    else
    {
      forward();
    }

  }
}

void moveLeftAroundObject()
{
  ultraSonicServo.write(180); // turns ultrasonic sensor to the left

  while (1)
  {
    gyroUpdate();
    
    if (gyroDegree > 1790)
    {
      turnMotorsOff();
      return;
    }

    int x = distanceInCM(); // pings distance away from object
    if (x < 35) // if too close to the object, turn left
    {
      turnRight();
    }
    else if (x > 40)
    {
      turnLeft();
    }
    else
    {
      forward();
    }

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
void forward()
{
  setMotorSpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void reverse()
{
  setMotorSpeed();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turns car in a wide right arc
void turnRight()
{
  setMotorSpeed();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(ENB, 0); // make this higher to make the turn wider
  digitalWrite(IN4, HIGH);
}

// does a clock wise turn in spot
void sharpTurnRight()
{
  setMotorSpeed(150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turns car in a wide left arc
void turnLeft()
{
  setMotorSpeed();
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // make this higher to make the turn wider
  digitalWrite(IN1, HIGH);
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
