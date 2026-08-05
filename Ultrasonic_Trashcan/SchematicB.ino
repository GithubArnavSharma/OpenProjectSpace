#include <ESP32Servo.h>


// Assign variables to pin numbers 
const int pwm = 10;
const int trig = 3;
const int echo = 4;
// Assign variable for open angle (ex. 160 may vary)
const int OPEN = 0;
// Assign variable for close angle (ex. 20 may vary)
const int CLOSED = 90;
const int THRES = 15;
// Initialize servo object with your servo name
Servo myServo;


void setup() {
 // Setup Trig and Echo pins
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 // Attach object of your servo name to the physical servo
 myServo.attach(pwm);
 // Initialize servo to close angle
 myServo.write(CLOSED);
 delay(1000);
 Serial.begin(115200);
}


void loop() {
   // Send pulses
   digitalWrite(trig, LOW);
   delayMicroseconds(100);
   digitalWrite(trig, HIGH);
   delayMicroseconds(100);
   digitalWrite(trig, LOW);
   // Calculate distance
   long duration = pulseIn(echo, HIGH);
   long distance = duration / 58.0;


   Serial.println(distance);


   // Write servo angle to open or close based on a distance threshold in cm (value may vary)
   if (distance <= 10 or distance == 1010) {
     myServo.write(OPEN);
   } else {
     myServo.write(CLOSED);
   }
   delay(1000);
}
