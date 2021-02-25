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

// pins
int b = 2;
int g = 3;
int y = 4;
int r = 5;

// variables for analog sensors
int photocell;
int potentiometer;

/// variables to hold the previous states of the buttons
int pRed = 1;
int pGreen = 1;
int pYellow = 1;
int pBlue = 1;

void setup() {
  Serial.begin(9600);
  pinMode(r, INPUT_PULLUP); // Input Pullup so we dont need a 10k resistor on the breadboard
  pinMode(g, INPUT_PULLUP);
  pinMode(y, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
}

void loop() {
// read the real time values and store them in variables
  int redValue = digitalRead(r);
  int yellowValue = digitalRead(y);
  int greenValue = digitalRead(g);
  int blueValue = digitalRead(b);

// read analog values
  photocell =  analogRead(A0);
  potentiometer = analogRead(A1);

// map the photocell values to a midi pitch
  int pitch = map(photocell , 0, 1023,  0, 127);


/// red button stuff
  if (redValue == 0 && pRed == 1) { // if red button is pressed send a note
    noteOn(0, pitch, 127);  // turn the note on
    pRed = 0;               // update the previous state of the red button
    delay(3);
  }

  if (redValue == 1 && pRed == 0)  { // if red button is not pressed turn note off
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);     // turn all notes off on release
    }                        
    pRed = 1;               // update the previous state of the red button
    delay(3);
  }

////////// yellow
  if (yellowValue == 0 && pYellow == 1) { // if red button is pressed send a note
    noteOn(0, pitch + 4 , 127);
    pYellow = 0;
    delay(3);
  }

  if (yellowValue == 1 && pYellow == 0)  { // if red button is not pressed turn note off
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    pYellow = 1;
    delay(3);
  }
///////////////green
  if (greenValue == 0 && pGreen == 1) { // if red button is pressed send a note
    noteOn(0, pitch + 7 , 127);
    pGreen = 0;
    delay(3);
  }

  if (greenValue == 1 && pGreen == 0)  { // if red button is not pressed turn note off
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    pGreen = 1;
    delay(3);
  }

///////////////blue
  if (blueValue == 0 && pBlue == 1) { // if red button is pressed send a note
    noteOn(0, pitch + 10 , 127);
    pBlue = 0;
    delay(3);
  }

  if (blueValue == 1 && pBlue == 0)  { // if red button is not pressed turn note off
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    pBlue = 1;
    delay(3);
  }
}



void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
