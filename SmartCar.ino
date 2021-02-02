/*
   Smart Car Program Version 0.1
   By: Evyn Rissling, Curtis Eck, Brandon Jones

*/

#define ENA 5 // Motor A Enable
#define ENB 6 // Motor B Enable

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define SRVO 3
#define SPEED 100

void setup()
{
  pinMode(ENA, OUTPUT); // enables left side
  pinMode(ENB, OUTPUT); // enables right side

  pinMode(IN1, OUTPUT); // left side forward
  pinMode(IN2, OUTPUT); // left side backwards
  pinMode(IN3, OUTPUT); // right side forward
  pinMode(IN4, OUTPUT); // right side backwards

  setMoveSpeed();
  
  digitalWrite(IN1, HIGH); // try IN1 for 2 seconds
  delay(2000);
  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH); // try IN2 for 2 seconds
  delay(2000);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); // try IN3 for 2 seconds
  delay(2000);
  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH); // try IN4 for 2 seconds
  delay(2000);
  digitalWrite(IN4, LOW);

  // Try disabling motor so we know which side ENA is
  digitalWrite(ENB, LOW);
  
  digitalWrite(IN1, HIGH); // try IN1 for 2 seconds
  delay(2000);
  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH); // try IN2 for 2 seconds
  delay(2000);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); // try IN3 for 2 seconds
  delay(2000);
  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH); // try IN4 for 2 seconds
  delay(2000);
  digitalWrite(IN4, LOW);

  
}

void loop()
{
  // empty for now

}

// Move car forward
void forward()
{

}

// Move car backwards
void reverse()
{

}

void turnRight()
{

}

void turnLeft()
{

}

void stopMoving()
{
  
}

void setMoveSpeed()
{
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}
