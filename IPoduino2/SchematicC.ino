#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
      


// Use pins 20 and 21 with HardwareSerial to communicate with DFPlayer Mini
const int PIN_MP3_RX = 20; // Connects to module's RX
const int PIN_MP3_TX = 21; // Connects to module's TX
const int PLAY_BTN = 3;
bool playing_now = false;
const int NEXT_BTN = 4;


// Define serial port objects
HardwareSerial mySerial1(1); //use UART1


// Create the player object which will serve as an interface for our DFPlayer commands
DFRobotDFPlayerMini player;
      
void setup() {       
 // Initialize USB serial port for debugging
 Serial.begin(115200);
      
 // Initialize the pins for HardwareSerial. No pinMode calls needed.
 mySerial1.begin(9600, SERIAL_8N1, PIN_MP3_RX, PIN_MP3_TX); // RX=20, TX=21


 delay(1000); //DO NOT REMOVE THIS DELAY. It is needed to properly initialize HardwareSerial.


 // Start communication with DFPlayer Mini using player.begin
   // player.begin returns true if the connection was a success
   // and false if it failed
 if (!player.begin(mySerial1)){
     Serial.println("Connecting to DFPlayer Mini failed!");
 }


 // Set the player volume to maximum (0 to 30).
 player.volume(30);


 pinMode(PLAY_BTN, INPUT_PULLUP);
 pinMode(NEXT_BTN, INPUT_PULLUP);
}


void loop() {
 delay(100);


 int play_btn_read = digitalRead(PLAY_BTN);
 if (play_btn_read == 1) {
   if (playing_now == false) {
     player.start();
     playing_now = true;
   }
   else {
     player.pause();
     playing_now = false;
   }
 }


 int next_btn_read = digitalRead(NEXT_BTN);
 if (next_btn_read == 1) {
   player.next();
   playing_now = true;
 }
}



