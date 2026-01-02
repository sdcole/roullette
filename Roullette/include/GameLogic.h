#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <Arduino.h>
#include <GameMode.h>
#include <Relay.h>

class GameLogic {
public:
    GameLogic(int navButtonPin, int selectButtonPin,  Relay &relayPower, Relay &relaySwitch);
    void startGame(GameMode mode); // New function to handle game start logic
    void playRandom(int probability); // Function for random game logic
    void playClassic(int probability); // Function for classic game logic

private:
    int navButtonPin;      // Declare navButtonPin here
    int selectButtonPin;   // Declare selectButtonPin here
    Relay &relayPower;
    Relay &relaySwitch;
    bool isGameActive;     // Declare isGameActive here
    GameMode gameMode;  // Declare currentMode here
};

#endif // GAMELOGIC_H
