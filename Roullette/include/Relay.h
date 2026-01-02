// Relay.h
#ifndef RELAY_H
#define RELAY_H

class Relay {
public:
    Relay(int switchPin);
    void activate();
    void deactivate();
    bool getState() const;
    void toggle(int timeMs);


private:
    int switchPin;
    bool state;

};


#endif // RELAY_H