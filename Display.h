#ifndef Display_h
#define Display_h

class Display{
  private:
    byte digitos[16] = {
      0b00111111, //0
      0b00110000, //1
      0b10010111, //2
      0b10110101, //3
      0b10111000, //4
      0b10101101, //5
      0b10101111, //6
      0b00110001, //7
      0b10111111, //8
      0b10111101, //9
      0b10111011, //A
      0b10101110, //B
      0b00001111, //C
    	0b10110110, //D
    	0b10001111, //E
    	0b10001011};//F

      int latch;
      int clock_;
      int data;

  public:
    Display(int latchPin, int clockPin, int dataPin){
      latch = latchPin;
      clock_ = clockPin;
      data = dataPin;
      pinMode(latch, OUTPUT);
      pinMode(clock_, OUTPUT);
      pinMode(data, OUTPUT);
    }

    void raw(byte a, byte b, byte c, byte d, byte e){
      static int i;
      byte pos = 0b00010000;

      for(i=0;i<6;i++){
        digitalWrite(latch, LOW);
        if(i==4) shiftOut(data, clock_, LSBFIRST, a);
        if(i==3) shiftOut(data, clock_, LSBFIRST, b);
        if(i==1) shiftOut(data, clock_, LSBFIRST, c);
        if(i==0) shiftOut(data, clock_, LSBFIRST, d);
        if(i==2) shiftOut(data, clock_, LSBFIRST, e);
    	if(i==5) shiftOut(data, clock_, LSBFIRST, 0xF);
        shiftOut(data, clock_, LSBFIRST, ~pos);
        pos = (pos >> 1);
        digitalWrite(latch, HIGH);
      }
    }

    void integer(int n){
      int a, b, c, d;
      d=n%10;
      n=n/10;
      c=n%10;
      n=n/10;
      b=n%10;
      n=n/10;
      a=n;
      raw(digitos[a], digitos[b], digitos[c], digitos[d], 0);
    }

    void clock(int h, int m){
      int a, b, c, d, n=h*100+m;
      static int flag=0, i=0;
      d=n%10;
      n=n/10;
      c=n%10;
      n=n/10;
      b=n%10;
      n=n/10;
      a=n;
      if(flag){
        raw(digitos[a], digitos[b], digitos[c], digitos[d], 0b00010001);
      }else{
        raw(digitos[a], digitos[b], digitos[c], digitos[d], 0b00000000);
      }
      if(i%4000==0) flag=~flag;
      i++;
    }

    void temp(float temp){
      int a, b, c, d, t;
      t=(int)temp;
      b=t%10;
      t=t/10;
      a=t;
      temp=temp*10.0;
      c=((int)temp)%10;

      d=0xC;
      raw(digitos[a], digitos[b]|0b01000000, digitos[c], digitos[d], 0b00100000);
    }

    void floatTwoDecimals(float value){
      int a, b, c, d, v;
      b=(int)value%10;
      a=(int)value/10;
      c=(int)(value*10)%10;
    	d=(int)(value*100)%10;
      raw(digitos[a], digitos[b]|0b01000000, digitos[c], digitos[d], 0b00000000);
    }

};
#endif
