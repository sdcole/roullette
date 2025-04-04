#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <Arduino.h>
#include <GameMode.h>

#include "LEDUtils.h"

class GameLogic {
public:
    GameLogic(int navButtonPin, int selectButtonPin, int redPin, int greenPin, int bluePin, int relayPowerPin, int relaySwitchPin);
    void startGame(GameMode mode); // New function to handle game start logic
    void playRandom(int probability); // Function for random game logic
    void playClassic(int probability); // Function for classic game logic

private:
    int navButtonPin;      // Declare navButtonPin here
    int selectButtonPin;   // Declare selectButtonPin here
    int redPin;
    int greenPin;
    int bluePin;
    int relayPowerPin;
    int relaySwitchPin;
    bool isGameActive;     // Declare isGameActive here
    GameMode gameMode;  // Declare currentMode here
    LEDUtils ledUtils;
};

#endif // GAMELOGIC_H
