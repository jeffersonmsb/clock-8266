#ifndef Ldr_h
#define Ldr_h

class Ldr{
  private:
    int pin;

  public:
    Ldr(int ldrPin){
      pin = ldrPin;
    }

    int read(){
      return analogRead(pin);
    }
};
#endif
