#include <GyverButton.h>
#include <GyverRGB.h>

#define RED 3
#define GREEN 5
#define BLUE 6

#define BUTTON 3
#define PHOTORESIST 4

GRGB ledStripe(RED, GREEN, BLUE);
GButton controlButton = GButton(BUTTON);

const int lightToDark = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(PHOTORESIST, INPUT);

  controlButton.setTickMode(AUTO);
}

void loop() {
  // put your main code here, to run repeatedly:
  colorWaveMode();
}

void colorWaveMode() {
  while (true) {
    for (int i = 0; i < 255; i++) {
        ledStripe.setHSV(i, 255, 255);
        delay(20);
        if (controlPhotoresist() < lightToDark) {}
        if (controlButton.isSingle()) {
          lightOff();
        }

        if (controlButton.isDouble()) {
          staticColorMode();
        }
      }
    
    for (int i = 255; i > 0; i--) {
        ledStripe.setHSV(i, 255, 255);
        delay(20);
        if (controlPhotoresist() < lightToDark) {}
        if (controlButton.isSingle()) {
          lightOff();
        }

        if (controlButton.isDouble()) {
          staticColorMode();
          }
      }
    }
  }

void staticColorMode() {
  while (true) {
        int hue = 0;
        ledStripe.setHSV(hue, 255, 255);
        delay(20);
        if (controlPhotoresist() < lightToDark) {}
        if (controlButton.isSingle()) {
          lightOff();
        }

        if (controlButton.isDouble()) {
          colorWaveMode();
         }

        if (controlButton.isTriple()) {
          hue = hue + 40;
          if (hue > 255) {
            hue = 0;
            }
         }
  }
}


void lightOff() {
  while (true) {
        ledStripe.setBrightness(0);
        if (controlButton.isSingle()) break;
    }
  }

int controlPhotoresist() {
  return constrain(map(analogRead(PHOTORESIST), 0, 1023, 0, 100), 0, 100);
  }
