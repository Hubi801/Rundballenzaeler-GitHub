#ifndef MAIN_H
#define MAIN_H

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "main_display.h"
#include "main_touch.h"
#include "archive_display.h"
#include "archive_touch.h"
#include "storage.h"

// Definitionen
#define CS_PIN 10 // Beispielwert, ändern Sie dies entsprechend Ihrer Konfiguration
#define EEPROM_ADDRESS 0x50 // Beispielwert, ändern Sie dies entsprechend Ihrer Konfiguration

extern int zaehlerstand;
extern bool zeigeArchiv;
extern bool zeigePopup;
extern int letzteWerte[10];
extern int currentPage;
extern const int itemsPerPage;

void setup();
void loop();

#endif // MAIN_H