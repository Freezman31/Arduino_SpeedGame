/**
   @file tempo.ino
   @author ArnauldDev (https://github.com/ArnauldDev/)
   @brief Une classe permettant de réaliser différentes temporisation
   @version 0.1
   @date 2020-11-05

   @copyright Copyright (c) 2020

*/

#include <Arduino.h>
#include "tempo.h"

/// Définition des méthodes de la classe Tempo

void Tempo::begin(unsigned long interval) {
  _interval = interval;  // set duration of tempo
  _previousMillis = millis(); // store the current time before start tempo
}

void Tempo::setDuration(unsigned long interval) {
  _interval = interval;  // set duration of tempo
}

int Tempo::getDuration() {
  return _interval;
}

/**
   @brief is the time out is ending
   check to see if the difference between the current time
   and last time you call this function is bigger than the interval
*/
bool Tempo::isTimeEnding() {
  bool tempo_ending = false;
  unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= _interval) {
    // save the last time
    _previousMillis = currentMillis;

    tempo_ending = true;
  }

  return tempo_ending;
}

void Tempo::reset() {
  unsigned long currentMillis = millis();
  _previousMillis = currentMillis;
}

/// Fin de la classe Tempo
