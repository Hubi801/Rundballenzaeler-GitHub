#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

void zeichneDisplay(TFT_eSPI &tft, int zaehlerstand, int letzteWerte[]);
void zeichnePopup(TFT_eSPI &tft);
void zeichneLetzteZaehlerstaende(TFT_eSPI &tft, int letzteWerte[]);
void zeichneArchiv(TFT_eSPI &tft, int letzteWerte[], int currentPage, int itemsPerPage);
void drawCenteredText(TFT_eSPI &tft, const char *text, int x1, int y1, int x2, int y2, uint16_t bgColor, int textSize = 2);

#endif // DISPLAY_H