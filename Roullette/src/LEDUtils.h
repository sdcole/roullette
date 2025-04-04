#ifndef LEDUTILS_H
#define LEDUTILS_H

#include <Arduino.h>

class LEDUtils {
public:
    LEDUtils(int redPin, int greenPin, int bluePin);
    void setColor(int redValue, int greenValue, int blueValue);

private:
    int redPin;
    int greenPin;
    int bluePin;
};

#endif
