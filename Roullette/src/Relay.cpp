#include <Arduino.h>
#include "Relay.h"

// Initialize ledUtils in the constructor initializer list
Relay::Relay(int switchPin)
    : switchPin(switchPin), state(false) {
    pinMode(switchPin, OUTPUT);
}

void Relay::activate() {
    digitalWrite(switchPin, HIGH);
    state = true;
}

void Relay::deactivate() {
    digitalWrite(switchPin, LOW);
    state = false;
}

bool Relay::getState() const {
    return state;
}

void Relay::toggle(int timeMs) {
    if (state) {
        deactivate();
    } else {
        activate();
    }
    delay(timeMs);
    if (state) {
        deactivate();
    } else {
        activate();
    }
}

    
