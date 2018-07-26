#ifndef Monitor_h
#define Monitor_h

#include "Display.h"
#include "DHT.h"
#include "Filesystem.h"
#include "Pir.h"

class Monitor{
  private:
    Display *display;
    unsigned long displayMillis;
    int displayFlag;

    DHT *dht;
    unsigned long dhtMillis;
    float temp;

    Filesystem *filesystem;

    Pir *pir;
    unsigned long pirMillis;

    int alarmFlag;

  public:
    Monitor(Display *displayOut, DHT *dhtOut, Pir *pirOut, Filesystem *filesystemOut){
      display = displayOut;
      displayMillis = 0;
      displayFlag = 0;

      dht = dhtOut;
      dht->begin();

      filesystem = filesystemOut;
      pir  = pirOut;
      pirMillis = 0;

      alarmFlag = 1;
    }

    void timerDisplay(){
      if(millis()-displayMillis >= 5000){
    		displayMillis = millis();
    	  if(displayFlag > 2){
          displayFlag = 0;
        }else{
          displayFlag++;
        }
      }
    }

    void timerDht(){
      if(millis()-dhtMillis >= 30000){
    		dhtMillis = millis();
    	  temp = dht->readTemperature();
      }
    }

    void timerPir(){
      if(millis()-pirMillis >= 1000*60*3){
    		pirMillis = millis();
        alarmFlag = 1;
      }
      if(alarmFlag == 1 && pir->state() == HIGH){
        filesystem->createFile("alarmlog" + String(day()) + "." + String(month()) + "." + String(year()));
        filesystem->writeFile("alarmlog" + String(day()) + "." + String(month()) + "." + String(year()) ,String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" +String(minute()) + ":" + String(second()) + " "  + String(now()));
        alarmFlag = 0;
      }
    }

    void run(){
      timerDisplay();
      timerDht();
      timerPir();
      if(displayFlag == 0) display->clock(hour(), minute());
      if(displayFlag == 3) display->integer(8266);
      if(displayFlag == 2) display->floatTwoDecimals((float)(1533542400 - now())/86400.0);
      if(displayFlag == 1) display->temp(temp);
    }
};
#endif
