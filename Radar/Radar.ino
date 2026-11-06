#include <Servo.h>
const int trigPin = 3;
const int echoPin = 4;
int pos = 0;
int range = 50;
int increment = 2;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop() {
  int closestpos = 90;
  float closest = 1000000;
  for (int i = 0; i<=180; i += 2 ) {
    myservo.write(pos);              
    delay(10);                      // waits 15ms for the servo to reach the position
    float current = Distance();
    if (current < closest){
      closestpos = pos;
      closest = current;
    }
    pos += increment;
  }
  if (closest < range){
    myservo.write(closestpos);              // tell servo to go to position in variable 'pos'
    delay(500); 
  }
  increment = 0-increment;
  Serial.println(increment);

}
  // put your main code here, to run repeatedly:


int Distance(){
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