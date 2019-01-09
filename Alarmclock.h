#ifndef Alarmclock_h
#define Alarmclock_h

#include "Buzzer.h"
#include <EEPROM.h>

class Alarmclock{
  private:
    int hour_;
    int minute_;
    Buzzer *buzzer;

  public:
    Alarmclock(Buzzer *buzzerOut){
      int h, m;
      EEPROM.get(96,h);
      hour_ = h;
      EEPROM.get(100, m);
      minute_ = m;
      buzzer = buzzerOut;
    }

    void setMinute(int m){
      minute_ = m;
      EEPROM.put(100, m);
      EEPROM.commit();
    }

    void setHour(int h){
      hour_ = h;
      EEPROM.put(96, h);
      EEPROM.commit();
    }

    int getMinute(){
      EEPROM.get(100, minute_);
      return minute_;
    }

    int getHour(){
      EEPROM.get(96, hour_);
      return hour_;
    }

    void activate(){
      if(hour() ==  hour_ && minute() == minute_){
        if(second() <= 30 ){
          buzzer->on();
        }else{
          buzzer->off();
        }
      }
    }
};
#endif
