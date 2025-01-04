#include "storage.h"
#include <EEPROM.h>

void speichereZaehlerstand(int &zaehlerstand, int letzteWerte[], int eepromAdresse) {
  for (int i = 9; i > 0; i--) {
    letzteWerte[i] = letzteWerte[i - 1];
  }
  letzteWerte[0] = zaehlerstand;

  for (int i = 0; i < 10; i++) {
    EEPROM.write(eepromAdresse + i, letzteWerte[i]);
  }
  EEPROM.commit();
}