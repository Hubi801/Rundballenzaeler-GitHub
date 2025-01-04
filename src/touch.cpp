#include "touch.h"
#include "display.h"
#include "storage.h"

const int plusX1 = 20, plusY1 = 60, plusX2 = 100, plusY2 = 100;
const int minusX1 = 110, minusY1 = 60, minusX2 = 190, minusY2 = 100;
const int speichernX1 = 20, speichernY1 = 130, speichernX2 = 140, speichernY2 = 170;
const int archivX1 = 20, archivY1 = 180, archivX2 = 140, archivY2 = 220;
const int resetX1 = 170, resetY1 = 180, resetX2 = 270, resetY2 = 220;
const int jaX1 = 80, jaY1 = 120, jaX2 = 130, jaY2 = 160;
const int neinX1 = 170, neinY1 = 120, neinX2 = 220, neinY2 = 160;
const int weiterX1 = 220, weiterY1 = 200, weiterX2 = 280, weiterY2 = 240;
const int zurueckX1 = 160, zurueckY1 = 200, zurueckX2 = 220, zurueckY2 = 240;

void ts_loop(XPT2046_Touchscreen &ts, TFT_eSPI &tft, int &zaehlerstand, bool &zeigeArchiv, bool &zeigePopup, int letzteWerte[], int eepromAdresse) {
  static int currentPage = 0;
  const int itemsPerPage = 3;

  if (ts.tirqTouched() && ts.touched()) {
    TS_Point p = ts.getPoint();

    int touchX = map(p.x, 0, 4095, 0, 320);
    int touchY = map(p.y, 0, 4095, 0, 240);

    if (!zeigePopup) {
      if (!zeigeArchiv) {
        if (touchX > plusX1 && touchX < plusX2 && touchY > plusY1 && touchY < plusY2) {
          zaehlerstand++;
          zeichneDisplay(tft, zaehlerstand, letzteWerte);
          delay(200);
        } else if (touchX > minusX1 && touchX < minusX2 && touchY > minusY1 && touchY < minusY2) {
          zaehlerstand--;
          zeichneDisplay(tft, zaehlerstand, letzteWerte);
          delay(200);
        } else if (touchX > speichernX1 && touchX < speichernX2 && touchY > speichernY1 && touchY < speichernY2) {
          speichereZaehlerstand(zaehlerstand, letzteWerte, eepromAdresse);
          zeichneDisplay(tft, zaehlerstand, letzteWerte);
          delay(200);
        } else if (touchX > archivX1 && touchX < archivX2 && touchY > archivY1 && touchY < archivY2) {
          zeigeArchiv = true;
          currentPage = 0;
          zeichneArchiv(tft, letzteWerte, currentPage, itemsPerPage);
          delay(200);
        } else if (touchX > resetX1 && touchX < resetX2 && touchY > resetY1 && touchY < resetY2) {
          zeigePopup = true;
          zeichnePopup(tft);
          delay(200);
        }
      } else {
        if (touchX > weiterX1 && touchX < weiterX2 && touchY > weiterY1 && touchY < weiterY2) {
          currentPage++;
          if (currentPage * itemsPerPage >= 10) currentPage = 0;
          zeichneArchiv(tft, letzteWerte, currentPage, itemsPerPage);
          delay(200);
        } else if (touchX > zurueckX1 && touchX < zurueckX2 && touchY > zurueckY1 && touchY < zurueckY2) {
          if (currentPage > 0) currentPage--;
          zeichneArchiv(tft, letzteWerte, currentPage, itemsPerPage);
          delay(200);
        } else if (touchX > archivX1 && touchX < archivX2 && touchY > archivY1 && touchY < archivY2) {
          zeigeArchiv = false;
          zeichneDisplay(tft, zaehlerstand, letzteWerte);
          delay(200);
        }
      }
    } else {
      if (touchX > jaX1 && touchX < jaX2 && touchY > jaY1 && touchY < jaY2) {
        zaehlerstand = 0;
        zeigePopup = false;
        zeichneDisplay(tft, zaehlerstand, letzteWerte);
        delay(200);
      } else if (touchX > neinX1 && touchX < neinX2 && touchY > neinY1 && touchY < neinY2) {
        zeigePopup = false;
        zeichneDisplay(tft, zaehlerstand, letzteWerte);
        delay(200);
      }
    }
  }
}