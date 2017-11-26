#include <Joystick.h>

Joystick_ Joystick;

int DATA_CLOCK = 6;
int DATA_LATCH = 7;
int DATA_SERIAL = 12;

int buttons[12];

void setup(){
  pinMode(DATA_CLOCK, OUTPUT);
  digitalWrite(DATA_CLOCK, HIGH);
  pinMode(DATA_LATCH, OUTPUT);
  digitalWrite(DATA_LATCH, LOW);
  pinMode(DATA_SERIAL, OUTPUT);
  digitalWrite(DATA_SERIAL, HIGH);
  pinMode(DATA_SERIAL, INPUT);  
  Joystick.begin();
}

void loop(){
  digitalWrite(DATA_LATCH, HIGH);
  delayMicroseconds(12);
  digitalWrite(DATA_LATCH, LOW);
  delayMicroseconds(6);
  for(int i = 0; i < 16; i++){
    digitalWrite(DATA_CLOCK, LOW);
    delayMicroseconds(6);
    if(i <= 11){
      buttons[i] = digitalRead(DATA_SERIAL);
    }
    digitalWrite(DATA_CLOCK, HIGH);
    delayMicroseconds(6);
  }
  for(int i = 0; i < 12; i++) {
    if(buttons[i] == 0) {
      Joystick.setButton(i, 1);
    } else {
      Joystick.setButton(i, 0);
    }
  }
}
