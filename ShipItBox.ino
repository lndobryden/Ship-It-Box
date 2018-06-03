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
#include "Adafruit_NeoPixel.h"

#define NEOPIN      A0
#define BLUETOGGLE  A1
#define WHITETOGGLE A2

char ctrlKey = KEY_LEFT_CTRL;

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
      if(blueToggle == HIGH) {
        write(offText);
      } else {
        write(onText);
      }
    }
    // save the current button state for comparison next time:
    previousState = currentState;
  }

  void write(String text) {
    if (text.charAt(0) == ctrlKey) {
      Keyboard.press(text.charAt(0));
      Keyboard.press(text.charAt(1));
      Keyboard.releaseAll();
    } else {
      Keyboard.println(text);
    }
  }
};

class LightRing {
  
  Adafruit_NeoPixel ring;
  unsigned long flashInterval;

  int state;
  unsigned long previousMillis;
  unsigned long currentMillis;

  public:
  LightRing(int _pin)
  {
    flashInterval = 500UL;
    state = 0;
    previousMillis = millis();
    ring = Adafruit_NeoPixel(16, _pin, NEO_RGBW + NEO_KHZ800);
  }

  void initialize() {
    ring.begin();
    ring.setBrightness(75);
    ringOn();
  }

  void update(int blueToggle) {
    if(blueToggle == HIGH) {
      flashRing();
    } else if (state == 0) {
      ringOn();
    }
  }

  void flashRing() {
    currentMillis = millis();
    if (currentMillis - previousMillis >= flashInterval) {
      previousMillis = currentMillis;
      if(state == 0) {
        ringOn();
      } else {
        ringOff();
      }
    }
  }

  void ringOn() {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, 255, 255, 255, 255);
    }
    ring.show();
    state = 1;
  }

  void ringOff() {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, 0, 0, 0, 0);
    }
    ring.show();
    state = 0;
  }
};


Button largeBtn(12, "git push\n", "./gradlew clean build");

char leftRedText[2] = {ctrlKey, 'C'};
Button leftRedBtn(6, "cat /Volumes/keys/id_rsa | ssh-add -t 30 -k -", leftRedText);

char yellowText[2] = {ctrlKey, 'R'};
Button yellowBtn(10, "git status", yellowText);

Button whiteBtn(11, "git diff", "Empty");
Button rightRedBtn(9, "git add -p", "./gradlew bootRun");

int blueToggleState;

LightRing ring(NEOPIN);

void setup() {

  pinMode(BLUETOGGLE, INPUT_PULLDOWN);
  ring.initialize();  
  Keyboard.begin();
}

void loop() {

  blueToggleState = digitalRead(BLUETOGGLE);
  
  largeBtn.update(blueToggleState);
  leftRedBtn.update(blueToggleState);
  yellowBtn.update(blueToggleState);
  whiteBtn.update(blueToggleState);
  rightRedBtn.update(blueToggleState);
  ring.update(blueToggleState);
}
