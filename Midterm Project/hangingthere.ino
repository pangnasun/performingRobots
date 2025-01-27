/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

int value;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(90);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
    Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
}



void loop() {

  int mVal = map(value, 50, 90, 170, 80);
  //int mVal2 = map(value, 50, 90, 80, 120);
  Serial.println(mVal);

  myMotor->setSpeed(mVal);
  for (int i=0; i<1100; i++) {
     myMotor->run(BACKWARD);  

  }

  delay(100);
  myMotor->setSpeed(90);
  for (int i=0; i<1100; i++) {
     myMotor->run(FORWARD);  

  }
  delay(100);
 
  
 
}

void receiveEvent(int howMany) {
  value = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
}
