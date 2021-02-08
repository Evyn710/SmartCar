/*
   Smart Car Program Version 0.71
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

#define SPEED 150 // Motor speed
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
double distance = 0; // used in ultrasonic sensor distance averaging

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
  
  ultraSonicServo.write(10); // Turn Sensor to the middle
  
  delay(3000);
   
}

void loop()
{
   moveRightAroundObject();
}

// Move in right circle around object
void moveRightAroundObject()
{
   ultraSonicServo.write(10);
   
   for (int c = 0; c < 5; c++) // reduces chance of misreading on sensor by averaging five readings
   {
      distance += distanceInCM();
   }
   
   int x = (int)(distance / 5.0);
   if (x < 20)
   {
      turnLeft();
   }
   else if (x > 100)
   {
      forward(200);
      turnSharpRight(500);
      forward(200);
   }
   else if (x > 30)
   {
      turnRight();
   }
   else
   {
      forward(250);
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
  return (long)(duration * 0.01715);
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
   delay(time);
   stopMoving();
}

// Turns car in a wide left arc
void turnLeft(int time = DEFAULT_TIME)
{
  digitalWrite(IN4, HIGH);
  delay(time);
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
