#ifndef TOUCH_H
#define TOUCH_H

#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

void ts_loop(XPT2046_Touchscreen &ts, TFT_eSPI &tft, int &zaehlerstand, bool &zeigeArchiv, bool &zeigePopup, int letzteWerte[], int eepromAdresse);

#endif // TOUCH_H