#include <ESP32Servo.h>


const int PM = 4;
const int PWM = 10;
Servo myServo;

void setup() {
 // Configure the Potentiometer's pin behavior to INPUT
 pinMode(PM, INPUT);
 // Attach object of your servo name to the physical servo
 myServo.attach(PWM);
 // Configure the Serial baud rate to 115200
 Serial.begin(115200);
}
              
void loop() {
 // Read potentiometer pin value
 int PM_val = analogRead(PM);
 int degrees = PM_val / 22.75;
 // Set and map servo angle to the potentiometer pin value
 myServo.write(degrees);
}
