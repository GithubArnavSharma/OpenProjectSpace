const int LED1 = 20;
const int LED2 = 10;
const int LED3 = 8;
const int PM1 = 0;
const int PM2 = 1;
const int PM3 = 4;


void setup() {
 // put your setup code here, to run once:
 pinMode(PM1, INPUT);
 pinMode(PM2, INPUT);
 pinMode(PM3, INPUT);
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 Serial.begin(115200);
}


void loop() {
 // put your main code here, to run repeatedly:
 int PM1_val = analogRead(PM1);
 int PM2_val = analogRead(PM2);
 int PM3_val = analogRead(PM3);
 analogWrite(LED1, PM1_val);
 analogWrite(LED2, PM2_val);
 analogWrite(LED3, PM3_val);
}
