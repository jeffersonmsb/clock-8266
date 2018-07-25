#ifndef Buzzer_h
#define Buzzer_h

class Buzzer{
  private:
    int pin;
    unsigned long buzzerMillis;
    int buzzerDelay;
    bool state;
    int tone;

  public:
    Buzzer(int buzzerPin){
      state = false;
      buzzerMillis = 0;
      buzzerDelay = 100;
      pin = buzzerPin;
      pinMode(pin, OUTPUT);
      analogWrite(pin, 0);
      tone = 128;
    }

    void timer(){
      static bool flag = false;
      if(millis()-buzzerMillis >= buzzerDelay && state == true){
    		buzzerMillis = millis();
        if(flag){
          analogWrite(pin, tone);
          flag = false;
        }else{
          analogWrite(pin, 0);
          flag = true;
        }
      }
    }

    void on(){
      state = true;
    }

    void off(){
      analogWrite(pin, 0);
      state = false;
    }
};
#endif
