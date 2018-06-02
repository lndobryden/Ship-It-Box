/**
 * Ship-It Box V3
 * 
 * Adafruit Feather M0 Express
 * 1 Large Arcade Button with Neopixel Ring under shell
 * 4 Small Arcade Buttons
 * 2 Toggle Switches
 * 1 7 Segment LED
 * 1 Feather Ethernet Wing
*/

#include "Keyboard.h"
#include "Bounce2.h"

const int largeBtnPin = 12;//
int previousButtonState = LOW;   // for checking the state of a pushButton
Bounce largeBtn = Bounce();

void setup() {
  // make the pushButton pin an input:
  pinMode(largeBtnPin, INPUT_PULLUP);
  largeBtn.attach(largeBtnPin);
  largeBtn.interval(5);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
    largeBtn.update();

  // read the pushbutton:
  int buttonState = largeBtn.read();
  // if the button state has changed,
  if ((buttonState != previousButtonState) && (buttonState == LOW)) {
    Keyboard.print("Hello World!");
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
