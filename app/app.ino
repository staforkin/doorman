#include <Servo.h>

const int servo1 = 4;  //eyelids
const int servo2 = 3; //left horizontal
const int servo3 = 2; //left vertical

const int servo4 = 6;  //right horizontal
const int servo5 = 5; //right vertical

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int pos = 0; // variable to store the servo position

int inputPin = 12;   // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0;        // variable for reading the pin status

const int ignoreSecConst = 30;
int ignoreSec = 0;

void setup()
{
  myservo1.attach(servo1);
  myservo2.attach(servo2);
  myservo2.attach(servo2);
  myservo3.attach(servo3);
  myservo4.attach(servo4);
  myservo5.attach(servo5);

  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  myservo5.write(90);

  pinMode(inputPin, INPUT); // declare sensor as input

  Serial.begin(9600);
  Serial.println("Start");
}
void loop()
{
  if(ignoreSec > 0)
  {
    Serial.println("ignore");
    Serial.print(ignoreSec);
    ignoreSec--;
    delay(1000);
    return;
  }
  else
  {
    myservo2.write(90);
    myservo3.write(90);
    myservo4.write(90);
    myservo5.write(90);
  }
  val = digitalRead(inputPin); // read input value
  if (val == HIGH)
  { // check if the input is HIGH
    digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
    if (pirState == LOW)
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;

      myservo1.write(170); //open lids
      delay(3000);

      myservo2.write(110); //left left
      myservo4.write(110); //right left
      delay(1000);

      myservo2.write(60); //left right
      myservo4.write(60); //right right
      delay(1000);

      // myservo2.write(100);//left left
      // myservo3.write(110);//left up
      // myservo4.write(100);//right left
      // myservo5.write(60);//right up
      //delay(1000);

      myservo2.write(60);  //left right
      myservo3.write(60);  //left down
      myservo4.write(60);  //right right
      myservo5.write(110); //right down
      delay(2000);
      myservo2.write(90);
      myservo3.write(90);
      myservo4.write(90);
      myservo5.write(90);
      delay(1000);
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);  // turn LED OFF
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;

      delay(3000); // Wait 1 second
      myservo1.write(90); //close lids
      delay(3000); // Wait 1 second
      ignoreSec = ignoreSecConst;
    }
    else
    {
      myservo2.write(90);
      myservo3.write(90);
      myservo4.write(90);
      myservo5.write(90);
    }
  }
}