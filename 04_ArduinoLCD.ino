#include "tempo.h"
#include <LiquidCrystal.h>

LiquidCrystal screen(12, 11, 7, 6, 5, 4);
Tempo tempoScore;

unsigned long result = 0;
unsigned long startTime = 0;

const byte startButton = 2;
const byte endButton = 3;
const byte scoreButton = 8;

bool started = false;
bool ended = true;

String scoreboard[10];
int place = 0;

void setup() {
  Serial.begin(9600);
  screen.begin(16, 2);
  screen.clear();
  tempoScore.begin(500);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(endButton, INPUT_PULLUP);
  pinMode(scoreButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startButton), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(endButton), stopChrono, FALLING);
}

void loop() {
  if (digitalRead(scoreButton) == 0) {
    showScoreboard();
    Serial.println("SCOREBOARD !!!");
  }
}

void start() {
  if (ended == true) {

    screen.clear();
    screen.setCursor(0, 0);
    screen.write("Started !!");
    startTime = millis();
    Serial.println("Started !");
    started = true;
    ended = false;
  }
}

void stopChrono() {
  if (started == true) {
    result = millis() - startTime;
    Serial.println("Stopped !");
    ended = true;
    started = false;
    addToScoreboard(String(result));
    showResults();
  }
}

void showResults() {
  screen.clear();
  screen.setCursor(0, 0);
  screen.write("Votre temps est");
  screen.setCursor(0, 1);
  screen.write("de : ");
  screen.print(String(result));
  screen.write("ms");
}

void showScoreboard() {
  int i = 0;
  int j = 0;
  screen.clear();
  screen.setCursor(0, 1);
  tempoScore.reset();
  while (i < 10) {
    if (tempoScore.isTimeEnding()) {
      if (scoreboard[i] == "") {
        screen.clear();
        break;
        return;
      }
      screen.print(scoreboard[i]);
      i++;
      j++;
      Serial.println(j);
      if (j != 2) {
        screen.setCursor(0, 1);
      } else if (j == 2) {
        Serial.println("reset");
        screen.clear();
        screen.setCursor(0, 0);
        j = 0;
      }
    }
  }
}

void addToScoreboard(String value) {
  for (int i = 0; i < 10; i++) {
    if (scoreboard[i] == "") {
      scoreboard[i] = value;
      return;
    }
  }
  for (int i = 0; i < 10; i++) {
    if (scoreboard[i] < value) {
      scoreboard[i] = value;
      return;
    }
  }
}
