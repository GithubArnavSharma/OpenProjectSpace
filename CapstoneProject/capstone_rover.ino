#include <WiFiConfig.h>
#include <WiFi.h>
#include <esp_wifi.h>
RemoteData data;




constexpr int low_bound_idle = 210;
constexpr int high_bound_idle = 230;
constexpr int left_down = 50;
constexpr int right_up = 240;
constexpr int trig = 3;
constexpr int echo = 4;


constexpr int IN1 = 0;
constexpr int IN2 = 1;
constexpr int IN3 = 5;
constexpr int IN4 = 6;


bool auto_mode = false;
int last_sw = 1;


constexpr int dist_max = 10;


struct MoveResult {
 int x;
 int y;
};




MoveResult movePos(int x, int y) {
 MoveResult result{0, 0};


 if (x < low_bound_idle) result.x = 1;
 else if (x > high_bound_idle) result.x = 2;
 if (y < low_bound_idle) result.y = 1;
 else if (y > high_bound_idle) result.y = 2;


 return result;
}


void setup() {
 // put your setup code here, to run once:
 Serial.begin(115200);


 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);


 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);


 wifi_setup();
 set_data_receiver(&data);
}


void loop() {
 /*
 if (data.sw == 0 && last_sw == 1) {
   auto_mode = !auto_mode;
 }
 */
  last_sw = data.sw;


 if (auto_mode) {
   digitalWrite(trig, LOW);
   delayMicroseconds(100);
   digitalWrite(trig, HIGH);
   delayMicroseconds(100);
   digitalWrite(trig, LOW);


   long duration = pulseIn(echo, HIGH);
   long distance = duration / 58.0;


   if (distance <= dist_max || distance == 1010) {
     // Turn right
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   } else {
     // Move forward
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   }


 } else {
   MoveResult result{data.vx, data.vy};


   // Y-axis takes priority; X-axis used only when Y is idle
   if (result.y < left_down) {
     // Move backward
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   } else if (result.y > right_up) {
     // Move forward
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   } else if (result.x > right_up) {
     // Turn left
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     //result.x > right_up
   } else if (result.x < left_down) {
     // Turn right
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   } else {
     // Stop
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   }
 }


 delay(500);
}
