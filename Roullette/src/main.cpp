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
#include "LEDUtils.h"
#include "GameMode.h"
#include "GameLogic.h"

//Prototypes
void clearTopRow();
void clearBottomRow();
void setTopText(const char*);
void setBottomText(const char*);
void setColor(int, int, int);

const char* getCurrentGameModeText(GameMode);
void incrementGameMode(GameMode &gameMode);

//initialize the liquid crystal library
const int navButtonPin = 2;
const int selectButtonPin = 3;

const int relayPowerPin = 4;
const int relaySwitchPin = 5;


//Init buttons
int redPin= 6;
int greenPin = 7;
int bluePin = 8;
LEDUtils ledUtils(redPin, greenPin, bluePin);

bool isPlaying = 0;
bool bottomTextChange = 0;
bool topTextChange = 0;

GameMode gameMode = GameMode::CLASSIC6;
GameLogic gameLogic(navButtonPin, selectButtonPin, redPin, greenPin, bluePin, relayPowerPin, relaySwitchPin);

void setup() {
  pinMode(relayPowerPin, OUTPUT);
  pinMode(relaySwitchPin, OUTPUT);
  digitalWrite(relayPowerPin, HIGH);
  digitalWrite(relaySwitchPin,HIGH);
  Serial.begin(9600);
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  //Setup Pins
  pinMode(navButtonPin, INPUT);
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //Set Top Game Text
  setTopText("TASER ROULLETTE ");
  delay(1000);
  //Sleep 1000ms before starting game
  //Begining of the loop -- Here we need to begin menu logic.
  setTopText("  SELECT MODE   ");

  //Set the initial bottom text with the first game mode.
  setBottomText(getCurrentGameModeText(gameMode));
  ledUtils.setColor(0,  255, 0); // Green Color
}

void loop() {

  //This condition if true will begin the game based off of the selected gamemode.
  if (isPlaying) {
    //PlayGame
    gameLogic.startGame(gameMode);
    //If we ever get here restart setup.
    isPlaying = false;
    delay(250);
    setTopText("  SELECT MODE   ");
    setBottomText(getCurrentGameModeText(gameMode));
    ledUtils.setColor(0,  255, 0); // Green Color
  }
  else {
    //This condition will begin the game if the button is pressed.
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