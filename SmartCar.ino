/*
   Smart Car Program Version 0.2
   By: Evyn Rissling, Curtis Eck, Brandon Jones

*/

#include <Servo.h>

#define ENA 5 // Motor A Enable (Left)
#define ENB 6 // Motor B Enable (Right)

#define IN1 7 // Left side forward
#define IN2 8 // Left side back
#define IN3 9 // Right side forward
#define IN4 11 // Right side back

#define SRVO 3 // Ultrasonic servo
#define ECHO A4 // Receives pulse
#define TRIG A5 // Sends pulse

#define SPEED 200 // Motor speed
#define DEFAULT_TIME 500 // Default time for movement

// Function Declarations
long distanceInCM();
void forward(int time = DEFAULT_TIME);
void reverse(int time = DEFAULT_TIME);
void turnRight(int time = DEFAULT_TIME);
void turnLeft(int time = DEFAULT_TIME);
void stopMoving();
void turnMotorsOff();
void setMotorSpeed(int speed = SPEED);

void setup()
{
  Serial.begin(9600); // Open serial for communication
  
  pinMode(ENA, OUTPUT); // enables left side
  pinMode(ENB, OUTPUT); // enables right side

  pinMode(IN1, OUTPUT); // left side forward
  pinMode(IN2, OUTPUT); // left side backwards
  pinMode(IN3, OUTPUT); // right side forward
  pinMode(IN4, OUTPUT); // right side backwards
  
  pinMode(ECHO, INPUT); // Pulse receiver
  pinMode(TRIG, OUTPUT); // Pulse generator
  
  Servo ultraSonicServo;
  ultraSonicServo.attach(SRVO); // Attach ultrasonic servo motor
  
  ultraSonicServo.write(90); // Turn Sensor to the middle
  
  setMotorSpeed(); // Set move speed to SPEED
  
  // PUT INITIAL ACTIONS BELOW
  
  // test sequence
  forward(3000);
  reverse(3000);
  turnRight(2000);
  turnLeft(2000);
  delay(5000);
}

void loop()
{
  // testing ultrasonic sensor
  if (distanceInCM() < 20)
  {
    turnMotorsOff(); 
  }
  
  forward();
   
}

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

void forward(int time = DEFAULT_TIME)
{
   digitalWrite(IN1, HIGH);
   digitalWrite(IN3, HIGH);
   delay(time);
   stopMoving();
}

// Move car backwards
void reverse(int time = DEFAULT_TIME)
{
   digitalWrite(IN2, HIGH);
   digitalWrite(IN4, HIGH);
   delay(time);
   stopMoving();
}

void turnRight(int time = DEFAULT_TIME)
{
   digitalWrite(IN1, HIGH);
   delay(time);
   stopMoving();
}

void turnLeft(int time = DEFAULT_TIME)
{
  digitalWrite(IN3, HIGH);
  delay(time);
  stopMoving();
}

void stopMoving()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnMotorsOff()
{
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
}

void setMotorSpeed(int speed = SPEED)
{
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}
