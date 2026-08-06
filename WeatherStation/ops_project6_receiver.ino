#include <WiFi.h>
#include <esp_wifi.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiConfig.h>
#include <Adafruit_AHTX0.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

WeatherReport report;

void setup(){
	 Serial.begin(115200);
	 WiFi.mode(WIFI_STA);
	 WiFi.STA.begin();
	 lcd.init();
 	lcd.backlight();
	 wifi_setup();
	 set_report_receiver(&report);
}
	
void loop(){
	 lcd.clear();                 // clear display
 	lcd.setCursor(0, 0);         // move cursor to   (0, 0)
 	lcd.print("Temp: " + String(report.temperature) + "C");          // print message at (0, 0)
 	lcd.setCursor(0, 1);         // move cursor to   (0, 1)
 	lcd.print("Hum: " + String(report.humidity) + "%");          // print message at (2, 1)
 	lcd.setCursor(10, 1);
 	if (report.light == 1) {
   	lcd.print("Day");
 	} else {
   	lcd.print("Night");
 	}
 	delay(10000);                 // delay between each print to LCD

}
