#ifndef Light_h
#define Light_h

class Light{
  private:
      bool lightState;
      int bright;
      int pin;

  public:
    Light(int lightPin){
      pin = lightPin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      lightState = false;
      bright = 255;
    }

    void on(){
      lightState = true;
      analogWrite(pin, bright);
    }

    void off(){
      lightState = false;
      analogWrite(pin, 0);
    }

    void setBrightness(int value){
      bright = value;
      analogWrite(pin, value);
      if(value != 0) lightState = true;
    }

    int readBrightness(){
      return bright;
    }

    bool state(){
      return lightState;
    }
};
#endif
