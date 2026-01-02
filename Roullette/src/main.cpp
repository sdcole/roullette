/*
* Roulette main.cpp
* Author: Saebastion Cole
* Date: 10/20/2024
* This program is meant to run on a Arduino Nano.
* It uses an IC2 display and momentary pushbuttons. to control the game.
* Roullette 
*/
//Imports
//Standard
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Local
#include "LCDUtils.h"
#include "GameMode.h"
#include "GameLogic.h"
#include "Relay.h"

//Prototypes
void clearTopRow();
void clearBottomRow();
void setTopText(const char*);
void setBottomText(const char*);

const char* getCurrentGameModeText(GameMode);
void incrementGameMode(GameMode &gameMode);

//initialize the liquid crystal library
const int navButtonPin = 5;
const int selectButtonPin = 6;

const int relayPowerPin = 10;
const int relaySwitchPin = 8;




bool isPlaying = 0;
bool bottomTextChange = 0;
bool topTextChange = 0;

GameMode gameMode = GameMode::CLASSIC6;

Relay relayPower(relayPowerPin);
Relay relaySwitch(relaySwitchPin);

GameLogic gameLogic(navButtonPin, selectButtonPin, relayPower, relaySwitch);

void setup() {

  relayPower.activate();
  relaySwitch.activate();


  Serial.begin(9600);
  Serial.print("INIT");
  //initialize lcd screen
  Wire.begin();
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  //Setup Pins
  pinMode(navButtonPin, INPUT);

  Serial.print("setting text");
  //Set Top Game Text
  setTopText("TASER ROULLETTE ");
  delay(1000);
  //Sleep 1000ms before starting game
  //Begining of the loop -- Here we need to begin menu logic.
  setTopText("  SELECT MODE   ");

  //Set the initial bottom text with the first game mode.
  setBottomText(getCurrentGameModeText(gameMode));
}

void loop() {
  relayPower.activate();
  //This condition if true will begin the game based off of the selected gamemode.
  if (isPlaying) {
    //PlayGame
    gameLogic.startGame(gameMode);
    //If we ever get here restart setup.
    isPlaying = false;
    delay(250);
    setTopText("  SELECT MODE   ");
    setBottomText(getCurrentGameModeText(gameMode));
  }
  else {
    //This condition will begin the game if the button is pressed.
    Serial.print(digitalRead(selectButtonPin));
    Serial.print(digitalRead(navButtonPin));
    if (digitalRead(selectButtonPin) == HIGH) {
      //Delays are required using I2C interface otherwise LCD will not update.
      delay(250);
      setBottomText("   BEGIN GAME   ");
      //Set state of the game to begin
      
      setTopText(getCurrentGameModeText(gameMode));
      isPlaying = true;
    }
    //This condition will move game types in the menu.
    else if (digitalRead(navButtonPin) == HIGH) {
      incrementGameMode(gameMode);
      setBottomText(getCurrentGameModeText(gameMode));
      
    }

    delay(750);
    
    }
    
}




void incrementGameMode(GameMode &mode) {
    mode = static_cast<GameMode>((static_cast<int>(mode) + 1) % static_cast<int>(4));
}



/*
* currentGameModeText
* This function gets passed the current game mode and returns the char array pointer that is needed to load into the display.
*
*/
const char* getCurrentGameModeText(GameMode gameMode) {

  switch (gameMode) {
    case GameMode::CLASSIC6:
      return "   CLASSIC 6    ";
      break;
    case GameMode::CLASSIC10:
      return "   CLASSIC 10   ";
      break;
    case GameMode::RANDOM6:
      return "    RANDOM 6    ";
      break;
    case GameMode::RANDOM10:
      return "    RANDOM 10   ";
      break;
  }
  return "  ERROR VALUE  ";
}