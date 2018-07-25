#ifndef Pir_h
#define Pir_h

class Pir{
  private:
    int pin;
    unsigned long lastBeaconTime;

  public:
    Pir(int pirPin){
      pin = pirPin;
      pinMode(pin, INPUT);
      lastBeaconTime = 0;
    }

    int lastBeacon(){
      return lastBeaconTime;
    }

    void monitor(){
      if(digitalRead(pin)== HIGH){
  			lastBeaconTime = millis();
  		}
    }

    bool state(){
      return digitalRead(pin);
    }
};
#endif
