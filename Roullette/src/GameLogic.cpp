#include <Arduino.h>
#include "GameLogic.h"
#include "LCDUtils.h"
#include "Relay.h"

// Initialize ledUtils in the constructor initializer list
GameLogic::GameLogic(int navButtonPin, int selectButtonPin, Relay &relayPower, Relay &relaySwitch)
    : navButtonPin(navButtonPin),
      selectButtonPin(selectButtonPin),
      relayPower(relayPower),
      relaySwitch(relaySwitch),
      isGameActive(false) {  // Initialize ledUtils here

    pinMode(navButtonPin, INPUT);
    pinMode(selectButtonPin, INPUT);
}

void GameLogic::startGame(GameMode mode) {
    // Set the game mode
    gameMode = mode;
    isGameActive = true;

    //Relay set to low will turn it on.
    relayPower.deactivate();

    Serial.println("Game Started!");
    Serial.print("Game Mode: ");
    Serial.print(static_cast<int>(gameMode));

    switch (gameMode) {
        case GameMode::CLASSIC6:
            playClassic(6);
            break;
        case GameMode::CLASSIC10:
            playClassic(10);
            break;
        case GameMode::RANDOM6:
            playRandom(6);
            break;
        case GameMode::RANDOM10:
            playRandom(10);
            break;
    }
}

void GameLogic::playRandom(int probability) {
    Serial.println("In play random");
    randomSeed(analogRead(0));
    int randomValue;

    while (isGameActive) {
        if (digitalRead(selectButtonPin) == HIGH) {
            randomValue = random(0, probability);
            Serial.println(randomValue);
            if (randomValue == 0) {
                setBottomText("    YOU LOSE    ");
                relaySwitch.toggle(500);
                delay(500);
                clearBottomRow();
                return;
            } else {
                setBottomText("      SAFE     ");
                delay(500);
                clearBottomRow();
            }
        }
        delay(500);
    }
}

void GameLogic::playClassic(int probability) {
    randomSeed(analogRead(0));
    int randomValue = random(0, probability);
    int currentValue = 0;

    while (isGameActive) {
        if (digitalRead(selectButtonPin) == HIGH) {
            if (currentValue == randomValue) {
                setBottomText("    YOU LOSE    ");
                relaySwitch.toggle(500);
                delay(500);
                clearBottomRow();
                return;
            } else {
                currentValue++;
                setBottomText("      SAFE      ");
                delay(500);
                clearBottomRow();
            }
        }
    }

    delay(500);
    
}
