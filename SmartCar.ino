/*
   Smart Car Program Version 0.2
   By: Evyn Rissling, Curtis Eck, Brandon Jones

*/

#define ENA 5 // Motor A Enable (Left)
#define ENB 6 // Motor B Enable (Right)

#define IN1 7 // Left side forward
#define IN2 8 // Left side back
#define IN3 9 // Right side forward
#define IN4 11 // Right side back
#define SRVO 3 // Ultrasonic servo

#define SPEED 100 // Motor speed
#define DEFAULT_TIME 500 // Default time for movement

void setup()
{
  pinMode(ENA, OUTPUT); // enables left side
  pinMode(ENB, OUTPUT); // enables right side

  pinMode(IN1, OUTPUT); // left side forward
  pinMode(IN2, OUTPUT); // left side backwards
  pinMode(IN3, OUTPUT); // right side forward
  pinMode(IN4, OUTPUT); // right side backwards

  setMoveSpeed();
  
}

void loop()
{
  // empty for now

}

// Move car forward
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
