#include <GyverButton.h>
#include <GyverRGB.h>

#define RED 3
#define GREEN 5
#define BLUE 6

#define BUTTON 11
#define PHOTORESIST A0

GRGB ledStripe(RED, GREEN, BLUE);
GButton controlButton = GButton(BUTTON);

const int lightToLightSwitch = 70;
unsigned long currentTime; 

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
        if (controlButton.isSingle()) {
          lightOff();
        }

        if (controlButton.isDouble()) {
          staticColorMode();
          }

        if (controlButton.isTriple()) {
          autoMode();
        }
      }
    }
  }

void staticColorMode() {
  int hue = 0;
  while (true) {
        ledStripe.setHSV(hue, 255, 255);
        delay(20);
        if (controlButton.hasClicks()) {
          switch (controlButton.getClicks()) {
            case 1:
            lightOff();
            break;
            
            case 2:
            colorWaveMode();
            break;
            
            case 3:
            hue = hue + 40;
            if (hue > 255) {
              hue = 0;
            }
            break;
            
            case 4:
            whiteMode();
            break;
            
            default:
            break;
            }
          }
  }
}

void whiteMode() {
  while (true) {
        ledStripe.setRGB(255, 180, 64);
        if (controlButton.isSingle()) {
          lightOff();
        }

        if (controlButton.isDouble()) {
          colorWaveMode();
          }
    }
  }


void lightOff() {
  while (true) {
        ledStripe.setBrightness(0);
        if (controlButton.isSingle()) {
          ledStripe.setBrightness(255);
          break;
        }
    }
  }

/*void autoMode() {
  while (true) {
      if (controlPhotoresist() < lightToLightSwitch) {
        ledStripe.setBrightness(255);
        for (int i = 0; i < 255; i++) {
        ledStripe.setHSV(i, 255, 255);
        delay(20);
        if (controlButton.isClick()) {
          colorWaveMode();
        }
      }
    
    for (int i = 255; i > 0; i--) {
        ledStripe.setHSV(i, 255, 255);
        delay(20);
        if (controlPhotoresist() >= lightToLightSwitch) ledStripe.setBrightness(0);
        if (controlButton.isClick()) {
          colorWaveMode();
        }
      }
      } else {
        ledStripe.setBrightness(0);
      }
    }
  }*/

void autoMode() {
  while (true) {
   if (controlPhotoresist() < lightToLightSwitch) {
      ledStripe.setBrightness(255);
      ledStripe.setRGB(255, 255, 255);

    }  else {
      ledStripe.setBrightness(0);
      ledStripe.setRGB(0, 0, 0);
    }

        if (controlButton.isSingle()) {
          colorWaveMode();
        }
   }
   
  }

int controlPhotoresist() {
  return constrain(map(analogRead(PHOTORESIST), 0, 1023, 0, 100), 0, 100);
  }
