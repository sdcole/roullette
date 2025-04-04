#include <Arduino.h>
#include "GameLogic.h"
#include "LCDUtils.h"
#include "LEDUtils.h"

// Initialize ledUtils in the constructor initializer list
GameLogic::GameLogic(int navButtonPin, int selectButtonPin, int redPin, int greenPin, int bluePin, int relayPowerPin, int relaySwitchPin)
    : navButtonPin(navButtonPin),
      selectButtonPin(selectButtonPin),
      redPin(redPin),
      greenPin(greenPin),
      bluePin(bluePin),
      relayPowerPin(relayPowerPin),
      relaySwitchPin(relaySwitchPin),
      isGameActive(false),
      ledUtils(redPin, greenPin, bluePin) {  // Initialize ledUtils here

    pinMode(navButtonPin, INPUT);
    pinMode(selectButtonPin, INPUT);
    pinMode(relayPowerPin, OUTPUT);
    pinMode(relaySwitchPin, OUTPUT);
}

void GameLogic::startGame(GameMode mode) {
    // Set the game mode
    gameMode = mode;
    isGameActive = true;

    // Use the existing ledUtils instance
    ledUtils.setColor(255, 255, 0); // Sets the LED to yellow
    digitalWrite(relayPowerPin, LOW);

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
                ledUtils.setColor(255, 0, 0); // Sets the LED to red
                setBottomText("    YOU LOSE    ");
                digitalWrite(relaySwitchPin, LOW);
                delay(150);
                digitalWrite(relaySwitchPin, HIGH);
                delay(500);
                clearBottomRow();
                return;
            } else {
                setBottomText("      SAFE     ");
                delay(500);
                clearBottomRow();
            }
        }
    }
}

void GameLogic::playClassic(int probability) {
    randomSeed(analogRead(0));
    int randomValue = random(0, probability);
    int currentValue = 0;

    while (isGameActive) {
        if (digitalRead(selectButtonPin) == HIGH) {
            if (currentValue == randomValue) {
                ledUtils.setColor(255, 0, 0); // Sets the LED to red
                setBottomText("    YOU LOSE    ");
                digitalWrite(relaySwitchPin, LOW);
                delay(150);
                digitalWrite(relaySwitchPin, HIGH);
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
