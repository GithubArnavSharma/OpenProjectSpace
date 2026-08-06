#include <WiFiConfig.h>
#include <WiFi.h>
#include <esp_wifi.h>


//Tape = left motor wires
uint8_t receiverAddress[] = {...........};


//Vx: 214-217 ish is middle, 255 is the up, 0 is the down
//Vy: 214-217 ish is middle, 255 is right, 0 is left


constexpr int LED_RED = 8;
constexpr int LED_GREEN = 10;
constexpr int VRY = 0;
constexpr int VRX = 1;
constexpr int SW = 3;


constexpr int low_bound_idle = 210;
constexpr int high_bound_idle = 230;


RemoteData data;




bool isIdle(int x, int y) {
 if (x >= low_bound_idle && x <= high_bound_idle && y >= low_bound_idle && y <= high_bound_idle) {
   return true;
 }
 return false;
}


void setup() {
 Serial.begin(115200);


 // put your setup code here, to run once:
 pinMode(VRY, INPUT);
 pinMode(VRX, INPUT);
 pinMode(SW, INPUT_PULLUP);


 pinMode(LED_RED, OUTPUT);
 pinMode(LED_GREEN, OUTPUT);


 wifi_setup();                      // start wifi mode and ESP-NOW
 peer_setup(receiverAddress);       // configure receiving address


 digitalWrite(LED_GREEN, LOW);
 digitalWrite(LED_RED, LOW);
 //set_data_receiver(&data);


}


void loop() {
 // put your main code here, to run repeatedly:
 int x_val = analogRead(VRX) / 16.0;
 int y_val = analogRead(VRY) / 16.0;
 int button_state = digitalRead(SW);
  if (isIdle(x_val, y_val)) {
   digitalWrite(LED_GREEN, LOW);
   digitalWrite(LED_RED, HIGH);
 } else {
   digitalWrite(LED_GREEN, HIGH);
   digitalWrite(LED_RED, LOW);
 }


 data.vx = x_val;
 data.vy = y_val;
 data.sw = button_state;
 send_data(receiverAddress, data);


 delay(250);
}


