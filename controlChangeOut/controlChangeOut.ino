/*
 * MIDIUSB_test.ino
 *
 * Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 * 
 * Modified by David Rios
 * Desigining Interfaces for Live Performance - IMA - NYU (Feb. 2021)
 */ 


#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>

int b = 2;
int g = 3;
int y = 4;
int r = 5;

int pRed = 1;
int pGreen = 1;
int pYellow = 1;
int pBlue = 1;

int photocell = A0;
int potentiometer = A1;


void setup() {
  Serial.begin(9600);
  pinMode(r, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pinMode(y, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
}

void loop() {
  int redValue = digitalRead(r);
  int yellowValue = digitalRead(y);
  int greenValue = digitalRead(g);
  int blueValue = digitalRead(b);

  int photoValue = analogRead(photocell);
  int potValue = analogRead(potentiometer);

  int delay1 = map(potValue, 0, 1023, 0, 127 );
  int delay2 = map(photoValue, 0, 1023, 0, 127);


  /// red button logic to send only one message on state change
  
  if (redValue == 0 && pRed == 1) { // if red button is pressed send a note
    controlChange(1, 16, 127);
    pRed = 0;
    delay(3);
  }

  if (redValue == 1 && pRed == 0)  { // if red button is not pressed turn note off
    pRed = 1;
    delay(3);
  }

  //////////  yellow button logic to send only one message on state change
  if (yellowValue == 0 && pYellow == 1) { // if red button is pressed send a note
    controlChange(1, 17, 127);
    pYellow = 0;
    delay(3);
  }

  if (yellowValue == 1 && pYellow == 0)  { // if red button is not pressed turn note off
    pYellow = 1;
    delay(3);
  }
  
///////// green button logic to send only one message on state change
  if (greenValue == 0 && pGreen == 1) { // if red button is pressed send a note
     controlChange(1, 18, 127);
    pGreen = 0;
    delay(3);
  }

  if (greenValue == 1 && pGreen == 0)  { // if red button is not pressed turn note off
    pGreen = 1;
    delay(3);
  }
//////// Blue button logic to send only one message on state change
  if (blueValue == 0 && pBlue == 1) { // if red button is pressed send a note
    controlChange(1, 19, 127);
    pBlue = 0;
    delay(3);
  }

  if (blueValue == 1 && pBlue == 0)  { // if red button is not pressed turn note off
    pBlue = 1;
    delay(3);
  }
 // constant control changes for the delay wobbler
 controlChange(1, 20, delay1);
 controlChange(1, 21, delay2);
  
}


// function for the Control Changes
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// function for noteOn
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

//function for noteOff
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
