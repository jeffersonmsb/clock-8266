#ifndef Alarmclock_h
#define Alarmclock_h

#include "Buzzer.h"

class Alarmclock{
  private:
    int hour_;
    int minute_;
    Buzzer *buzzer;

  public:
    Alarmclock(int h, int m, Buzzer *buzzerOut){
      hour_ = h;
      minute_ = m;
      buzzer = buzzerOut;
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
