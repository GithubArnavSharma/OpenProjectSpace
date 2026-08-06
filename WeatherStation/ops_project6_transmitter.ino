#include <WiFiConfig.h>
#include <Adafruit_AHTX0.h>
#include <Wire.h>
//Find the mac address of your receiver ESP32 first, then enter it in here:
uint8_t receiverAddress[] = {.........};

WeatherReport report;      // global initialization of WeatherReport


#define I2C_SDA 6
#define I2C_SCL 7
const int PR_PIN = 4;
sensors_event_t humidity, temp;
Adafruit_AHTX0 aht;


void setup()
{
 Serial.begin(115200);                // Serial setup


 Wire.begin(I2C_SDA, I2C_SCL);
 aht.begin();


 pinMode(PR_PIN, INPUT);


 wifi_setup();                      // start wifi mode and ESP-NOW
 peer_setup(receiverAddress);       // configure receiving address
 //set_report_receiver(&report);      // configure the receiver ESP32 to update report’s values upon reception
}


void loop()
{
 aht.getEvent(&humidity, &temp);
 report.temperature = temp.temperature;
 report.humidity = humidity.relative_humidity;


 int light = analogRead(PR_PIN);
 Serial.println(light);
 report.light = 0;
 if (light > 1000) {
   report.light = 1;
 }


 send_report(receiverAddress, report);       // send the report


 delay(10000);
}
