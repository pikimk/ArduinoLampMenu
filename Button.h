#include <Arduino.h>
class Button{
    private:
     int pin;

     public:
      Button(int pin){
        this->pin = pin;
        pinMode(pin, INPUT_PULLUP);
      }

      bool isClicked(){
        return !digitalRead(pin);
      }

};