#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "4vUtoMAQbWpamPHEkmiPiSS1uMpktzCS";
char ssid[] = "Anh_Khoi";
char pass[] = "Ninhbinh";

#define analogPin A0
#define led D2
int value;
int percent;
bool isLedOn = false;

BlynkTimer timer;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);

  Blynk.virtualWrite(V1, isLedOn); 
  
  timer.setInterval(1000L, updateSensor); 
}

void loop()
{
  Blynk.run();
  timer.run();
}

void updateSensor()
{
  value = analogRead(analogPin);
  percent = map(value, 0, 1023, 100, 0);
  Blynk.virtualWrite(V2, percent);

  if (isLedOn) {
    if (percent <= 30) {
      digitalWrite(led, HIGH);
    }
    else {
      digitalWrite(led, LOW);
    }
  }
}

BLYNK_WRITE(V1)
{
  int ledState = param.asInt();
  if (ledState == 1) {
    isLedOn = true;
  }
  else {
    isLedOn = false;
    digitalWrite(led, LOW);
  }
  Blynk.virtualWrite(V1, isLedOn);
}


