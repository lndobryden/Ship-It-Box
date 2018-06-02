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

#define BLUETOGGLE  A1

class Button {
  
  int pin;
  int previousState;
  Bounce btn;
  String offText;
  String onText;

  public:
  Button(int _pin, String _offText, String _onText)
  {
    pin = _pin;
    pinMode(pin, INPUT_PULLUP);
    previousState = LOW;
    offText = _offText;
    onText = _onText;

    btn = Bounce();
    btn.attach(pin);
    btn.interval(5);
  }

  void update(int blueToggle) {
    btn.update();
    // read the pushbutton:
    int currentState = btn.read();
    // if the button state has changed,
    if ((currentState != previousState) && (currentState == LOW)) {
      if(blueToggle == LOW) {
        Keyboard.print(offText);
      } else {
        Keyboard.print(onText);
      }
    }
    // save the current button state for comparison next time:
    previousState = currentState;
  }
};

Button largeBtn(12, "Large Button", "Off");
Button leftRedBtn(6, "Left Red", "Off");
Button yellowBtn(10, "Yellow", "Off");
Button whiteBtn(11, "White", "Off");
Button rightRedBtn(9, "Right Red", "Off");

int blueToggleState;

void setup() {
  pinMode(BLUETOGGLE, INPUT_PULLDOWN);
  Keyboard.begin();
}

void loop() {

  blueToggleState = digitalRead(BLUETOGGLE);
  
  largeBtn.update(blueToggleState);
  leftRedBtn.update(blueToggleState);
  yellowBtn.update(blueToggleState);
  whiteBtn.update(blueToggleState);
  rightRedBtn.update(blueToggleState);
}
