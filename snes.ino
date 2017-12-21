#include <Joystick.h>

Joystick_ Joystick;

int DATA_CLOCK = 6;
int DATA_LATCH = 7;
int DATA_SERIAL = 12;

int buttons[12];

void setup(){
  // Starten
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
  digitalWrite(DATA_LATCH, HIGH); // Blockiere den Controller. Hier wird der Controller nun die Buttons zwischenspeichern.
  delayMicroseconds(12); // Warte 12ms
  digitalWrite(DATA_LATCH, LOW); // Entblocke den Controller
  delayMicroseconds(6); // Warte 6ms
  for(int i = 0; i < 16; i++) { // Für jeden Button auf dem Controller
    digitalWrite(DATA_CLOCK, LOW); // Sag dem Controller er soll den Status des jetzigen Button in den Serialport schreiben.
    delayMicroseconds(6); // Warte 6ms
    if(i <= 11){
      // Da wir nur die physischen Buttons brauchen, werden wir hier nur die ersten 12 Buttons verwenden.
      buttons[i] = digitalRead(DATA_SERIAL); // Lies den Serialport.
    }
    digitalWrite(DATA_CLOCK, HIGH); // Sag dem Controller, dass wir fertig sind.
    delayMicroseconds(6); // Warte 6ms
  }
  for(int i = 0; i < 12; i++) { // Für jeden Button den wir ausgelesen haben...
    if(buttons[i] == 0) { // Wenn der Button gedrückt ist... (0 ist aktiviert!)
      Joystick.setButton(i, 1); // Simuliere den Knopfdruck.
    } else {
      Joystick.setButton(i, 0); // Sonst gib an, dass die Taste nicht gedrückt wird.
    }
  }
}
