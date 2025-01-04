#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>
#include "display.h"
#include "touch.h"
#include "storage.h"

// Touchscreen Pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

// Globale Variablen
int zaehlerstand = 0;
bool zeigeArchiv = false;
bool zeigePopup = false;
const int eepromAdresse = 0;
int letzteWerte[10] = {0};

// Zeitvariablen für Cooldown
unsigned long lastPressTime = 0;

// Setup
void setup() {
  Serial.begin(115200);

  mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(mySpi);
  tft.init();
  tft.setRotation(1);

  EEPROM.begin(512);
  for (int i = 0; i < 10; i++) {
    letzteWerte[i] = EEPROM.read(eepromAdresse + i);
  }

  zeichneDisplay(tft, zaehlerstand, letzteWerte);
}

// Loop
void loop() {
  ts_loop(ts, tft, zaehlerstand, zeigeArchiv, zeigePopup, letzteWerte, eepromAdresse);
}