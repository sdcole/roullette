#include <Arduino.h>

#include "GameLogic.h"
#include "LCDUtils.h"



GameLogic::GameLogic(int navButtonPin, int selectButtonPin, int redPin, int greenPin, int bluePin) : 
    navButtonPin(navButtonPin), selectButtonPin(selectButtonPin), isGameActive(false) {

    pinMode(navButtonPin, INPUT);
    pinMode(selectButtonPin, INPUT);
}


void GameLogic::startGame(GameMode mode) {
    // Set the game mode
    gameMode = mode;
    isGameActive = true;

    // Display game start message
    Serial.println("Game Started!");
    Serial.print("Game Mode: ");
    Serial.print(static_cast<int>(gameMode));
    // Additional setup based on mode
    switch (gameMode) {
        case GameMode::CLASSIC6:
            // Set up for CLASSIC6 mode
            playClassic(6);
            break;
        case GameMode::CLASSIC10:
            // Set up for CLASSIC10 mode
            playClassic(10);
            break;
        case GameMode::RANDOM6:
            // Set up for RANDOM6 mode
            playRandom(6);
            break;
        case GameMode::RANDOM10:
            // Set up for RANDOM10 mode
            playRandom(10);
            break;
    }
}

void GameLogic::playRandom(int probability) {
  Serial.println("In play random");
  //This will create a psuedo random seed that the numbers will be based on.
  randomSeed(analogRead(0));
  int randomValue;

  while(isGameActive) {
    
    if (digitalRead(selectButtonPin) == HIGH) {
      randomValue = random(0,probability);
      Serial.println(randomValue);
      if (randomValue == 0) {
        //TRIGGER TASER
        delay(100);
        setBottomText("    YOU LOSE    ");
      }
    }
  }
}

void GameLogic::playClassic(int probability) {
  //This will create a psuedo random seed that the numbers will be based on.
  randomSeed(analogRead(0));
  int randomValue;

  while(isGameActive) {
    if (digitalRead(selectButtonPin) == HIGH) {
      randomValue = random(0,probability);
      Serial.print("Random value: ");
      Serial.print(randomValue);
      if (randomValue == 0) {
        //TRIGGER TASER
        delay(100);
        setBottomText("    YOU LOSE    ");
      }
    }

    delay(500);
  }
}