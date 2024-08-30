#include <Servo.h>
#include <Stepper.h>

servo myServo;
int pos = 0;

const int stepsPerRevolution = 200;


const int ECHO_PIN = 9;
const int TRIG_PIN = 10;

const int warningDistance = 20;


void setup() {
  // put your setup code here, to run once:
  myServo.attach(11);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Stepper myStepper(stepsPerRevolution, 3, 4, 5, 6);
  myStepper.setSpeed(60);
  Serial.begin(9600);






}

void loop() {
  // put your main code here, to run repeatedly:

// 10 second pulse to trigger ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delay(2000);
  digitalWrite(TRIG_PIN, HIGH);
  delay(10000);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN);
  int distance = duration * 0.034 /2;

  if (distance > warningDistance)
  {
    for (pos = 0; pos <= 180; pos++)
    {
      myServo.write(pos);
      delay(15);
      distance = measureDistance();
      
      if (distance <= warningDistance)
      {
        break;
      }
    }


    for (pos = 180; pos >= 0; pos--)
    {
      myServo.write(pos);
      delay(15);

      distance = measureDistance();
      if (distance <= warningDistance)
      {
        break;
      }  

    }

  }

  else
  {
    myServo.write(myServo.read());
    Serial.println("Clockwise");
    myStepper.step(stepsPerRevolution);
    delay(500);
    Serial.println("Counterclockwise");
    myStepper.step(-stepsPerRevolution);
    delay(500);

  }

  delay(100);


}
