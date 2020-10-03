/* USB MIDI AnalogControlChange Example

   You must select MIDI from the "Tools > USB Type" menu
   http://www.pjrc.com/teensy/td_midi.html

   This example code is in the public domain.
*/

#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each analog input
//const int controllerA0 = 10; // 10 = pan position

void setup() {
  analogReadResolution(13);
}

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
int previousA3 = -1;

elapsedMillis msec = 0;

void loop() {
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 5) {
    msec = 0;
    int n0 = analogRead(A0);
    int n1 = analogRead(A1);
    int n2 = analogRead(A2);
    int n3 = analogRead(A3);
    // only transmit MIDI messages if analog input changed
    if (n0 != previousA0) {
        usbMIDI.sendPitchBend((n0 * 2) - 8192, channel);
        previousA0 = n0;
    }
    if (n1 != previousA1) {
        usbMIDI.sendPitchBend((n1 * 2) - 8192, channel + 1);
        previousA1 = n1;
    }
    if (n2 != previousA2) {
        usbMIDI.sendPitchBend((n2 * 2) - 8192, channel + 2);
        previousA2 = n2;
    }
    if (n3 != previousA3) {
        usbMIDI.sendPitchBend((n3 * 2) - 8192, channel + 3);
        previousA3 = n3;
    }
  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
