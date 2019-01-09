//clock-8266
//My MAC: 5c:cf:7f:d9:9a:b6
//http://arduino.esp8266.com/stable/package_esp8266com_index.json

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>
#include "Display.h"
#include "Monitor.h"
#include "DHT.h"
#include "Light.h"
#include "Led.h"
#include "Buzzer.h"
#include "Pir.h"
#include "Alarmclock.h"
#include "Web.h"
#include "Filesystem.h"
#include <EEPROM.h>

#define D0 16  //LED1
#define D1 5 //PIR
#define D2 4 //Buzzer
#define D3 0 //DHT22
#define D4 2  //LED0
#define D5 14 //display
#define D6 12 //display
#define D7 13 //display
#define D8 15 //Light
#define D9 3 //RX
#define D10 1 //TX

#define latchPin D7
#define clockPin D5
#define dataPin D6
#define LDR A0
#define DHTPIN D3
#define BUZZER D2
#define LIGHT D8
#define PIR D1
#define LED0 D4
#define LED1 D0

Display display(latchPin, clockPin, dataPin);
DHT dht(DHTPIN, DHT22);
WiFiUDP ntpUDP;
int16_t utc = -3; //UTC -3:00 BRASIL
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);
Light light(LIGHT);
Led led0(LED0);
Led led1(LED1);
Buzzer buzzer(BUZZER);
Ldr ldr(LDR);
Pir pir(PIR);
Filesystem filesystem;
Alarmclock alarmclock(8, 15, &buzzer);
Monitor monitor(&display, &dht, &pir, &ldr, &filesystem);
Web web(&light, &ldr, &dht, &alarmclock, &filesystem);


void setup(){
  display.raw(0b10111111, 0b10010111, 0b10101111, 0b10101111, 0x00);

  EEPROM.begin(1024);
  const char ssid[32] = "ssid";
  const char wifipass[64] = "pass";
  EEPROM.get(0,ssid);
  EEPROM.get(32,wifipass);

  WiFi.begin(ssid, wifipass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  timeClient.begin();
  timeClient.update();
  setTime(timeClient.getEpochTime());
  while(now() < 0){
    timeClient.update();
    setTime(timeClient.getEpochTime());
  }

  filesystem.createFile("log");
  filesystem.writeFile("log" ,String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" +String(minute()) + ":" + String(second()) + " "  + String(now()) + " Booting");

  web.begin();

}

void loop(){
  monitor.run();
  web.run();
  buzzer.timer();
  pir.monitor();
  alarmclock.activate();
  //if(pir.lastBeacon() > 0) light.on();
  /*if(pir.state()){
    led0.on();
  }else{
    led0.off();
  }*/
}
