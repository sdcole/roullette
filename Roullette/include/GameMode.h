// GameMode.h
#ifndef GAMEMODE_H
#define GAMEMODE_H

// Define an enumeration for different game modes
// 4 different Game Modes:
// Classic (normal roullette rules where set probabilities like 1 out of 6 will occur).
// Random (truly/psudo random probability meaning statistics don't go up).
enum class GameMode {
    CLASSIC6,
    CLASSIC10,
    RANDOM6,
    RANDOM10,
};

#endif // GAMEMODE_H