#include <wiringPi.h>
#include "movement_control.h"

// initialize GPIO pins and set pins to output
void control::init() {
    wiringPiSetupGpio();

    pinMode(17, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
}

// move forward
void control::forward() {
    digitalWrite(17, LOW);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    digitalWrite(24, HIGH);
}

// move backward
void control::reverse() {
    digitalWrite(17, HIGH);
    digitalWrite(22, LOW);
    digitalWrite(23, HIGH);
    digitalWrite(24, LOW);
}

// move left
void control::left() {
    digitalWrite(17, HIGH);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(24, HIGH);
}

// move right
void control::right() {
    digitalWrite(17, LOW);
    digitalWrite(22, HIGH);
    digitalWrite(23, HIGH);
    digitalWrite(24, LOW);
}

// stop movement
void control::stop() {
    digitalWrite(17, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(24, LOW);
}

// clean up GPIO pins by setting them as input
void control::cleanup() {
    pinMode(17, INPUT);
    pinMode(22, INPUT);
    pinMode(23, INPUT);
    pinMode(24, INPUT);
}
