/*
 * MIDIUSB_test.ino
 * 
 * Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 * 
 * Modified by David Rios
 * Desigining Interface for Live Performance - IMA - NYU (Feb. 2021)
 */ 


#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>


// Variables:
int b = 5;
int g = 6;
int y = 7;
int r = 8;
int counter = 16;

int pr = 1;
int pg = 1;
int pb = 1;
int py = 1;

int ccv1;
int ccv2;

int pcc1;
int pcc2;
int note = pitchA5;
int


boolean wasPressed = false;
void setup() {
  Serial.begin(9600);
  pinMode(y, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(r, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pcc2 =  map(analogRead(A1), 0, 1023, 0, 127);
}

void loop() {
  /* map a potentiometer reading to a midi value
     Full MIDI Range is 0-127
  */
  // ccv1 = map(analogRead(A0), 0, 1023, 30, 100);
  ccv1 = map(analogRead(A0), 0, 1023, 0, 127); // cc mapping
  // ccv2 = map(analogRead(A1), 0, 1023, 0, 127); //for note
  ccv2 = map(analogRead(A1), 0, 723, 0, 127) ; // cc mapping

  if (digitalRead(y) == 0 && py == 1) {
    noteOn(0, note, 80);
    py = 0;
  }
  if (digitalRead(y) == 1 && py == 0) {
    noteOff(0, note, 0);
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    py = 1;
  }

  if (digitalRead(g) == 0 && pg == 1) {
    noteOn(0, note+3, 80);
    pg = 0;
  }
  if (digitalRead(g) == 1 && pg == 0) {
    noteOff(0, note+3, 80);
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    pg = 1;
  }

  if (digitalRead(b) == 0 && pb == 1) {
    noteOn(0, note+7, 80);
    pb = 0;
  }
  if (digitalRead(b) == 1 && pb == 0) {
    noteOff(0, note+7, 0);
    for (int i = 0; i < 128; i++) {
      noteOff(0, i, 0);
    }
    pb = 1;
  }


  if (digitalRead(r) == 0 && pr == 1) {
    controlChange(1, counter, 127);
    counter++;
    if (counter >= 20) {
      counter = 16;
    }
    pr = 0;
  }
  if (digitalRead(r) == 1 && pr == 0) {
    pr = 1;
  }


  controlChange(0, 20, ccv1);
  controlChange(0, 21, ccv2);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


// Control Change
// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
