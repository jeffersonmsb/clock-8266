#ifndef Led_h
#define Led_h

class Led{
  private:
      bool ledState;
      int bright;
      int pin;

  public:
    Led(int ledPin){
      pin = ledPin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
      ledState = false;
    }

    void on(){
      ledState = true;
      digitalWrite(pin, LOW);
    }

    void off(){
      ledState = false;
      digitalWrite(pin, HIGH);
    }

    /*void brightness(int value){
      //fazr inversão depois 0 -> 255 e 255 -> 0
      bright = value;
      analogWrite(pin, value);
    }*/

    bool state(){
      return ledState;
    }
};
#endif
