#include "display.h"

const int ballenX1 = 20, ballenY1 = 20, ballenX2 = 110, ballenY2 = 50;
const int zaehlerX1 = 120, zaehlerY1 = 20, zaehlerX2 = 180, zaehlerY2 = 50;
const int plusX1 = 20, plusY1 = 60, plusX2 = 100, plusY2 = 100;
const int minusX1 = 110, minusY1 = 60, minusX2 = 190, minusY2 = 100;
const int speichernX1 = 20, speichernY1 = 130, speichernX2 = 140, speichernY2 = 170;
const int archivX1 = 20, archivY1 = 180, archivX2 = 140, archivY2 = 220;
const int resetX1 = 170, resetY1 = 180, resetX2 = 270, resetY2 = 220;
const int popupX1 = 60, popupY1 = 60, popupX2 = 260, popupY2 = 180;
const int jaX1 = 80, jaY1 = 120, jaX2 = 130, jaY2 = 160;
const int neinX1 = 170, neinY1 = 120, neinX2 = 220, neinY2 = 160;
const int letzteX1 = 200, letzteY1 = 20, letzteX2 = 300, letzteY2 = 50;
const int letzteZaehlerX1 = 200, letzteZaehlerY1 = 60, letzteZaehlerX2 = 300, letzteZaehlerY2 = 90;
const int weiterX1 = 220, weiterY1 = 200, weiterX2 = 280, weiterY2 = 240;
const int zurueckX1 = 160, zurueckY1 = 200, zurueckX2 = 220, zurueckY2 = 240;

void drawCenteredText(TFT_eSPI &tft, const char *text, int x1, int y1, int x2, int y2, uint16_t bgColor, int textSize) {
  int charWidth = 6 * textSize;
  int charHeight = 8 * textSize;

  int textWidth = strlen(text) * charWidth;
  int textHeight = charHeight;

  int centerX = x1 + ((x2 - x1) - textWidth) / 2;
  int centerY = y1 + ((y2 - y1) - textHeight) / 2;

  tft.setTextSize(textSize);
  tft.setTextColor(TFT_BLACK, bgColor);
  tft.drawString(text, centerX, centerY);
}

void zeichneDisplay(TFT_eSPI &tft, int zaehlerstand, int letzteWerte[]) {
  tft.fillScreen(TFT_WHITE);

  tft.drawRect(ballenX1, ballenY1, ballenX2 - ballenX1, ballenY2 - ballenY1, TFT_BLACK);
  drawCenteredText(tft, "Ballen", ballenX1, ballenY1, ballenX2, ballenY2, TFT_WHITE);

  tft.drawRect(zaehlerX1, zaehlerY1, zaehlerX2 - zaehlerX1, zaehlerY2 - zaehlerY1, TFT_BLACK);
  drawCenteredText(tft, String(zaehlerstand).c_str(), zaehlerX1, zaehlerY1, zaehlerX2, zaehlerY2, TFT_WHITE);

  tft.fillRect(plusX1, plusY1, plusX2 - plusX1, plusY2 - plusY1, TFT_GREEN);
  tft.drawRect(plusX1, plusY1, plusX2 - plusX1, plusY2 - plusY1, TFT_BLACK);
  drawCenteredText(tft, "+1", plusX1, plusY1, plusX2, plusY2, TFT_GREEN);

  tft.fillRect(minusX1, minusY1, minusX2 - minusX1, minusY2 - minusY1, TFT_RED);
  tft.drawRect(minusX1, minusY1, minusX2 - minusX1, minusY2 - minusY1, TFT_BLACK);
  drawCenteredText(tft, "-1", minusX1, minusY1, minusX2, minusY2, TFT_RED);

  tft.drawRect(speichernX1, speichernY1, speichernX2 - speichernX1, speichernY2 - speichernY1, TFT_BLACK);
  drawCenteredText(tft, "Speichern", speichernX1, speichernY1, speichernX2, speichernY2, TFT_WHITE);

  tft.drawRect(archivX1, archivY1, archivX2 - archivX1, archivY2 - archivY1, TFT_BLACK);
  drawCenteredText(tft, "Archiv", archivX1, archivY1, archivX2, archivY2, TFT_WHITE);

  tft.drawRect(resetX1, resetY1, resetX2 - resetX1, resetY2 - resetY1, TFT_BLACK);
  drawCenteredText(tft, "Reset", resetX1, resetY1, resetX2, resetY2, TFT_WHITE);

  zeichneLetzteZaehlerstaende(tft, letzteWerte);
}

void zeichnePopup(TFT_eSPI &tft) {
  uint16_t hellesGrau = tft.color565(211, 211, 211);

  tft.fillRect(popupX1, popupY1, popupX2 - popupX1, popupY2 - popupY1, hellesGrau);
  tft.drawRect(popupX1, popupY1, popupX2 - popupX1, popupY2 - popupY1, TFT_BLACK);
  drawCenteredText(tft, "Zaehler wirklich", popupX1, popupY1, popupX2, popupY1 + 40, hellesGrau, 2);
  drawCenteredText(tft, "loeschen?", popupX1, popupY1 + 40, popupX2, popupY2 / 2, hellesGrau, 2);

  tft.drawRect(jaX1, jaY1, jaX2 - jaX1, jaY2 - jaY1, TFT_BLACK);
  drawCenteredText(tft, "Ja", jaX1, jaY1, jaX2, jaY2, hellesGrau, 2);

  tft.drawRect(neinX1, neinY1, neinX2 - neinX1, neinY2 - neinY1, TFT_BLACK);
  drawCenteredText(tft, "Nein", neinX1, neinY1, neinX2, neinY2, hellesGrau, 2);
}

void zeichneLetzteZaehlerstaende(TFT_eSPI &tft, int letzteWerte[]) {
  int startY = letzteZaehlerY1;
  int boxHeight = 30;

  tft.drawRect(letzteX1, letzteY1, letzteX2 - letzteX1, letzteY2 - letzteY1, TFT_BLACK);
  drawCenteredText(tft, "Letzte", letzteX1, letzteY1, letzteX2, letzteY2, TFT_WHITE);

  for (int i = 0; i < 3; i++) {
    int y1 = startY + (i * boxHeight);
    int y2 = y1 + boxHeight;

    tft.drawRect(letzteZaehlerX1, y1, letzteZaehlerX2 - letzteZaehlerX1, boxHeight, TFT_BLACK);
    String text = String(letzteWerte[i]);
    drawCenteredText(tft, text.c_str(), letzteZaehlerX1, y1, letzteZaehlerX2, y2, TFT_WHITE);
  }
}

void zeichneArchiv(TFT_eSPI &tft, int letzteWerte[], int currentPage, int itemsPerPage) {
  tft.fillScreen(TFT_WHITE);
  tft.drawRect(20, 20, 300, 30, TFT_BLACK);
  drawCenteredText(tft, "Letzte Zählerstände", 20, 20, 320, 50, TFT_WHITE);

  int start = currentPage * itemsPerPage;
  int end = start + itemsPerPage;
  if (end > 10) end = 10;

  for (int i = start; i < end; i++) {
    int y1 = 60 + ((i - start) * 30);
    int y2 = y1 + 30;

    tft.drawRect(20, y1, 300, 30, TFT_BLACK);
    String text = String(letzteWerte[i]);
    drawCenteredText(tft, text.c_str(), 20, y1, 320, y2, TFT_WHITE);
  }

  // Pfeile und Seitenangabe zeichnen
  tft.fillTriangle(zurueckX1, zurueckY1, zurueckX2, zurueckY1, (zurueckX1 + zurueckX2) / 2, zurueckY2, TFT_BLACK);
  tft.fillTriangle(weiterX1, weiterY1, weiterX2, weiterY1, (weiterX1 + weiterX2) / 2, weiterY2, TFT_BLACK);

  String pageText = String(currentPage + 1) + " / " + String((10 + itemsPerPage - 1) / itemsPerPage);
  drawCenteredText(tft, pageText.c_str(), 20, weiterY1, 300, weiterY2, TFT_WHITE);
}