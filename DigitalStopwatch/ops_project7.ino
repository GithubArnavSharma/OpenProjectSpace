#include <Timer.h>
#include <TM1637Display.h>


Timer timer;
Timer button_delay;
const int pause_pin = 8;
const int stop_pin = 10;
const int CLK = 4;
const int DIO = 6;
const int buzzer_pin = 21;
TM1637Display display(CLK, DIO);
int max_min = 1;


void pauseHandler()
{
 if (button_delay.read() == 0 || button_delay.read() > 1000) {
   button_delay.stop();
   if (timer.state() == PAUSED) {
     timer.resume();
   } else if (timer.state() == RUNNING) {
     timer.pause();
   } else if (timer.state() == STOPPED) {
     timer.start();
     max_min = 1;
   }
   tone(buzzer_pin, 523, 500);
   button_delay.start();
 }
}


void stopHandler() {
 if (button_delay.read() == 0 || button_delay.read() > 1000) {
   button_delay.stop();
   if (timer.state() == RUNNING) {
     timer.stop();
   }
   tone(buzzer_pin, 523, 500);
   button_delay.start();
 }
}


int msToNumber(int ms) {
 int sec_total = ms / 1000;
 int min = sec_total / 60;
 int sec = sec_total - (min * 60);
 return min * 100 + sec;
}




void setup() {
 // put your setup code here, to run once:
 Serial.begin(115200);


 attachInterrupt(digitalPinToInterrupt(pause_pin), pauseHandler, FALLING);
 attachInterrupt(digitalPinToInterrupt(stop_pin), stopHandler, FALLING);


 pinMode(pause_pin, INPUT_PULLUP);
 pinMode(stop_pin, INPUT_PULLUP);


 display.clear();
 display.setBrightness(7);
 display.showNumberDecEx(0, 0x40, true);


 timer.stop();
}


void loop() {
 // put your main code here, to run repeatedly:
 if (timer.state() != STOPPED) {
   display.showNumberDecEx(msToNumber(timer.read()), 0x40, true);
 }
 if (timer.read() >= max_min*60*1000) {
   max_min++;
   tone(buzzer_pin, 523, 500);
 }
 delay(100);
}


