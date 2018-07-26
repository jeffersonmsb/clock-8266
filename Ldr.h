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
      return 1024-analogRead(pin);
    }
};
#endif
