#include <Servo.h>
const int trigPin = 3;//pin declarations and variable assignment
const int echoPin = 4;
int pos = 0;
int range = 50;
int increment = 2;
Servo myservo;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop() {
  int closestpos = 90;
  float closest = 1000000;
  for (int i = 0; i<=180; i += 2 ) { //loop for the servo to occilate over 180 deg
    myservo.write(pos);              
    delay(10);                      // waits for the servo to reach the position
    float current = Distance();
    if (current < closest){ //logic to find closest position
      closestpos = pos;
      closest = current;
    }
    pos += increment;
  }
  if (closest < range){ //servo 'looks' at closest position within range
    myservo.write(closestpos);      
    delay(500); 
  }
  increment = 0-increment; //flips the incrememnet between positive and negative to acheive occilation of the servo
  Serial.println(increment);

}


int Distance(){ //function to measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
  delay(50);
}